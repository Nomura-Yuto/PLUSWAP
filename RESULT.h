//===================
// =====================
// リザルトモジュール用ヘッダ
//========================================
#ifndef _RESULT_H
#define _RESULT_H
//========================================
// マクロ定義
//========================================
#define CLEAR_TIME_COLOR CYAN
#define NUM_SIZE_X	6
#define NUM_SIZE_Y	6
#define DOT_SIZE_X	4
#define DOT_SIZE_Y	2

#define TENSPLACE	0
#define ONESPLACE	1

#define MINUTE_TENSPLACE_POS_X		41
#define MINUTE_ONESPLACE_POS_X		MINUTE_TENSPLACE_POS_X + NUM_SIZE_X + 2
#define SECONDS_TENSPLACE_POS_X		66
#define SECONDS_ONESPLACE_POS_X		SECONDS_TENSPLACE_POS_X + NUM_SIZE_X + 2
#define NUMBER_POS_Y				29

#define DOT_POS_X		59
#define DOT_TOP_POS_Y	29
#define DOT_UNDER_POS_Y	DOT_TOP_POS_Y + DOT_SIZE_Y + 1


#define RESULT_POS_X		0
#define RESULT_POS_Y		0

#define pRESULT_POS(y,x)	((y) * WINDOW_SIZE_X) + (x)	// リザルト画面の座標計算用


//========================================
// 構造体
//========================================
typedef struct {
	int number;
	int pos_x;
	int pos_y;
}Number_t;

typedef struct {
	Number_t minute[2];
	Number_t seconds[2];
}Time_t;
//========================================
// 関数プロトタイプ宣言
//========================================
void ResultInit(void);
void ResultDraw(void);
void ResultUpdate(void);
void ResultEnd(void);
void ResultLoad(const char *fname);
void RecordTime(DWORD update_time);
void PrintNum(int number, int pos_x, int pos_y);
void StopResultSound(void);

#endif // !_RESULT_H
