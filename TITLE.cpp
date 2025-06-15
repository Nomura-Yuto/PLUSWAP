//========================================
// タイトルモジュール
//========================================
#define CONIOEX
#include "MYlibrary.h"
#include "conioex.h"
#include "TITLE.h"

//========================================
// グローバル変数
//========================================
const char *title_name = "title.txt";	// タイトル画面のファイル名
char *ptitle;							// タイトル画面読み込み用

const char *title_sound_name = "魔王魂  アコースティック10.mp3";	// タイトル画面のBGM
static int title_sound;

extern bool press_escape;	// ESCキーが押されたかどうかの判定用(MYlibrary.cppで定義)
//========================================
// 初期設定
//========================================
void TitleInit(void) {
	press_escape = false;
	title_sound = opensound((char*)title_sound_name);
	TitleLoad(title_name);
}

//========================================
// タイトル表示
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
	printf("[ SPACE ] を押してください");
	RESET_COLOR;
}

//========================================
// タイトル画面アップデート処理
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
// 終了処理
//========================================
void TitleEnd(void) {
	StopTitleSound();
	closesound(title_sound);
	free(ptitle);
}

//========================================
// ファイルからタイトルを読み込む
//========================================
void TitleLoad(const char* fname) {
	FILE *fp;

	int size;               // 文字数カウント用
	char c;                 // 文字入力用
	int	i; 

	size	= 0;

	fp = fopen(fname, "r");

	if (fp == NULL) {
		printf("%sが開けません",fname);
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
// タイトル画面で流れているBGMを止める
//========================================
void StopTitleSound(void) {
	stopsound(title_sound);
}