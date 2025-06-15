#define CONIOEX

#include "MYlibrary.h"
#include "conioex.h"
#include "TITLE.h"
#include "MENU.h"
#include "FIELD.h"
#include "PLAYER.h"
#include "RESULT.h"

//========================================
// �}�N����`
//========================================
#define GAME_FRAMERATE 45	// �Q�[�����̃t���[�����[�g

//========================================
// �O���[�o���ϐ�
//========================================
static DWORD	record_time;			// FPS����p�̕ϐ�
static DWORD	disp_time,disp_cnt;		// FPS�\���p�̕ϐ�

static DWORD	elapsed_record_time;	// 1�b�J�E���g�p�̕ϐ�
static DWORD	update_time;			// �^�C�}�[�p�̕ϐ�

//========================================
// �֐��v���g�^�C�v�錾
//========================================
void Init(void);
void End(void);
void Update(void);
void Draw(void);
void Title(void);
void Menu(void);
void Result(void);

//========================================
// ���C���֐�
//========================================
int main(void)
{
	bool end = false;
	bool stage_select = false;
	//system("cls");
	ChangeConsoleSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	
	while (!end) {	// �Q�[�����[�v
		end = false;
		if (inport(PK_ESC)) {
			end = true;
		}
		else {
			Init();
			Title();
			if (isPressEscape()) break;
			Menu();
			if (isPressEscape()) break;

			PlayFieldBGM();
			FieldFirstDraw();
			PlayerFirstDraw();
			while (!isPlayerEscape()) {
				DWORD now_time = timeGetTime();
				if (now_time - elapsed_record_time >= 1000) {
					// �^�C�}�[�\��
					elapsed_record_time = now_time;
					update_time++;
					CURSOR_POS(FIELD_POS_Y,FIELD_POS_X + FIELD_SIZE_X + 2);
					TEXT_COLOR(RED);
					clreol();
					printf("TIME  %02d�F%02d", update_time / 60, update_time % 60);
				}
				if (now_time - record_time >= 1000 / GAME_FRAMERATE) {
					record_time = now_time;

#ifdef _DEBUG
					if (now_time - disp_time >= 500) {
						// FPS�\��
						TEXT_COLOR(WHITE);
						CURSOR_POS(1, 1);
						printf("FPS:%5.1f", ((float)disp_cnt * 1000) / (now_time - disp_time));
						disp_time = now_time;
						disp_cnt = 0;
					}
					disp_cnt++;
#endif
					Update();
					if (isPlayerMove()) {
						// �v���C���[����������
						Draw();
					}
					if (isPlayerGoal()) {
						// �v���C���[���S�[���ɓ��B������
						StopFieldSound();
						Result();
						if (isPressEscape()) end = true;
						break;
					}
				}
			}
			End();
		}
	}

	CLS_CLEAR;
	RESET_COLOR;
	CURSOR_INDICATE;
	rewind(stdin);
	_getch();

	return 0;
}

void Init(void) {
	CURSOR_ERASE;
	RESET_COLOR;
	CLS_CLEAR;
	timeBeginPeriod(1);
	reinport();
	update_time = 0;

	FieldInit();
	PlayerInit();
	ResultInit();
}

void End(void) {
	timeEndPeriod(1);
	CLS_CLEAR;
	RESET_COLOR;
	CURSOR_INDICATE;


	FieldEnd();
	PlayerEnd();
	ResultEnd();
}

void Update(void) {
	PlayerUpdate();
}

void Draw(void) {
	if (isTypeSwap()) {
		FieldLoad(isSelectStage() -1);
		FieldDraw();
	}		
	PlayerDraw();
}
void Title(void) {
	TitleInit();
	TitleDraw();
	TitleUpdate();
}

void Menu(void) {
	MenuInit();
	MenuDraw();
	MenuUpdate(record_time, disp_time, disp_cnt);
	TitleEnd();
	MenuEnd();
}

void Result(void) {
	RecordTime(update_time);
	ResultDraw();
	ResultUpdate();
	StopResultSound();
}