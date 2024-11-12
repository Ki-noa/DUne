/*
*  display.c:
* ȭ�鿡 ���� ������ ���
* ��, Ŀ��, �ý��� �޽���, ����â, �ڿ� ���� ���
* io.c�� �ִ� �Լ����� �����
*/

#include "display.h"
#include "io.h"

// ����� ������� �»��(topleft) ��ǥ
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
    display_system_message("System initialized");   // �ý��� �޽��� ���
    display_status_message("Status OK");            // ����â �޽��� ���
    display_command_message("Enter command");       // ���â �޽��� ���

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
    static bool initialized = false; // �ʱ�ȭ ���� Ȯ��

    if (!initialized) {
        // �� ���� ���� (�� ���� ������)
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                map[0][i][j] = ' '; // �⺻ ������ ��ĭ���� ����
            }
        }

        // ���� ��迡 # ���ڸ� ����
        for (int j = 0; j < MAP_WIDTH; j++) {
            map[0][0][j] = '#';                  // ��� ���
            map[0][MAP_HEIGHT - 1][j] = '#';     // �ϴ� ���
        }
        for (int i = 0; i < MAP_HEIGHT; i++) {
            map[0][i][0] = '#';                  // ���� ���
            map[0][i][MAP_WIDTH - 1] = '#';      // ������ ���
        }

        // ���� ��� ��ġ (��� ���ʿ� ��ġ)
        map[0][MAP_HEIGHT - 2][1] = 'B';    // ��Ʈ���̵� ����(�Ķ���)
        map[0][MAP_HEIGHT - 2][2] = 'B';
        map[0][MAP_HEIGHT - 3][1] = 'B';
        map[0][MAP_HEIGHT - 3][2] = 'B';

        map[0][MAP_HEIGHT - 2][3] = 'P';    // ��Ʈ���̵� ���� �ϴ� ����
        map[0][MAP_HEIGHT - 2][4] = 'P';
        map[0][MAP_HEIGHT - 3][3] = 'P';
        map[0][MAP_HEIGHT - 3][4] = 'P';

        map[0][MAP_HEIGHT - 4][1] = 'H';    // ��Ʈ���̵� �Ϻ�����

        map[0][MAP_HEIGHT - 6][1] = '5';    // ���� ��� �����̽�

        map[0][5][MAP_WIDTH / 4] = 'W';     // �����

        map[0][MAP_HEIGHT - 6][7] = 'R';    // ��Ʈ���̵� ���� Rock

        // ���ڳ� ���� ��ġ (1�� ����)
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

        // ���� ��ġ
        map[0][MAP_HEIGHT - 4][MAP_WIDTH - 9] = 'R';

        map[0][7][MAP_WIDTH / 2 - 1] = 'R';
        map[0][7][MAP_WIDTH / 2] = 'R';
        map[0][8][MAP_WIDTH / 2 - 1] = 'R';
        map[0][8][MAP_WIDTH / 2] = 'R';

        map[0][MAP_HEIGHT - 7][MAP_WIDTH - MAP_WIDTH / 2 - 1] = 'R';
        map[0][MAP_HEIGHT - 7][MAP_WIDTH - MAP_WIDTH / 2] = 'R';
        map[0][MAP_HEIGHT - 8][MAP_WIDTH - MAP_WIDTH / 2 - 1] = 'R';
        map[0][MAP_HEIGHT - 8][MAP_WIDTH - MAP_WIDTH / 2] = 'R';

        initialized = true; // �ʱ�ȭ�� �Ϸ������� ǥ��
    }

    project(map, backbuf);  // ���� ���¸� backbuf�� ����

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int color = COLOR_DEFAULT;

            // 7�� ���� ������ ��� �ǹ��� ������ �Ķ������� ǥ��
            if ((i >= MAP_HEIGHT - 4 && i <= MAP_HEIGHT - 2) && (j >= 1 && j <= 4)) {
                if (backbuf[i][j] == 'B' || backbuf[i][j] == 'H' || backbuf[i][j] == 'b' || backbuf[i][j] == 'h') {
                    color = COLOR_PLAYER;
                }
            }
            // 1�� ���� ������ ��� �ǹ��� ������ ���������� ǥ��
            else if ((i >= 1 && i <= 3) && (j >= MAP_WIDTH - 5 && j <= MAP_WIDTH - 2)) {
                if (backbuf[i][j] == 'B' || backbuf[i][j] == 'H' || backbuf[i][j] == 'b' || backbuf[i][j] == 'h') {
                    color = COLOR_AI;
                }
            }
            else {
                // ������ �⺻ ���� ����
                switch (backbuf[i][j]) {
                case 'B': color = COLOR_PLAYER; break;   // �⺻ ���� ����
                case 'H': color = COLOR_AI; break;       // �⺻ �Ϻ����� ����
                case 'P': color = COLOR_PLATE; break;    // ���� ����
                case '5': color = COLOR_SPICE; break;    // �����̽� ����
                case 'W': color = COLOR_SANDWORM; break; // ����� ����
                case 'R': color = COLOR_ROCK; break;     // ���� ����
                case '#': color = COLOR_DEFAULT; break;  // ��輱 ����
                default: color = COLOR_DEFAULT; break;
                }
            }

            if (frontbuf[i][j] != backbuf[i][j]) {
                POSITION pos = { map_pos.row + i, map_pos.column + j };
                printc(pos, backbuf[i][j], color);  // �ش� ��ġ�� ���
            }
            frontbuf[i][j] = backbuf[i][j];  // frontbuf�� ���� ���� ���
        }
    }
}



// frontbuf[][]���� Ŀ�� ��ġ�� ���ڸ� ���� �ٲ㼭 �״�� �ٽ� ���
void display_cursor(CURSOR cursor){
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	printc(padd(map_pos, prev), ch, COLOR_DEFAULT);

	ch = frontbuf[curr.row][curr.column];
	printc(padd(map_pos, curr), ch, COLOR_CURSOR);
}