//========================================
// �v���C���[���W���[��
//========================================
#include "MYlibrary.h"
#include "conioex.h"
#include "PLAYER.h"
#include "FIELD.h"

//========================================
// �O���[�o���ϐ�
//========================================
PlayerStatus_t player;
bool player_escape;		// ESC�L�[�������ꂽ���A�S�[���������𔻕ʂ���p
bool type_swap;			// +��-���؂�ւ�������𔻕ʂ���p

extern char *pfield;	// field�ǂݍ��ݗp(FIELD.cpp�Œ�`)

int	move_x;		// �ړ������̔���p
int move_y;
//========================================
// �����ݒ�
//========================================
void PlayerInit(void) {

	char player_obj[PLAYER_SIZE_Y][PLAYER_SIZE_X+1] ={
		"������",
		"�|�{�|",
		"������",
	};
	memcpy(player.obj.strings, player_obj, sizeof(char) * PLAYER_SIZE_Y * (PLAYER_SIZE_X + 1));
	player.obj.width =	PLAYER_SIZE_X;
	player.obj.height = PLAYER_SIZE_Y;

	player.speed_y = PLAYER_SPEED_Y;
	player.speed_x = PLAYER_SPEED_X;

	player.pos_x =	PLAYER_STARTPOS_X + FIELD_POS_X;
	player.pos_y =	PLAYER_STARTPOS_Y + FIELD_POS_Y;
	player.next_x = player.pos_x;
	player.next_y = player.pos_y;

	player.goal = false;
	player.plus = true;

	player_escape = false;

	move_x = 0;
	move_y = 0;
}

//========================================
// �v���C���[�\��
//========================================
void PlayerDraw(void) {
	RESET_COLOR;
	for (int i = 0; i < player.obj.height; i++) {
		// ���ݒn�̃v���C���[���\��
		CURSOR_POS(player.pos_y+i, player.pos_x);
		printf("%*s", player.obj.width, "");
	}

	for (int i = 0; i < player.obj.height; i++) {
		// ���̈ړ��ʒu�Ƀv���C���[��\��
		CURSOR_POS(player.next_y+i, player.next_x);
		TEXT_COLOR(PLAYER_COLOR);
		printf("%s", player.obj.strings[i]);
		RESET_COLOR;
	}
	player.pos_x = player.next_x;
	player.pos_y = player.next_y;
}

//========================================
// �v���C���[�X�V����
//========================================
void PlayerUpdate(void) {
	move_x = 0;
	move_y = 0;

	if (inport(PK_ESC)) {
		player_escape = true;
		player.goal = false;
	}
	else {
		if (inport(PK_UP))		move_y = -1;
		if (inport(PK_DOWN))	move_y = 1;
		if (inport(PK_LEFT))	move_x = -1;
		if (inport(PK_RIGHT))	move_x = 1;

		player.next_x = player.pos_x + player.speed_x * move_x;
		player.next_y = player.pos_y + player.speed_y * move_y;

		if (PlayerCollision(&player)) {
			// �v���C���[�̐i�s�����ɉ������邩�̔���
			player.next_x = player.pos_x;
			player.next_y = player.pos_y;
		}
	}
}

//========================================
// �I������
//========================================
void PlayerEnd(void) {
	move_x = 0;
	move_y = 0;
}

//========================================
// �v���C���[�Փ˔���
//========================================
bool PlayerCollision(PlayerStatus_t *p) {
	bool check = false;
	type_swap = false;

	int	px0, px1, py0, py1;

	px0 = (int)p->next_x;						// �v���C���[�̍��[
	px1 = (int)p->next_x + p->obj.width - 1;	// �v���C���[�̉E�[
	py0 = (int)p->next_y;						// �v���C���[�̏�[
	py1 = (int)p->next_y + p->obj.height - 1;	// �v���C���[�̉��[

		
	for (int i = 0; i < PLAYER_SIZE_Y; i++) {
		for (int j = 0; j < PLAYER_SIZE_X; j++) {
			switch (pfield[pFIELD_POS(py0+i - FIELD_POS_Y, px0+j - FIELD_POS_X)]){
			// �i�ޕ����ɕǂȂǂ����邩�̔���
			case '0':
				check = true;
				break;
			case '1':
				check = true;
				break;
			case '+':
				check = true;
				break;
			case '-':
				check = true;
				break;
			case 'p':
				type_swap = true;
				player.plus = true;
				break;
			case 'm':
				type_swap = true;
				player.plus = false;
				break;
			case 'G':
				player_escape = true;
				player.goal = true;
				break;
			case 'g':
				player_escape = true;
				player.goal = true;
				break;
			case 'o':
				player_escape = true;
				player.goal = true;
				break;
			case 'a':
				player_escape = true;
				player.goal = true;
				break;
			case 'l':
				player_escape = true;
				player.goal = true;
				break;
			default:
				break;
			}
		}
	}
	return check;
}

//========================================
// �v���C���[�����\��
//========================================
void PlayerFirstDraw(void) {
	PlayerDraw();
}

//========================================
// ESC�L�[�������ꂽ�� �܂��� �S�[��������
//========================================
bool isPlayerEscape(void){
	return player_escape;
}

//========================================
// �{�Ɓ|���؂�ւ������
//========================================
bool isTypeSwap(void) {
	return type_swap;
}

//========================================
// ���݂̏�Ԃ��{�Ɓ|�̂ǂ�����
//========================================
bool isPlayerType(void) {
	return player.plus;
}

//========================================
// �v���C���[���S�[���ɒ�������
//========================================
bool isPlayerGoal(void) {
	return player.goal;
}

//========================================
// �v���C���[���ړ�������
//========================================
bool isPlayerMove(void) {
	if (move_x != 0 || move_y != 0)	return true;
	else	return false;
}