/*
*  display.c:
* 화면에 게임 정보를 출력
* 맵, 커서, 시스템 메시지, 정보창, 자원 상태 등등
* io.c에 있는 함수들을 사용함
*/

#include "display.h"
#include "io.h"

// 출력할 내용들의 좌상단(topleft) 좌표
const POSITION resource_pos = { 0, 0 };
const POSITION map_pos = { 2, 5 };
const POSITION system_message_pos = { MAP_HEIGHT + 2, 5};
const POSITION status_message_pos = { 2, MAP_WIDTH + 7 };
const POSITION command_message_pos = { MAP_HEIGHT + 2, MAP_WIDTH + 7 };

char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };

void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]);
void display_cursor(CURSOR cursor);


void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH], 
	CURSOR cursor)
{
	display_resource(resource);
	display_map(map);
	display_cursor(cursor);
    display_system_message("System initialized");   // 시스템 메시지 출력
    display_status_message("Status OK");            // 상태창 메시지 출력
    display_command_message("Enter command");       // 명령창 메시지 출력

}

void display_system_message(const char* message) {
	set_color(COLOR_DEFAULT);
	gotoxy(system_message_pos);
	printf("System: %s\n", message ? message : "No system message");
}

void display_status_message(const char* message) {
	set_color(COLOR_DEFAULT);
	gotoxy(status_message_pos);
	printf("Status: %s\n", message ? message : "No status");
}

void display_command_message(const char* message) {
	set_color(COLOR_DEFAULT);
	gotoxy(command_message_pos);
	printf("Command: %s\n", message ? message : "No command");
}


