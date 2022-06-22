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
	bool isParryinged = false;
	int pHp = 3;
}PLAYER, *PPLAYER;

typedef struct _Shield
{
	_pos shieldPos;
}SHIELD, *PSHIELD;

typedef struct _Bullet
{
	_pos bulletPos;
	int color = 4;
	bool isPar = false;
}BULLET, *PBULLET;

typedef struct _Boss
{
	_pos bossPos;
	int bHp = 7;
}BOSS, *PBOSS;

void SetStage(char Stage[StageHeight][StageWeight],PPLAYER pPlayer, PBOSS pBoss, PPOS pStartPos, PPOS pBossPos);
void DrawStage(char Stage[StageHeight][StageWeight], PPLAYER pPlayer, PBOSS pBoss, PSHIELD pShield);
bool Check(int x, int y);

void Parrying(char stage[StageHeight][StageWeight], PPLAYER pPlayer, PSHIELD pShield, PBOSS pBoss);
void DestroyParrying(PPLAYER pPlayer, PSHIELD pShield);

void BulletMove(char stage[StageHeight][StageWeight], PPLAYER pPlayer, PSHIELD pShield, PBOSS pBoss);
BULLET *BossInstantiateBullet(PBOSS pBoss, PPLAYER pPlayer);
void BossFire(PBOSS pBoss, PPLAYER pPlayer);

bool PlayerDie(PPLAYER pPlayer);
bool PlayerWin(PBOSS pBoss);

void PMoveDown(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
void PMoveUp(char stage[StageHeight][StageWeight], PPLAYER pPlayer);
void PlayerMove(char stage[StageHeight][StageWeight], PPLAYER pPlayer);

void BMoveDown(char stage[StageHeight][StageWeight], PBOSS pBoss);
void BMoveUp(char stage[StageHeight][StageWeight], PBOSS pBoss);
void BossMove(char stage[StageHeight][StageWeight], PBOSS pBoss);