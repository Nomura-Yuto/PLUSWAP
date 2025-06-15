//========================================
// フィールドモジュール
//========================================
#define CONIOEX

#include "MYlibrary.h"
#include "conioex.h"
#include "MENU.h"
#include "FIELD.h"
#include "PLAYER.h"

//========================================
// グローバル変数
//========================================
Type_t field_name[FIELD_MAX];	// ファイル名を入れるための構造体配列
char *pfield;					// フィールド読み込み用

const char *field_sound_name = "魔王魂  民族13.mp3";					// フィールドで流れるBGM
static int field_sound;
const char *field_swap_sound_name = "魔王魂 効果音 システム44.mp3";		// フィールドが切り替わった時の効果音
static int field_swap_sound;
//========================================
// 初期設定
//========================================
void FieldInit(void) {
	field_sound = opensound((char*)field_sound_name);
	field_swap_sound = opensound((char*)field_swap_sound_name);
	field_name[0] = {	// field1のファイル名
		"field1_plus.txt",
		"field1_minus.txt"
	};
	field_name[1] = {	// field2のファイル名
		"field2_plus.txt",
		"field2_minus.txt"
	};
	field_name[2] = {	// field3のファイル名
		"field3_plus.txt",
		"field3_minus.txt"
	};
}

//========================================
// フィールド表示
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
				printf("＋");
				j++;
				break;			
			case '-':
				BACK_COLOR(RED);
				CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
				printf("ー");
				j++;
				break;
			case 'p':
				BACK_COLOR(GREEN);
				TEXT_COLOR(RED);
				CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
				printf("＋");
				j++;
				break;
			case 'm':
				BACK_COLOR(GREEN);
				TEXT_COLOR(RED);
				CURSOR_POS(FIELD_POS_Y+i,FIELD_POS_X+ j);
				printf("ー");
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
	printf("[ ← ] [ → ] [ ↑ ] [ ↓ ] ： 移動");
	RESET_COLOR;
}


//========================================
// 終了処理
//========================================
void FieldEnd(void) {
	StopFieldSound();
	closesound(field_sound);
	closesound(field_swap_sound);
	free(pfield);
}

//========================================
// ファイルからフィールドを読み込む
//========================================
void FieldLoad(int num) {

	FILE *fp;
	const char *fname;
	

	int size;               // 文字数カウント用
	char c = 0;             // 文字入力用
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
		printf("%sが開けません",fname);
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
// フィールド初期表示
//========================================
void FieldFirstDraw(void) {
	CLS_CLEAR;
	FieldLoad(isSelectStage() -1);
	FieldDraw();
}

//========================================
// フィールドで流れているBGMを止める
//========================================
void PlayFieldBGM(void) {
	playsound(field_sound, LOOP);
}

//========================================
// フィールドで流れているBGMを止める
//========================================
void StopFieldSound(void) {
	stopsound(field_sound);
}