void display_resource(RESOURCE resource) {
	set_color(COLOR_RESOURCE);
	gotoxy(resource_pos);
	printf("spice = %d/%d, population=%d/%d\n",
		resource.spice, resource.spice_max,
		resource.population, resource.population_max
	);
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

void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) {
    static bool initialized = false; // 초기화 여부 확인

    if (!initialized) {
        // 맵 지형 설정 (한 번만 설정됨)
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                map[0][i][j] = ' '; // 기본 지형을 빈칸으로 설정
            }
        }

        // 맵의 경계에 # 문자를 설정
        for (int j = 0; j < MAP_WIDTH; j++) {
            map[0][0][j] = '#';                  // 상단 경계
            map[0][MAP_HEIGHT - 1][j] = '#';     // 하단 경계
        }
        for (int i = 0; i < MAP_HEIGHT; i++) {
            map[0][i][0] = '#';                  // 왼쪽 경계
            map[0][i][MAP_WIDTH - 1] = '#';      // 오른쪽 경계
        }

        // 지형 요소 배치 (경계 안쪽에 배치)
        map[0][MAP_HEIGHT - 2][1] = 'B';    // 아트레이디스 본진(파란색)
        map[0][MAP_HEIGHT - 2][2] = 'B';
        map[0][MAP_HEIGHT - 3][1] = 'B';
        map[0][MAP_HEIGHT - 3][2] = 'B';

        map[0][MAP_HEIGHT - 2][3] = 'P';    // 아트레이디스 본진 하단 장판
        map[0][MAP_HEIGHT - 2][4] = 'P';
        map[0][MAP_HEIGHT - 3][3] = 'P';
        map[0][MAP_HEIGHT - 3][4] = 'P';

        map[0][MAP_HEIGHT - 4][1] = 'H';    // 아트레이디스 하베스터

        map[0][MAP_HEIGHT - 6][1] = '5';    // 왼쪽 상단 스파이스

        map[0][5][MAP_WIDTH / 4] = 'W';     // 샌드웜

        map[0][MAP_HEIGHT - 6][7] = 'R';    // 아트레이디스 본진 Rock

        // 하코넨 본진 배치 (1시 방향)
        map[0][1][MAP_WIDTH - 2] = 'B';
        map[0][1][MAP_WIDTH - 3] = 'B';
        map[0][2][MAP_WIDTH - 2] = 'B';
        map[0][2][MAP_WIDTH - 3] = 'B';

        map[0][1][MAP_WIDTH - 4] = 'P';
        map[0][1][MAP_WIDTH - 5] = 'P';
        map[0][2][MAP_WIDTH - 4] = 'P';
        map[0][2][MAP_WIDTH - 5] = 'P';

        map[0][3][MAP_WIDTH - 2] = 'H';

        map[0][5][MAP_WIDTH - 2] = '5';

        map[0][MAP_HEIGHT - 5][MAP_WIDTH - MAP_WIDTH / 4] = 'W';

        map[0][5][MAP_WIDTH - 7] = 'R';

        // 바위 배치
        map[0][MAP_HEIGHT - 4][MAP_WIDTH - 9] = 'R';

        map[0][7][MAP_WIDTH / 2 - 1] = 'R';
        map[0][7][MAP_WIDTH / 2] = 'R';
        map[0][8][MAP_WIDTH / 2 - 1] = 'R';
        map[0][8][MAP_WIDTH / 2] = 'R';

        map[0][MAP_HEIGHT - 7][MAP_WIDTH - MAP_WIDTH / 2 - 1] = 'R';
        map[0][MAP_HEIGHT - 7][MAP_WIDTH - MAP_WIDTH / 2] = 'R';
        map[0][MAP_HEIGHT - 8][MAP_WIDTH - MAP_WIDTH / 2 - 1] = 'R';
        map[0][MAP_HEIGHT - 8][MAP_WIDTH - MAP_WIDTH / 2] = 'R';

        initialized = true; // 초기화를 완료했음을 표시
    }

    project(map, backbuf);  // 현재 상태를 backbuf에 복사

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int color = COLOR_DEFAULT;

            // 7시 방향 영역의 모든 건물과 유닛을 파란색으로 표시
            if ((i >= MAP_HEIGHT - 4 && i <= MAP_HEIGHT - 2) && (j >= 1 && j <= 4)) {
                if (backbuf[i][j] == 'B' || backbuf[i][j] == 'H' || backbuf[i][j] == 'b' || backbuf[i][j] == 'h') {
                    color = COLOR_PLAYER;
                }
            }
            // 1시 방향 영역의 모든 건물과 유닛을 빨간색으로 표시
            else if ((i >= 1 && i <= 3) && (j >= MAP_WIDTH - 5 && j <= MAP_WIDTH - 2)) {
                if (backbuf[i][j] == 'B' || backbuf[i][j] == 'H' || backbuf[i][j] == 'b' || backbuf[i][j] == 'h') {
                    color = COLOR_AI;
                }
            }
            else {
                // 나머지 기본 색상 설정
                switch (backbuf[i][j]) {
                case 'B': color = COLOR_PLAYER; break;   // 기본 본진 색상
                case 'H': color = COLOR_AI; break;       // 기본 하베스터 색상
                case 'P': color = COLOR_PLATE; break;    // 장판 색상
                case '5': color = COLOR_SPICE; break;    // 스파이스 색상
                case 'W': color = COLOR_SANDWORM; break; // 샌드웜 색상
                case 'R': color = COLOR_ROCK; break;     // 바위 색상
                case '#': color = COLOR_DEFAULT; break;  // 경계선 색상
                default: color = COLOR_DEFAULT; break;
                }
            }

            if (frontbuf[i][j] != backbuf[i][j]) {
                POSITION pos = { map_pos.row + i, map_pos.column + j };
                printc(pos, backbuf[i][j], color);  // 해당 위치에 출력
            }
            frontbuf[i][j] = backbuf[i][j];  // frontbuf에 현재 상태 기록
        }
    }
}



// frontbuf[][]에서 커서 위치의 문자를 색만 바꿔서 그대로 다시 출력
void display_cursor(CURSOR cursor){
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	printc(padd(map_pos, prev), ch, COLOR_DEFAULT);

	ch = frontbuf[curr.row][curr.column];
	printc(padd(map_pos, curr), ch, COLOR_CURSOR);
}