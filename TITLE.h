//========================================
// �^�C�g�����W���[���p�w�b�_
//========================================
#ifndef _TITLE_H
#define _TITLE_H

//========================================
// �}�N����`
//========================================

#define TITLE_POS_X		0
#define TITLE_POS_Y		0

#define pTITLE_POS(y,x)	((y) * WINDOW_SIZE_X) + (x)	// ���j���[��ʂ̍��W�v�Z�p

//========================================
// �֐��v���g�^�C�v�錾
//========================================
void TitleInit(void);
void TitleDraw(void);
void TitleUpdate(void);
void TitleEnd(void);
void TitleLoad(const char *fname);
void StopTitleSound(void);

#endif // !_TITLE_H

