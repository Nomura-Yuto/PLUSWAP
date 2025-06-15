//========================================
// ���j���[���W���[���p�w�b�_
//========================================
#ifndef _MENU_H
#define _MENU_H

//========================================
// �}�N����`
//========================================
#define MENU_FRAMERATE 12	// ���j���[��ʂ̃t���[�����[�g

#define SELECTBOX_SIZE_Y	12
#define SELECTBOX_SIZE_X	24
#define FRAME_SIZE_Y	SELECTBOX_SIZE_Y + 2
#define FRAME_SIZE_X	SELECTBOX_SIZE_X + 4

#define SELECTBOX_POS_Y		23
#define SELECTBOX1_POS_X	13
#define SELECTBOX2_POS_X	49
#define SELECTBOX3_POS_X	85

#define SELECT_SPEED 0.1f

#define MENU_POS_X		0
#define MENU_POS_Y		0

#define pMENU_POS(y,x)	((y) * WINDOW_SIZE_X) + (x)	// ���j���[��ʂ̍��W�v�Z�p

//========================================
// �\����
//========================================
typedef struct {
	int now_x;
	int next_x;
}Select_t;

//========================================
// �֐��v���g�^�C�v�錾
//========================================
void MenuInit(void);
void MenuDraw(void);
void MenuUpdate(DWORD	record_time, DWORD	disp_time, DWORD disp_cnt);
void MenuEnd(void);
void MenuLoad(const char *fname);
void MenuSelect(void);
bool isMenuEscape(void);
int isSelectStage(void);
#endif // !_MENU_H

