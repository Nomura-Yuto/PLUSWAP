//========================================
// �t�B�[���h���W���[��
//========================================
#define CONIOEX

#include "MYlibrary.h"
#include "conioex.h"
#include "MENU.h"
#include "FIELD.h"
#include "PLAYER.h"

//========================================
// �O���[�o���ϐ�
//========================================
Type_t field_name[FIELD_MAX];	// �t�@�C���������邽�߂̍\���̔z��
char *pfield;					// �t�B�[���h�ǂݍ��ݗp

const char *field_sound_name = "������  ����13.mp3";					// �t�B�[���h�ŗ����BGM
static int field_sound;
const char *field_swap_sound_name = "������ ���ʉ� �V�X�e��44.mp3";		// �t�B�[���h���؂�ւ�������̌��ʉ�
static int field_swap_sound;
//========================================
// �����ݒ�
//========================================
void FieldInit(void) {
	field_sound = opensound((char*)field_sound_name);
	field_swap_sound = opensound((char*)field_swap_sound_name);
	field_name[0] = {	// field1�̃t�@�C����
		"field1_plus.txt",
		"field1_minus.txt"
	};
	field_name[1] = {	// field2�̃t�@�C����
		"field2_plus.txt",
		"field2_minus.txt"
	};
	field_name[2] = {	// field3�̃t�@�C����
		"field3_plus.txt",
		"field3_minus.txt"
	};
}

//========================================
// �t�B�[���h�\��
//========================================
void FieldDraw(void) {
	playsound(field_swap_sound, NOT_LOOP);
	for (int i = 0; i < FIELD_SIZE_Y; i++) {
		for (int j = 0; j < FIELD_SIZE_X; j++) {
			switch (pfield[pFIELD_POS(i,j)]) {
			case '0':
				BACK_COLOR(WHITE);
				break;
			case '1':
				BACK_COLOR(RED);
				break;
			case '2':
				BACK_COLOR(BLACK);
				break;
			case '+':
				BACK_COLOR(RED);
				CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
				printf("�{");
				j++;
				break;			
			case '-':
				BACK_COLOR(RED);
				CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
				printf("�[");
				j++;
				break;
			case 'p':
				BACK_COLOR(GREEN);
				TEXT_COLOR(RED);
				CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
				printf("�{");
				j++;
				break;
			case 'm':
				BACK_COLOR(GREEN);
				TEXT_COLOR(RED);
				CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
				printf("�[");
				j++;
				break;
			case 'G':
				BACK_COLOR(MAGENTA);
				break;
			case 'g':
				BACK_COLOR(MAGENTA);
				CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
				printf("G");
				continue;
				break;
			case 'o':
				BACK_COLOR(MAGENTA);
				CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
				printf("O");
				continue;
				break;
			case 'a':
				BACK_COLOR(MAGENTA);
				CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
				printf("A");
				continue;
				break;
			case 'l':
				BACK_COLOR(MAGENTA);
				CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
				printf("L");
				continue;
				break;
			default:
				break;
			}
			CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
			printf(" ");
			RESET_COLOR;
		}
	}
	TEXT_COLOR(RED);
	CURSOR_POS(FIELD_POS_Y + FIELD_SIZE_Y + 1, FIELD_POS_X);
	printf("[ �� ] [ �� ] [ �� ] [ �� ] �F �ړ�");
	RESET_COLOR;
}


//========================================
// �I������
//========================================
void FieldEnd(void) {
	StopFieldSound();
	closesound(field_sound);
	closesound(field_swap_sound);
	free(pfield);
}

//========================================
// �t�@�C������t�B�[���h��ǂݍ���
//========================================
void FieldLoad(int num) {

	FILE *fp;
	const char *fname;
	

	int size;               // �������J�E���g�p
	char c = 0;             // �������͗p
	int	i; 

	size	= 0;
	if (isPlayerType()) {
		fname = field_name[num].plus;
	}
	else {
		fname = field_name[num].minus;
	}
	fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("%s���J���܂���",fname);
		exit(1);
	}
	else {
		while ((c = getc(fp)) != EOF) {
			size++;
			if (c == '\n')size++;
		}
		pfield = (char *)calloc(size, sizeof(char));
		rewind(fp);
		for (i = 0; (*(pfield + i) = (char)fgetc(fp)) != EOF; i++) {
			if (*(pfield + i) == '\n') {
				*(pfield + i) = *(pfield + i - 1);
			}
		}
		pfield[i] = '\0';
	}

	fclose(fp);
}

//========================================
// �t�B�[���h�����\��
//========================================
void FieldFirstDraw(void) {
	CLS_CLEAR;
	FieldLoad(isSelectStage() -1);
	FieldDraw();
}

//========================================
// �t�B�[���h�ŗ���Ă���BGM���~�߂�
//========================================
void PlayFieldBGM(void) {
	playsound(field_sound, LOOP);
}

//========================================
// �t�B�[���h�ŗ���Ă���BGM���~�߂�
//========================================
void StopFieldSound(void) {
	stopsound(field_sound);
}