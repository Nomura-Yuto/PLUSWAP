//========================================
// リザルトモジュール
//========================================
#define CONIOEX
#include "MYlibrary.h"
#include "conioex.h"
#include "RESULT.h"

//========================================
// グローバル変数
//========================================
const char *result_name = "result.txt";	// リザルト画面のファイル名
char *presult;					// リザルト画面読み込み用
Time_t clear_time;				// クリアタイム保存用

const char *result_sound_name = "魔王魂  民族14.mp3";		// リザルト画面のBGM
static int result_sound;

extern bool press_escape;	// ESCキーが押されたかどうかの判定用(MYlibrary.cppで定義)

// 数字のアスキーアート
char num[10][NUM_SIZE_Y][NUM_SIZE_X+1] = {
	{
		"■■■",
		"■  ■",
		"■  ■",
		"■  ■",
		"■■■",
	},
	{
		"    ■",
		"    ■",
		"    ■",
		"    ■",
		"    ■",
	},
	{
		"■■■",
		"    ■",
		"■■■",
		"■    ",
		"■■■",
	},
	{
		"■■■",
		"    ■",
		"■■■",
		"    ■",
		"■■■",
	},
	{
		"■  ■",
		"■  ■",
		"■■■",
		"    ■",
		"    ■",
	},
	{
		"■■■",
		"■    ",
		"■■■",
		"    ■",
		"■■■",
	},
	{
		"■■■",
		"■    ",
		"■■■",
		"■  ■",
		"■■■",
	},
	{
		"■■■",
		"■  ■",
		"    ■",
		"    ■",
		"    ■",
	},
	{
		"■■■",
		"■  ■",
		"■■■",
		"■  ■",
		"■■■",
	},
	{
		"■■■",
		"■  ■",
		"■■■",
		"    ■",
		"■■■",
	},
};
// コロン(：)用のドット
char dot[DOT_SIZE_Y][DOT_SIZE_X + 1] = {
	"■■",
	"■■"
};

//========================================
// 初期設定
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
// リザルト画面表示
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
	PrintNum(clear_time.minute[TENSPLACE].number,		// 分(十の位)の表示
		clear_time.minute[TENSPLACE].pos_x, clear_time.minute[TENSPLACE].pos_y);
	PrintNum(clear_time.minute[ONESPLACE].number, 		// 分(一の位)の表示
		clear_time.minute[ONESPLACE].pos_x, clear_time.minute[ONESPLACE].pos_y);
	PrintNum(clear_time.seconds[TENSPLACE].number, 		// 秒(十の位)の表示
		clear_time.seconds[TENSPLACE].pos_x, clear_time.seconds[TENSPLACE].pos_y);
	PrintNum(clear_time.seconds[ONESPLACE].number, 		// 秒(一の位)の表示
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
	printf("[ SPACE ] を押してタイトルに戻る ");
	RESET_COLOR;
}

//========================================
// リザルト画面アップデート処理
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
// 終了処理
//========================================
void ResultEnd(void) {
	StopResultSound();
	closesound(result_sound);
	free(presult);
}

//========================================
// ファイルからリザルト画面を読み込む
//========================================
void ResultLoad(const char* fname) {

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
		presult = (char *)calloc(size, sizeof(char));
		rewind(fp);
		for (i = 0; (*(presult + i) = (char)fgetc(fp)) != EOF; i++);
		presult[i] = '\0';
	}

	fclose(fp);
};

//========================================
// クリアタイムの記録
//========================================
void RecordTime(DWORD update_time) {
	clear_time.minute[TENSPLACE].number = (update_time / 60) / 10;		// 分(十の位)の保存
	clear_time.minute[ONESPLACE].number = (update_time / 60) % 10;		// 分(一の位)の保存
	clear_time.seconds[TENSPLACE].number = (update_time % 60) / 10;		// 秒(十の位)の保存
	clear_time.seconds[ONESPLACE].number = (update_time % 60) % 10;		// 秒(一の位)の保存
}

//========================================
// 数字の表示
//========================================
void PrintNum(int number, int pos_x, int pos_y) {
	for (int i = 0; i < NUM_SIZE_Y; i++) {
		CURSOR_POS(pos_y + i, pos_x);
		printf("%s", num[number][i]);
	}
}

//========================================
// リザルト画面で流れているBGMを止める
//========================================
void StopResultSound(void) {
	stopsound(result_sound);
}
