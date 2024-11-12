/*
*  display.c:
* 화면에 게임 정보를 출력
* 맵, 커서, 시스템 메시지, 정보창, 자원 상태 등등
* io.c에 있는 함수들을 사용함
*/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"

// 표시할 색상 정의. 대충 맞춰 뒀는데, 취향껏 추가하거나 변경하기
#define COLOR_DEFAULT	15
#define COLOR_CURSOR	112
#define COLOR_RESOURCE  112

#define COLOR_BACKGROUND_WHITE 240 // 흰색 배경 색상 코드
#define COLOR_DEFAULT    15  // 기본 색상 (흰색)
#define COLOR_CURSOR     112 // 커서 색상
#define COLOR_RESOURCE   14  // 자원 표시 색상 (노란색)
#define COLOR_PLAYER     9   // 플레이어 본진 색상 (파란색)
#define COLOR_PLATE      2   // 장판 색상 (초록색)
#define COLOR_AI         12  // AI 하베스터 색상 (빨간색)
#define COLOR_SANDWORM   6   // 샌드웜 색상 (황토색)
#define COLOR_SPICE      14  // 스파이스 색상 (노란색)
#define COLOR_ROCK       8   // 바위 색상 (회색)

void display_system_message(const char* message);
void display_status_message(const char* message);
void display_command_message(const char* message);

// 지금은 자원, 맵, 커서만 표시
// 앞으로 화면에 표시할 내용들 여기에 추가하기
void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	CURSOR cursor
);

#endif
