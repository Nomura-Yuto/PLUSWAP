//========================================
// プレイヤーモジュール用ヘッダー
//========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//========================================
// マクロ定義
//========================================
#define PLAYER_COLOR ORANGE

#define PLAYER_STARTPOS_X	2
#define PLAYER_STARTPOS_Y	26


#define PLAYER_SIZE_X 6
#define PLAYER_SIZE_Y 3

#define PLAYER_SPEED_X 0.5f
#define PLAYER_SPEED_Y 0.5f

//========================================
// 構造体
//========================================
typedef struct {
	char strings[PLAYER_SIZE_Y][PLAYER_SIZE_X + 1];
	int		width;
	int		height;
}Strings_t;

typedef struct {
	Strings_t	obj;	// プレイヤーの見た目
	float	speed_x;	// 移動スピード
	float	speed_y;
	float	pos_x;		// 現在地
	float	pos_y;
	float	next_x;		// 次に動く場所
	float	next_y;
	bool	goal;		// trueならゴールした  falseならESCが押された
	bool	plus;		// trueならプラス  falseならマイナス
}PlayerStatus_t;


//========================================
// 関数プロトタイプ宣言
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