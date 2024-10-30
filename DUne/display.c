/*
*  display.c:
* ȭ�鿡 ���� ������ ���
* ��, Ŀ��, �ý��� �޽���, ����â, �ڿ� ���� ���
* io.c�� �ִ� �Լ����� �����
*/

#include "display.h"
#include "io.h"
#include <string.h>

// ����� ������� �»��(topleft) ��ǥ -> ���÷��� ���� ��ġ
const POSITION resource_pos = { 0, 0 };         // �ڿ� ���� ��ġ
const POSITION system_message_pos = { 10, 2 };  // �ý��� �޽��� ��ġ
const POSITION status_message_pos = { 20, 4 };  // ����â ��ġ
const POSITION command_message_pos = { 30, 6 }; // ���â ��ġ
const POSITION map_pos = { 5, 10 };             // �� ��ġ


char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };

void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]);
void display_cursor(CURSOR cursor);
void display_system_message(const char* message);
void display_status_message(const char* message);
void display_command_message(const char* message);


// display()���� �Լ� �ۼ�
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

// 1) ȭ�� ��ġ
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

// �� �Լ�
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) {
	project(map, backbuf);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			int color = COLOR_DEFAULT;
			switch (backbuf[i][j]) {
			case 'B': color = COLOR_PLAYER; break;    // ���� (�Ķ��� �Ǵ� ������)
			case 'P': color = COLOR_PLATE; break;     // ���� (������)
			case 'H': color = COLOR_AI; break;        // �Ϻ����� (�Ķ��� �Ǵ� ������)
			case 'W': color = COLOR_SANDWORM; break;  // ����� (Ȳ���)
			case '5': color = COLOR_SPICE; break;     // �����̽� (��Ȳ��)
			case 'R': color = COLOR_ROCK; break;      // ���� (ȸ��)
			}

			if (frontbuf[i][j] != backbuf[i][j]) {
				POSITION pos = { map_pos.row + i, map_pos.column + j };
				printc(pos, backbuf[i][j], color);
			}
			frontbuf[i][j] = backbuf[i][j];
		}
	}
}


// frontbuf[][]���� Ŀ�� ��ġ�� ���ڸ� ���� �ٲ㼭 �״�� �ٽ� ���
void display_cursor(CURSOR cursor) {
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	printc(padd(map_pos, prev), ch, COLOR_DEFAULT);

	ch = frontbuf[curr.row][curr.column];
	printc(padd(map_pos, curr), ch, COLOR_CURSOR);
}

void display_building_info(const BUILDING* building) {
	printf("�ǹ� �̸�: %s\n", building->name);
	printf("�Ǽ� ���: %d\n", building->build_cost);
	printf("������: %d\n", building->capacity);
	printf("����: %s\n", building->description);
	if (building->command_key) {
		printf("��ɾ� ����Ű: %c\n", building->command_key);
	}
}


void display_unit_info(const UNIT* unit) {
	printf("���� �̸�: %s\n", unit->name);
	printf("���� ���: %d\n", unit->production_cost);
	printf("�α� ��: %d\n", unit->population);
	printf("�̵� �ֱ�: %d\n", unit->move_speed);
	printf("���ݷ�: %d\n", unit->attack);
	printf("���� �ֱ�: %d\n", unit->range);
	printf("ü��: %d\n", unit->health);
	printf("�þ�: %d\n", unit->sight);
	if (unit->command_key) {
		printf("��ɾ� ����Ű: %c\n", unit->command_key);
	}
}