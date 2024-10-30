#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "common.h"
#include "io.h"
#include "display.h"

void init(void);
void intro(void);
void outro(void);
void cursor_move(DIRECTION dir);
void sample_obj_move(void);
void show_all_buildings();
void show_all_units();

POSITION sample_obj_next_position(void);

/* ================= control =================== */
int sys_clock = 0;		// system-wide clock(ms)
CURSOR cursor = { { 1, 1 }, {1, 1} };


/* ================= game data =================== */
char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH] = { 0 };

RESOURCE resource = { 
	.spice = 0,
	.spice_max = 0,
	.population = 0,
	.population_max = 0
};

OBJECT_SAMPLE obj = {
	.pos = {1, 1},
	.dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2},
	.repr = 'o',
	.speed = 300,
	.next_move_time = 300
};

BUILDING buildings[] = {
	{"Base", 0, 50, "본진", 'H'},
	{"Plate", 1, 0, "건물 짓기 전에 깔기", '\0'},
	{"Dormitory", 2, 10, "인구 최대치 증가(10)", '\0'},
	{"Garage", 4, 10, "스파이스 보관 최대치 증가(10)", '\0'},
	{"Barracks", 4, 20, "보병 생산", 'S'},
	{"Shelter", 5, 30, "특수유닛 생산", 'F'},
	{"Arena", 3, 15, "투사 생산", 'F'},
	{"Factory", 5, 30, "중전차 생산", 'T'}
};

UNIT units[] = {
	{"Harvester", 5, 5, 2000, 0, 0, 70, 0, 'H'},
	{"Fremen", 5, 2, 400, 15, 200, 25, 8, 'M'},
	{"Soldier", 1, 1, 1000, 5, 800, 15, 1, 'M'},
	{"Fighter", 1, 1, 1200, 6, 1000, 20, 4, 'M'},
	{"Heavy Tank", 12, 5, 3000, 40, 4000, 60, 4, 'M'},
	{"Sandworm", 0, 0, 2500, -1, 10000, -1, -1, '\0'}
};


/* ================= main() =================== */
int main(void) {
	srand((unsigned int)time(NULL));
	init();
	intro();
	display(resource, map, cursor);
	printf("display");
	show_all_buildings();
	printf("show buildings");
	show_all_units();
	printf("show units");

	while (1) {
		// loop 돌 때마다(즉, TICK==10ms마다) 키 입력 확인
		KEY key = get_key();

		// 키 입력이 있으면 처리
		if (is_arrow_key(key)) {
			cursor_move(ktod(key));
		}
		else {
			// 방향키 외의 입력
			switch (key) {
			case k_quit: outro();
			case k_none:
			case k_undef:
			default: break;
			}
		}

		// 샘플 오브젝트 동작
		sample_obj_move();

		// 화면 출력
		display(resource, map, cursor);
		Sleep(TICK);
		sys_clock += 10;
	}
	outro();
	printf("outro");
}

/* ================= subfunctions =================== */
void intro(void) {
	printf("DUNE 1.5\n");		
	Sleep(2000);
	//system("cls");
}

void outro(void) {
	printf("exiting...\n");
	exit(0);
}

/* =====================맵 데이터 설정 =====================*/
void init(void) {
	// 기본 지형 설정 (빈칸)
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			map[0][i][j] = ' '; // 기본 지형 빈칸
		}
	}

	// 객체 배치 설정 (이미지와 일치하도록 조정)
	map[0][0][0] = 'B';  // 본진 (파란색)
	map[0][0][1] = 'P';  // 장판 (검은색)
	map[0][1][0] = 'H';  // 하베스터 (파란색)
	map[0][1][2] = '5';  // 스파이스 (주황색)
	map[0][2][2] = 'W';  // 샌드웜 (황토색)
	map[0][4][1] = 'R';  // 바위 (회색)
	map[0][4][5] = 'R';  // 바위 (회색)
	map[0][2][5] = 'R';  // 바위 (회색)
	map[0][6][3] = 'P';  // 장판 (검은색)
	map[0][6][4] = 'B';  // 본진 (빨간색)
	map[0][6][5] = 'H';  // 하베스터 (빨간색)
}

// (가능하다면) 지정한 방향으로 커서 이동
void cursor_move(DIRECTION dir) {
	POSITION curr = cursor.current;
	POSITION new_pos = pmove(curr, dir);

	// validation check
	if (1 <= new_pos.row && new_pos.row <= MAP_HEIGHT - 2 && \
		1 <= new_pos.column && new_pos.column <= MAP_WIDTH - 2) {

		cursor.previous = cursor.current;
		cursor.current = new_pos;
	}
}

/* ================= sample object movement =================== */
POSITION sample_obj_next_position(void) {
	// 현재 위치와 목적지를 비교해서 이동 방향 결정	
	POSITION diff = psub(obj.dest, obj.pos);
	DIRECTION dir;

	// 목적지 도착. 지금은 단순히 원래 자리로 왕복
	if (diff.row == 0 && diff.column == 0) {
		if (obj.dest.row == 1 && obj.dest.column == 1) {
			// topleft --> bottomright로 목적지 설정
			POSITION new_dest = { MAP_HEIGHT - 2, MAP_WIDTH - 2 };
			obj.dest = new_dest;
		}
		else {
			// bottomright --> topleft로 목적지 설정
			POSITION new_dest = { 1, 1 };
			obj.dest = new_dest;
		}
		return obj.pos;
	}
	
	// 가로축, 세로축 거리를 비교해서 더 먼 쪽 축으로 이동
	if (abs(diff.row) >= abs(diff.column)) {
		dir = (diff.row >= 0) ? d_down : d_up;
	}
	else {
		dir = (diff.column >= 0) ? d_right : d_left;
	}
	
	// validation check
	// next_pos가 맵을 벗어나지 않고, (지금은 없지만)장애물에 부딪히지 않으면 다음 위치로 이동
	// 지금은 충돌 시 아무것도 안 하는데, 나중에는 장애물을 피해가거나 적과 전투를 하거나... 등등
	POSITION next_pos = pmove(obj.pos, dir);
	if (1 <= next_pos.row && next_pos.row <= MAP_HEIGHT - 2 && \
		1 <= next_pos.column && next_pos.column <= MAP_WIDTH - 2 && \
		map[1][next_pos.row][next_pos.column] < 0) {
		
		return next_pos;
	}
	else {
		return obj.pos;  // 제자리
	}
}

void sample_obj_move(void) {
	if (sys_clock <= obj.next_move_time) {
		// 아직 시간이 안 됐음
		return;
	}

	// 오브젝트(건물, 유닛 등)은 layer1(map[1])에 저장
	map[1][obj.pos.row][obj.pos.column] = -1;
	obj.pos = sample_obj_next_position();
	map[1][obj.pos.row][obj.pos.column] = obj.repr;

	obj.next_move_time = sys_clock + obj.speed;
}

void show_all_buildings() {
	for (int i = 0; i < sizeof(buildings) / sizeof(BUILDING); i++) {
		display_building_info(&buildings[i]);
		printf("\n");
	}
}

void show_all_units() {
	for (int i = 0; i < sizeof(units) / sizeof(UNIT); i++) {
		display_unit_info(&units[i]);
		printf("\n");
	}
}