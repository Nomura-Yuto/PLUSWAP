//========================================
// コンソール制御モジュール用ヘッダ
//========================================
#ifndef _MYLIBRARY_H_
#define _MYLIBRARY_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <digitalv.h>

#pragma comment(lib,"winmm.lib")

//========================================
// マクロ定義
//========================================
#define WINDOW_SIZE_Y 40
#define WINDOW_SIZE_X 120

#define RED			0xff,0x00,0x00
#define GREEN		0x00,0xff,0x00
#define BLUE		0x00,0x00,0xff
#define YELLOW		0xff,0xff,0x00
#define MAGENTA		0xff,0x00,0xff
#define CYAN		0x00,0xff,0xff

#define SKYBLUE		0x87,0xce,0xfa
#define	VIOLET		0xee,0x82,0xee
#define ORANGE		0xff,0xa5,0x00
#define DARKGREEN	0x00,0x80,0x00

#define BLACK		0x00,0x00,0x00
#define	GRAY		0x80,0x80,0x80
#define SILVER		0xc0,0xc0,0xc0
#define WHITE		0xff,0xff,0xff

#define TEXT_COLOR(x)	printf("\x1b[38;2;%d;%d;%dm",x)
#define BACK_COLOR(x)	printf("\x1b[48;2;%d;%d;%dm",x)
#define RESET_COLOR		printf("\x1b[0m")

#define CLS_CLEAR		printf("\x1B[2J")

#define CURSOR_ERASE	printf("\033[?25l")
#define CURSOR_INDICATE	printf("\033[?25h")
#define CURSOR_POS(y,x)		printf("\033[%d;%dH", (int)(y), (int)(x))

#define WAIT_ENTER	while(!inport(PK_ENTER))
#define WAIT_SPACE	while(!inport(PK_SP))

#define LOOP		1
#define NOT_LOOP	0
//========================================
// 関数プロトタイプ宣言
//========================================
BOOL ChangeConsoleSize(int x, int y);
bool isPressEscape(void);

#endif // !_MYLIBRARY_H_