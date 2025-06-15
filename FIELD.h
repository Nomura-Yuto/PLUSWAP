//========================================
// �t�B�[���h���W���[���p�w�b�_
//========================================
#ifndef _FIELD_H_
#define _FIELD_H_

//========================================
// �}�N����`
//========================================
#define FIELD_MAX	3

#define FIELD_POS_X		3
#define FIELD_POS_Y		2
#define FIELD_SIZE_X	60
#define FIELD_SIZE_Y	30

#define pFIELD_POS(y,x)	((y) * FIELD_SIZE_X) + (x) // �t�B�[���h�̍��W�v�Z�p

//========================================
// �\����
//========================================
typedef struct {
	const char *plus;
	const char *minus;
}Type_t;

//========================================
// �֐��v���g�^�C�v�錾
//========================================
void FieldInit(void);
void FieldDraw(void);
void FieldEnd(void);
void FieldLoad(int num);
void FieldFirstDraw(void);
void PlayFieldBGM(void);
void StopFieldSound(void);
#endif // !_FIELD_H_