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

#define COLOR_BACKGROUND_WHITE 240 // ��� ��� ���� �ڵ�
#define COLOR_DEFAULT    15  // �⺻ ���� (���)
#define COLOR_CURSOR     112 // Ŀ�� ����
#define COLOR_RESOURCE   14  // �ڿ� ǥ�� ���� (�����)
#define COLOR_PLAYER     9   // �÷��̾� ���� ���� (�Ķ���)
#define COLOR_PLATE      2   // ���� ���� (�ʷϻ�)
#define COLOR_AI         12  // AI �Ϻ����� ���� (������)
#define COLOR_SANDWORM   6   // ����� ���� (Ȳ���)
#define COLOR_SPICE      14  // �����̽� ���� (�����)
#define COLOR_ROCK       8   // ���� ���� (ȸ��)

void display_system_message(const char* message);
void display_status_message(const char* message);
void display_command_message(const char* message);

// ������ �ڿ�, ��, Ŀ���� ǥ��
// ������ ȭ�鿡 ǥ���� ����� ���⿡ �߰��ϱ�
void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	CURSOR cursor
);

#endif
