//========================================
// ���U���g���W���[��
//========================================
#define CONIOEX
#include "MYlibrary.h"
#include "conioex.h"
#include "RESULT.h"

//========================================
// �O���[�o���ϐ�
//========================================
const char *result_name = "result.txt";	// ���U���g��ʂ̃t�@�C����
char *presult;					// ���U���g��ʓǂݍ��ݗp
Time_t clear_time;				// �N���A�^�C���ۑ��p

const char *result_sound_name = "������  ����14.mp3";		// ���U���g��ʂ�BGM
static int result_sound;

extern bool press_escape;	// ESC�L�[�������ꂽ���ǂ����̔���p(MYlibrary.cpp�Œ�`)

// �����̃A�X�L�[�A�[�g
char num[10][NUM_SIZE_Y][NUM_SIZE_X+1] = {
	{
		"������",
		"��  ��",
		"��  ��",
		"��  ��",
		"������",
	},
	{
		"    ��",
		"    ��",
		"    ��",
		"    ��",
		"    ��",
	},
	{
		"������",
		"    ��",
		"������",
		"��    ",
		"������",
	},
	{
		"������",
		"    ��",
		"������",
		"    ��",
		"������",
	},
	{
		"��  ��",
		"��  ��",
		"������",
		"    ��",
		"    ��",
	},
	{
		"������",
		"��    ",
		"������",
		"    ��",
		"������",
	},
	{
		"������",
		"��    ",
		"������",
		"��  ��",
		"������",
	},
	{
		"������",
		"��  ��",
		"    ��",
		"    ��",
		"    ��",
	},
	{
		"������",
		"��  ��",
		"������",
		"��  ��",
		"������",
	},
	{
		"������",
		"��  ��",
		"������",
		"    ��",
		"������",
	},
};
// �R����(�F)�p�̃h�b�g
char dot[DOT_SIZE_Y][DOT_SIZE_X + 1] = {
	"����",
	"����"
};

//========================================
// �����ݒ�
//========================================
void ResultInit(void) {
	result_sound = opensound((char*)result_sound_name);
	clear_time = {
		0,
		0
	};
	clear_time.minute[TENSPLACE] = {
		0,
		MINUTE_TENSPLACE_POS_X,
		NUMBER_POS_Y
	};
	clear_time.minute[ONESPLACE] = {
		0,
		MINUTE_ONESPLACE_POS_X,
		NUMBER_POS_Y
	};
	clear_time.seconds[TENSPLACE] = {
		0,
		SECONDS_TENSPLACE_POS_X,
		NUMBER_POS_Y
	};
	clear_time.seconds[ONESPLACE] = {
		0,
		SECONDS_ONESPLACE_POS_X,
		NUMBER_POS_Y
	};

	ResultLoad(result_name);
}

//========================================
// ���U���g��ʕ\��
//========================================
void ResultDraw(void) {
	CLS_CLEAR;
	playsound(result_sound, LOOP);
	for (int i = 0; i < WINDOW_SIZE_Y; i++) {
		for (int j = 0; j < WINDOW_SIZE_X; j++) {
			switch (presult[pRESULT_POS(i,j)]) {
			case '0':
				BACK_COLOR(GRAY);
				break;
			case '1':
				BACK_COLOR(RED);
				break;
			case '2':
				BACK_COLOR(BLUE);
				break;
			case 'n':
				BACK_COLOR(GRAY);
				break;
			case 'd':
				BACK_COLOR(GRAY);
				break;
			default:
				BACK_COLOR(GRAY);
				break;
			}
			CURSOR_POS(RESULT_POS_Y + i + 1, RESULT_POS_X + j+1);
			printf(" ");
		}
	}

	TEXT_COLOR(CLEAR_TIME_COLOR);
	PrintNum(clear_time.minute[TENSPLACE].number,		// ��(�\�̈�)�̕\��
		clear_time.minute[TENSPLACE].pos_x, clear_time.minute[TENSPLACE].pos_y);
	PrintNum(clear_time.minute[ONESPLACE].number, 		// ��(��̈�)�̕\��
		clear_time.minute[ONESPLACE].pos_x, clear_time.minute[ONESPLACE].pos_y);
	PrintNum(clear_time.seconds[TENSPLACE].number, 		// �b(�\�̈�)�̕\��
		clear_time.seconds[TENSPLACE].pos_x, clear_time.seconds[TENSPLACE].pos_y);
	PrintNum(clear_time.seconds[ONESPLACE].number, 		// �b(��̈�)�̕\��
		clear_time.seconds[ONESPLACE].pos_x, clear_time.seconds[ONESPLACE].pos_y);

	for (int i = 0; i < DOT_SIZE_Y; i++) {
		CURSOR_POS(DOT_TOP_POS_Y + i, DOT_POS_X);
		printf("%s", dot[i]);
	}
	for (int i = 0; i < DOT_SIZE_Y; i++) {
		CURSOR_POS(DOT_UNDER_POS_Y + i, DOT_POS_X);
		printf("%s", dot[i]);
	}
	TEXT_COLOR(RED);
	CURSOR_POS(WINDOW_SIZE_Y - 1, 40);
	printf("[ SPACE ] �������ă^�C�g���ɖ߂� ");
	RESET_COLOR;
}

//========================================
// ���U���g��ʃA�b�v�f�[�g����
//========================================
void ResultUpdate(void) {
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
void ResultEnd(void) {
	StopResultSound();
	closesound(result_sound);
	free(presult);
}

//========================================
// �t�@�C�����烊�U���g��ʂ�ǂݍ���
//========================================
void ResultLoad(const char* fname) {

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
		presult = (char *)calloc(size, sizeof(char));
		rewind(fp);
		for (i = 0; (*(presult + i) = (char)fgetc(fp)) != EOF; i++);
		presult[i] = '\0';
	}

	fclose(fp);
};

//========================================
// �N���A�^�C���̋L�^
//========================================
void RecordTime(DWORD update_time) {
	clear_time.minute[TENSPLACE].number = (update_time / 60) / 10;		// ��(�\�̈�)�̕ۑ�
	clear_time.minute[ONESPLACE].number = (update_time / 60) % 10;		// ��(��̈�)�̕ۑ�
	clear_time.seconds[TENSPLACE].number = (update_time % 60) / 10;		// �b(�\�̈�)�̕ۑ�
	clear_time.seconds[ONESPLACE].number = (update_time % 60) % 10;		// �b(��̈�)�̕ۑ�
}

//========================================
// �����̕\��
//========================================
void PrintNum(int number, int pos_x, int pos_y) {
	for (int i = 0; i < NUM_SIZE_Y; i++) {
		CURSOR_POS(pos_y + i, pos_x);
		printf("%s", num[number][i]);
	}
}

//========================================
// ���U���g��ʂŗ���Ă���BGM���~�߂�
//========================================
void StopResultSound(void) {
	stopsound(result_sound);
}
