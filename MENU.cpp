//========================================
// ���j���[���W���[��
//========================================
#define CONIOEX
#include "MYlibrary.h"
#include "conioex.h"
#include "MENU.h"

//========================================
// �O���[�o���ϐ�
//========================================
const char *menu_name = "menu.txt";
char *pmenu;
bool menu_escape;
Select_t select_num;

extern bool press_escape;	// ESC�L�[�������ꂽ���ǂ����̔���p(MYlibrary.cpp�Œ�`)
//========================================
// �����ݒ�
//========================================
void MenuInit(void) {
	select_num.now_x = 1;
	select_num.next_x = select_num.now_x;
	menu_escape = false;
	press_escape = false;
	MenuLoad(menu_name);
}

//========================================
// ���j���[��ʕ\��
//========================================
void MenuDraw(void) {
	for (int i = 0; i < WINDOW_SIZE_Y; i++) {
		for (int j = 0; j < WINDOW_SIZE_X; j++) {
			switch (pmenu[pMENU_POS(i,j)]) {
			case '0':
				BACK_COLOR(GRAY);
				break;
			case '1':
				BACK_COLOR(RED);
				break;
			case '2':
				BACK_COLOR(GREEN);
				break;
			case '3':
				BACK_COLOR(BLUE);
				break;
			case '9':
				BACK_COLOR(WHITE);
				break;
			case 'c':
				BACK_COLOR(ORANGE);
				break;
			default:
				BACK_COLOR(GRAY);
				break;
			}
			CURSOR_POS(MENU_POS_Y + i + 1, MENU_POS_X + j+1);
			printf(" ");
		}
	}
	TEXT_COLOR(RED);
	CURSOR_POS(WINDOW_SIZE_Y - 1, 40);
	printf("[ �� ] [ �� ] �F �ړ��@ [ SPACE ] �F���� ");
	RESET_COLOR;
}


//========================================
// ���j���[�A�b�v�f�[�g����
//========================================
void MenuUpdate(DWORD	record_time, DWORD	disp_time,DWORD disp_cnt) {
	while (!isMenuEscape()) {
		if (inport(PK_ESC)) {
			press_escape = true;
			menu_escape = true;
		}
		DWORD now_time = timeGetTime();
		if (now_time - record_time >= 1000 / MENU_FRAMERATE) {
			record_time = now_time;

#ifdef _DEBUG
			//FPS�\��
			if (now_time - disp_time >= 500) {
				TEXT_COLOR(WHITE);
				CURSOR_POS(1, 1);
				printf("FPS:%5.1f",((float)disp_cnt * 1000) / (now_time - disp_time));
				disp_time = now_time;
				disp_cnt = 0;
			}
			disp_cnt++;
#endif
			MenuSelect();
		}
	}
}

//========================================
// �I������
//========================================
void MenuEnd(void) {
	free(pmenu);
}

//========================================
// �t�@�C�����烁�j���[��ʂ�ǂݍ���
//========================================
void MenuLoad(const char* fname) {

	FILE *fp;

	int size;               // �������J�E���g�p
	char c;                 // �������͗p
	int	i; 

	size	= 0;

	fp = fopen(fname, "r");

	if (fp == NULL) {
		printf("%s���J���܂���",fname);
		exit(1);
	}
	else {
		rewind(fp);
		while ((c = getc(fp)) != EOF) {
			size++;
			if (c == '\n')size++;
		}
		pmenu = (char *)calloc(size, sizeof(char));
		rewind(fp);
		for (i = 0; (*(pmenu + i) = (char)fgetc(fp)) != EOF; i++);
		pmenu[i] = '\0';
	}

	fclose(fp);
}

//========================================
// �X�e�[�W�̑I��
//========================================
void MenuSelect(void) {
	int move = 0;
	int pos_x = 0;
	int pos_y = SELECTBOX_POS_Y - 1;

	if (inport(PK_SP)) {
		menu_escape = true;
	}
	else {
		if (inport(PK_LEFT))	move = -1;
		if (inport(PK_RIGHT))	move = 1;

		switch (select_num.next_x) {
		case 1:
			pos_x = SELECTBOX1_POS_X - 2;
			break;
		case 2:
			pos_x = SELECTBOX2_POS_X - 2;
			break;
		case 3:
			pos_x = SELECTBOX3_POS_X - 2;
			break;
		default:
			break;
		}
		BACK_COLOR(YELLOW);
		for (int i = 0; i < FRAME_SIZE_X; i++) {
			CURSOR_POS(pos_y, pos_x + i);
			printf(" ");
			CURSOR_POS(pos_y + SELECTBOX_SIZE_Y + 1, pos_x + i);
			printf(" ");
			CURSOR_POS(pos_y + (i / 2), pos_x);
			printf("  ");
			CURSOR_POS(pos_y + (i / 2), pos_x + SELECTBOX_SIZE_X + 2);
			printf("  ");
		}
		RESET_COLOR;
		if (move == 1 || move == -1) {
			switch (select_num.now_x) {
			case 1:
				pos_x = SELECTBOX1_POS_X - 2;
				break;
			case 2:
				pos_x = SELECTBOX2_POS_X - 2;
				break;
			case 3:
				pos_x = SELECTBOX3_POS_X - 2;
				break;
			default:
				break;
			}

			BACK_COLOR(GRAY);
			for (int i = 0; i < FRAME_SIZE_X; i++) {
				CURSOR_POS(pos_y, pos_x + i);
				printf(" ");
				CURSOR_POS(pos_y + SELECTBOX_SIZE_Y + 1, pos_x + i);
				printf(" ");
				CURSOR_POS(pos_y + (i / 2), pos_x);
				printf("  ");
				CURSOR_POS(pos_y + (i / 2), pos_x + SELECTBOX_SIZE_X + 2);
				printf("  ");
			}
			RESET_COLOR;
		}

		if (select_num.next_x == 1 && move <0) {
			move = 0;
		}
		if (select_num.next_x == 3 && move >0) {
			move = 0;
		}
		if (select_num.next_x >= 1 && select_num.next_x <=3 ) {
			select_num.next_x = select_num.now_x + 1 * move;
		}
		select_num.now_x = select_num.next_x;
	}
}

//========================================
// ���j���[���甲�������ǂ���
//========================================
bool isMenuEscape(void) {
	return menu_escape;
}


//========================================
// �I�������X�e�[�W�̔ԍ�
//========================================
int isSelectStage(void) {
	return (int)select_num.now_x;
}