/*
*  display.c:
* ȭ�鿡 ���� ������ ���
* ��, Ŀ��, �ý��� �޽���, ����â, �ڿ� ���� ���
* io.c�� �ִ� �Լ����� �����
*/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"

// ǥ���� ���� ����. ���� ���� �״µ�, ���ⲯ �߰��ϰų� �����ϱ�
#define COLOR_DEFAULT	15
#define COLOR_CURSOR	112
#define COLOR_RESOURCE  112

#define COLOR_PLAYER 9    // ���� ���� (�Ķ��� �Ǵ� ������)
#define COLOR_PLATE 8     // ���� ���� (������)
#define COLOR_AI 12       // �Ϻ����� ���� (������)
#define COLOR_SANDWORM 14 // ����� ���� (Ȳ���)
#define COLOR_SPICE 6     // �����̽� ���� (��Ȳ��)
#define COLOR_ROCK 7      // ���� ���� (ȸ��)

// ������ �ڿ�, ��, Ŀ���� ǥ��
// ������ ȭ�鿡 ǥ���� ����� ���⿡ �߰��ϱ�
void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	CURSOR cursor
);

#endif
