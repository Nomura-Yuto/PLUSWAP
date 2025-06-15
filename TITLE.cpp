//========================================
// �^�C�g�����W���[��
//========================================
#define CONIOEX
#include "MYlibrary.h"
#include "conioex.h"
#include "TITLE.h"

//========================================
// �O���[�o���ϐ�
//========================================
const char *title_name = "title.txt";	// �^�C�g����ʂ̃t�@�C����
char *ptitle;							// �^�C�g����ʓǂݍ��ݗp

const char *title_sound_name = "������  �A�R�[�X�e�B�b�N10.mp3";	// �^�C�g����ʂ�BGM
static int title_sound;

extern bool press_escape;	// ESC�L�[�������ꂽ���ǂ����̔���p(MYlibrary.cpp�Œ�`)
//========================================
// �����ݒ�
//========================================
void TitleInit(void) {
	press_escape = false;
	title_sound = opensound((char*)title_sound_name);
	TitleLoad(title_name);
}

//========================================
// �^�C�g���\��
//========================================
void TitleDraw(void) {
	CLS_CLEAR;
	playsound(title_sound, LOOP);
	for (int i = 0; i < WINDOW_SIZE_Y; i++) {
		for (int j = 0; j < WINDOW_SIZE_X; j++) {
			switch (ptitle[pTITLE_POS(i,j)]) {
			case '0':
				BACK_COLOR(GRAY);
				break;
			case '1':
				BACK_COLOR(RED);
				break;
			case '2':
				BACK_COLOR(VIOLET);
				break;
			case '3':
				BACK_COLOR(SKYBLUE);
				break;
			case '8':
				BACK_COLOR(SKYBLUE);
				break;
			case '9':
				BACK_COLOR(RED);
				break;
			default:
				BACK_COLOR(GRAY);
				break;
			}
			CURSOR_POS(TITLE_POS_Y + i + 1, TITLE_POS_X + j + 1);
			printf(" ");
		}
	}

	BACK_COLOR(SKYBLUE);
	TEXT_COLOR(RED);
	CURSOR_POS(28, 10);
	printf("[ SPACE ] �������Ă�������");
	RESET_COLOR;
}

//========================================
// �^�C�g����ʃA�b�v�f�[�g����
//========================================
void TitleUpdate(void) {
	while (true) {
		if (inport(PK_ESC)) {
			press_escape = true;
			break;
		}
		if (inport(PK_SP)) {
			break;
		}
	}
}
//========================================
// �I������
//========================================
void TitleEnd(void) {
	StopTitleSound();
	closesound(title_sound);
	free(ptitle);
}

//========================================
// �t�@�C������^�C�g����ǂݍ���
//========================================
void TitleLoad(const char* fname) {
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
		ptitle = (char *)calloc(size, sizeof(char));
		rewind(fp);
		for (i = 0; (*(ptitle + i) = (char)fgetc(fp)) != EOF; i++);
		ptitle[i] = '\0';
	}
	fclose(fp);
}

//========================================
// �^�C�g����ʂŗ���Ă���BGM���~�߂�
//========================================
void StopTitleSound(void) {
	stopsound(title_sound);
}