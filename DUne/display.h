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

#define COLOR_PLAYER 9    // 본진 색상 (파란색 또는 빨간색)
#define COLOR_PLATE 8     // 장판 색상 (검은색)
#define COLOR_AI 12       // 하베스터 색상 (빨간색)
#define COLOR_SANDWORM 14 // 샌드웜 색상 (황토색)
#define COLOR_SPICE 6     // 스파이스 색상 (주황색)
#define COLOR_ROCK 7      // 바위 색상 (회색)

// 지금은 자원, 맵, 커서만 표시
// 앞으로 화면에 표시할 내용들 여기에 추가하기
void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	CURSOR cursor
);

#endif
