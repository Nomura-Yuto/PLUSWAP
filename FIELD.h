//========================================
// フィールドモジュール用ヘッダ
//========================================
#ifndef _FIELD_H_
#define _FIELD_H_

//========================================
// マクロ定義
//========================================
#define FIELD_MAX	3

#define FIELD_POS_X		3
#define FIELD_POS_Y		2
#define FIELD_SIZE_X	60
#define FIELD_SIZE_Y	30

#define pFIELD_POS(y,x)	((y) * FIELD_SIZE_X) + (x) // フィールドの座標計算用

//========================================
// 構造体
//========================================
typedef struct {
	const char *plus;
	const char *minus;
}Type_t;

//========================================
// 関数プロトタイプ宣言
//========================================
void FieldInit(void);
void FieldDraw(void);
void FieldEnd(void);
void FieldLoad(int num);
void FieldFirstDraw(void);
void PlayFieldBGM(void);
void StopFieldSound(void);
#endif // !_FIELD_H_