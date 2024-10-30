/*
*  display.c:
* 화면에 게임 정보를 출력
* 맵, 커서, 시스템 메시지, 정보창, 자원 상태 등등
* io.c에 있는 함수들을 사용함
*/

#include "display.h"
#include "io.h"
#include <string.h>

// 출력할 내용들의 좌상단(topleft) 좌표 -> 디스플레이 세션 위치
const POSITION resource_pos = { 0, 0 };         // 자원 상태 위치
const POSITION system_message_pos = { 10, 2 };  // 시스템 메시지 위치
const POSITION status_message_pos = { 20, 4 };  // 상태창 위치
const POSITION command_message_pos = { 30, 6 }; // 명령창 위치
const POSITION map_pos = { 5, 10 };             // 맵 위치


char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };

void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]);
void display_cursor(CURSOR cursor);
void display_system_message(const char* message);
void display_status_message(const char* message);
void display_command_message(const char* message);


// display()하위 함수 작성
void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],  CURSOR cursor, 
	const char* system_message, const char* status_message, const char* command_message)
{
	display_resource(resource);
	display_map(map);
	display_cursor(cursor);
	display_system_message(system_message);
	display_status_message(status_message);
	display_command_message(command_message);

}

void display_resource(RESOURCE resource) {
	set_color(COLOR_RESOURCE);
	gotoxy(resource_pos);
	printf("spice = %d/%d, population=%d/%d\n",
		resource.spice, resource.spice_max,
		resource.population, resource.population_max
	);
}

// 1) 화면 배치
void display_system_message(const char* message) {
	set_color(COLOR_DEFAULT);
	gotoxy(system_message_pos);
	printf("System: %s\n", message);
}

void display_status_message(const char* message) {
	set_color(COLOR_DEFAULT);
	gotoxy(status_message_pos);
	printf("Status: %s\n", message);
}

void display_command_message(const char* message) {
	set_color(COLOR_DEFAULT);
	gotoxy(command_message_pos);
	printf("Command: %s\n", message);
}

// subfunction of draw_map()
void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			for (int k = 0; k < N_LAYER; k++) {
				if (src[k][i][j] >= 0) {
					dest[i][j] = src[k][i][j];
				}
			}
		}
	}
}

// 맵 함수
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) {
	project(map, backbuf);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			int color = COLOR_DEFAULT;
			switch (backbuf[i][j]) {
			case 'B': color = COLOR_PLAYER; break;    // 본진 (파란색 또는 빨간색)
			case 'P': color = COLOR_PLATE; break;     // 장판 (검은색)
			case 'H': color = COLOR_AI; break;        // 하베스터 (파란색 또는 빨간색)
			case 'W': color = COLOR_SANDWORM; break;  // 샌드웜 (황토색)
			case '5': color = COLOR_SPICE; break;     // 스파이스 (주황색)
			case 'R': color = COLOR_ROCK; break;      // 바위 (회색)
			}

			if (frontbuf[i][j] != backbuf[i][j]) {
				POSITION pos = { map_pos.row + i, map_pos.column + j };
				printc(pos, backbuf[i][j], color);
			}
			frontbuf[i][j] = backbuf[i][j];
		}
	}
}


// frontbuf[][]에서 커서 위치의 문자를 색만 바꿔서 그대로 다시 출력
void display_cursor(CURSOR cursor) {
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	printc(padd(map_pos, prev), ch, COLOR_DEFAULT);

	ch = frontbuf[curr.row][curr.column];
	printc(padd(map_pos, curr), ch, COLOR_CURSOR);
}

void display_building_info(const BUILDING* building) {
	printf("건물 이름: %s\n", building->name);
	printf("건설 비용: %d\n", building->build_cost);
	printf("내구도: %d\n", building->capacity);
	printf("설명: %s\n", building->description);
	if (building->command_key) {
		printf("명령어 단축키: %c\n", building->command_key);
	}
}


void display_unit_info(const UNIT* unit) {
	printf("유닛 이름: %s\n", unit->name);
	printf("생산 비용: %d\n", unit->production_cost);
	printf("인구 수: %d\n", unit->population);
	printf("이동 주기: %d\n", unit->move_speed);
	printf("공격력: %d\n", unit->attack);
	printf("공격 주기: %d\n", unit->range);
	printf("체력: %d\n", unit->health);
	printf("시야: %d\n", unit->sight);
	if (unit->command_key) {
		printf("명령어 단축키: %c\n", unit->command_key);
	}
}