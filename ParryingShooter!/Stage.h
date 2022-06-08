#pragma once

const int StageHeight = 11;
const int StageWeight = 21;

typedef struct _pos
{
	int x;
	int y;
}POS, *PPOS;

typedef struct _player
{
	_pos pos;
	bool isParryinged;
	int pHp = 3;
}PLAYER, *PPLAYER;

typedef struct _Bullet
{
	_pos bulletPos;
}BULLET, *PBULLET;

void SetStage(char Stage[StageHeight][StageWeight],PPLAYER pPlayer, PPOS pStartPos);
void DrawStage(char Stage[StageHeight][StageWeight], PPLAYER pPlayer);

void Parrying(char stage[StageHeight][StageWeight], PPLAYER pPlayer);

void BulletMove(char stage[StageHeight][StageWeight], PBULLET pBullet, PPLAYER pPlayer);

void PMoveDown(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
void PMoveUp(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
void PMoveLeft(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
void PMoveRight(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
void PlayerMove(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
