//========================================
// �v���C���[���W���[���p�w�b�_�[
//========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//========================================
// �}�N����`
//========================================
#define PLAYER_COLOR ORANGE

#define PLAYER_STARTPOS_X	2
#define PLAYER_STARTPOS_Y	26


#define PLAYER_SIZE_X 6
#define PLAYER_SIZE_Y 3

#define PLAYER_SPEED_X 0.5f
#define PLAYER_SPEED_Y 0.5f

//========================================
// �\����
//========================================
typedef struct {
	char strings[PLAYER_SIZE_Y][PLAYER_SIZE_X + 1];
	int		width;
	int		height;
}Strings_t;

typedef struct {
	Strings_t	obj;	// �v���C���[�̌�����
	float	speed_x;	// �ړ��X�s�[�h
	float	speed_y;
	float	pos_x;		// ���ݒn
	float	pos_y;
	float	next_x;		// ���ɓ����ꏊ
	float	next_y;
	bool	goal;		// true�Ȃ�S�[������  false�Ȃ�ESC�������ꂽ
	bool	plus;		// true�Ȃ�v���X  false�Ȃ�}�C�i�X
}PlayerStatus_t;


//========================================
// �֐��v���g�^�C�v�錾
//========================================
void PlayerInit(void);
void PlayerDraw(void);
void PlayerUpdate(void);
void PlayerEnd(void);
bool PlayerCollision(PlayerStatus_t *p);
void PlayerFirstDraw(void);
bool isPlayerEscape(void);
bool isTypeSwap(void);
bool isPlayerType(void);
bool isPlayerGoal(void);
bool isPlayerMove(void);

#endif // !_PLAYER_H_