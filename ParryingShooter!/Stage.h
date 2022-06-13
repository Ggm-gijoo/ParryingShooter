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

typedef struct _Shield
{
	_pos shieldPos;
}SHIELD, *PSHIELD;

typedef struct _Bullet
{
	_pos bulletPos;
}BULLET, *PBULLET;

typedef struct _Boss
{
	_pos bossPos;
	int bHp = 10;
}BOSS, *PBOSS;

void SetStage(char Stage[StageHeight][StageWeight],PPLAYER pPlayer, PBOSS pBoss, PPOS pStartPos, PPOS pBossPos);
void DrawStage(char Stage[StageHeight][StageWeight], PPLAYER pPlayer, PBOSS pBoss, PBULLET pBullet);

void Parrying(char stage[StageHeight][StageWeight], PPLAYER pPlayer);

void BulletMove(char stage[StageHeight][StageWeight], PBULLET pBullet, PPLAYER pPlayer, PSHIELD pShield);
void BossFire(char stage[StageHeight][StageWeight], PBOSS pBoss, PPLAYER pPlayer, PSHIELD pShield);

void PMoveDown(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
void PMoveUp(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
void PMoveLeft(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
void PMoveRight(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
void PlayerMove(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
