//========================================
// タイトルモジュール用ヘッダ
//========================================
#ifndef _TITLE_H
#define _TITLE_H

//========================================
// マクロ定義
//========================================

#define TITLE_POS_X		0
#define TITLE_POS_Y		0

#define pTITLE_POS(y,x)	((y) * WINDOW_SIZE_X) + (x)	// メニュー画面の座標計算用

//========================================
// 関数プロトタイプ宣言
//========================================
void TitleInit(void);
void TitleDraw(void);
void TitleUpdate(void);
void TitleEnd(void);
void TitleLoad(const char *fname);
void StopTitleSound(void);

#endif // !_TITLE_H

