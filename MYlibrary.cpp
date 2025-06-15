//========================================
// コンソール制御モジュール
//========================================
#include "MYlibrary.h"



//========================================
// グローバル変数
//========================================
bool press_escape;  // ESCキーが押されたかどうかの判定用

//========================================
// コンソール画面のサイズの変更
//========================================
BOOL ChangeConsoleSize(int x, int y) {
    HANDLE hStdout;
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SMALL_RECT rectConsoleSize;
    rectConsoleSize.Left = 0;
    rectConsoleSize.Top = 0;
    rectConsoleSize.Right = 1;
    rectConsoleSize.Bottom = 1;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);

    if (!SetConsoleScreenBufferSize(hStdout, coord)) {
        return FALSE;
    }

    rectConsoleSize.Right = x - 1;
    rectConsoleSize.Bottom = y - 1;
    SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);
    return TRUE;
}


//========================================
// ESCキーが押されたかどうか
//========================================
bool isPressEscape(void) {
    return press_escape;
}

