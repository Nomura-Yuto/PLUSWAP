//========================================
// �R���\�[�����䃂�W���[��
//========================================
#include "MYlibrary.h"



//========================================
// �O���[�o���ϐ�
//========================================
bool press_escape;  // ESC�L�[�������ꂽ���ǂ����̔���p

//========================================
// �R���\�[����ʂ̃T�C�Y�̕ύX
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
// ESC�L�[�������ꂽ���ǂ���
//========================================
bool isPressEscape(void) {
    return press_escape;
}

