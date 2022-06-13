#include "Stage.h"
#include "Console.h"

using namespace std;

/// <summary>
/// 0은 벽, 1은 공허, 2는 플레이어 초기 위치, 3은 보스 초기 위치
/// </summary>

enum StageType
{
	_WALL = '0',
	_VOID,
	_PLAYER,
	_BOSS,
	_SHIELD,
};
float parryingTimer;

void SetStage(char Stage[StageHeight][StageWeight],PPLAYER pPlayer, PBOSS pBoss, PPOS pStartPos, PPOS pBossPos)
{
	pStartPos->x = 1;
	pStartPos->y = 5;
	pPlayer->pos = *pStartPos;
	pBossPos->x = 18;
	pBossPos->y = 5;
	pBoss->bossPos = *pBossPos;
	strcpy_s(Stage[0], "00000000000000000000");
	strcpy_s(Stage[1], "01111111111111111110");
	strcpy_s(Stage[2], "01111111111111111110");
	strcpy_s(Stage[3], "01111111111111111110");
	strcpy_s(Stage[4], "01111111111111111110");
	strcpy_s(Stage[5], "01111111111111111110");
	strcpy_s(Stage[6], "01111111111111111110");
	strcpy_s(Stage[7], "01111111111111111110");
	strcpy_s(Stage[8], "01111111111111111110");
	strcpy_s(Stage[9], "01111111111111111110");
	strcpy_s(Stage[10],"00000000000000000000");
}

void DrawStage(char Stage[StageHeight][StageWeight],PPLAYER pPlayer, PBOSS pBoss, PBULLET pBullet)
{
	for (int i = 0; i < StageHeight; i++)
	{
		for (int j = 0; j < StageWeight; j++)
		{
			int wallColor = rand() % 15 + 1;
			if (pPlayer->pos.x == j && pPlayer->pos.y == i)
			{
				setColor(9);
				cout << "▶";
			}
			else if (pBoss->bossPos.x == j && pBoss->bossPos.y == i)
			{
				setColor(5);
				cout << "◀";
			}
			else if (pBullet->bulletPos.x == j && pBullet->bulletPos.y == i)
			{
				setColor(5);
				cout << "o ";
			}
			else
			{
				switch (Stage[i][j])
				{
				case _WALL:
					setColor(15);
					cout << "■";
					break;
				case _VOID:
					setColor(9);
					if (rand() % 15 < 12)
						cout << "  ";
					else
						cout << " .";
					break;
				case _SHIELD:
					setColor(6);
					cout << " )";
					break;
				}
			}
		}
		cout << endl;
	}
}

void Parrying(char stage[StageHeight][StageWeight], PPLAYER pPlayer)
{
	if (pPlayer->pos.x + 1 <= StageWeight - 1)
	{
		if (stage[pPlayer->pos.y][pPlayer->pos.x + 1] != '0' && stage[pPlayer->pos.y][pPlayer->pos.x + 1] != '3')
		{
			if (!pPlayer->isParryinged)
			{
				parryingTimer = (float)time(NULL);
				pPlayer->isParryinged = true;
				stage[pPlayer->pos.y][pPlayer->pos.x + 1] = '4';
				
			}
			else if ((float)time(NULL) - parryingTimer >= 3000 && pPlayer->isParryinged)
			{
				pPlayer->isParryinged = false;
			}
		}
	}
}

void BulletMove(char stage[StageHeight][StageWeight], PBULLET pBullet, PPLAYER pPlayer, PSHIELD pShield)
{
	Sleep(50);
	if (stage[pBullet->bulletPos.y][pBullet->bulletPos.x] == stage[pPlayer->pos.y][pPlayer->pos.x])
	{
		pPlayer->pHp--;
	}
	/*else if (stage[pBullet->bulletPos.y][pBullet->bulletPos.x] == stage[pShield->shieldPos.y][pShield->shieldPos.x])
	{

	}*/
	else
	pBullet->bulletPos.x--;
}

void BossFire(char stage[StageHeight][StageWeight], PBOSS pBoss, PPLAYER pPlayer, PSHIELD pShield)
{
	BULLET *bossBullet = new BULLET;
	bossBullet->bulletPos.x = 0;
	bossBullet->bulletPos.y = 0;
	stage[bossBullet->bulletPos.y][bossBullet->bulletPos.x] = stage[pBoss->bossPos.y][pBoss->bossPos.x - 1];
	//BulletMove(stage[StageHeight][StageWeight], bossBullet, pPlayer, pShield);
}


void PMoveDown(char stage[StageHeight][StageWeight], PPLAYER pPlayer)
{
	if (pPlayer->pos.y + 1 <= StageHeight)
	{
		if (stage[pPlayer->pos.y+1][pPlayer->pos.x] != '0' && stage[pPlayer->pos.y+1][pPlayer->pos.x] != '3' && stage[pPlayer->pos.y + 1][pPlayer->pos.x] != '4')
		{
			++pPlayer->pos.y;
		}
	}
}

void PMoveUp(char stage[StageHeight][StageWeight], PPLAYER pPlayer)
{
	if (pPlayer->pos.y - 1 >= 0)
	{
		if (stage[pPlayer->pos.y-1][pPlayer->pos.x] != '0' && stage[pPlayer->pos.y-1][pPlayer->pos.x] != '3' && stage[pPlayer->pos.y - 1][pPlayer->pos.x] != '4')
		{
			--pPlayer->pos.y;
		}
	}
}

void PMoveLeft(char stage[StageHeight][StageWeight], PPLAYER pPlayer)
{
	if (pPlayer->pos.x - 1 >= 0)
	{
		if (stage[pPlayer->pos.y][pPlayer->pos.x - 1] != '0' && stage[pPlayer->pos.y][pPlayer->pos.x - 1] != '3' && stage[pPlayer->pos.y][pPlayer->pos.x - 1] != '4')
		{
			--pPlayer->pos.x;
		}
	}
}

void PMoveRight(char stage[StageHeight][StageWeight], PPLAYER pPlayer)
{
	if (pPlayer->pos.x + 1 <= StageWeight - 1)
	{
		if (stage[pPlayer->pos.y][pPlayer->pos.x + 1] != '0' && stage[pPlayer->pos.y][pPlayer->pos.x + 1] != '3' && stage[pPlayer->pos.y][pPlayer->pos.x + 1] != '4')
		{
			++pPlayer->pos.x;
		}
	}
}

void PlayerMove(char stage[StageHeight][StageWeight], PPLAYER pPlayer)
{
	if (GetAsyncKeyState(VK_UP) & 0X8000)
	{
		PMoveUp(stage, pPlayer);
		Sleep(50);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0X8000)
	{
		PMoveDown(stage, pPlayer);
		Sleep(50);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0X8000)
	{
		PMoveLeft(stage, pPlayer);
		Sleep(50);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0X8000)
	{
		PMoveRight(stage, pPlayer);
		Sleep(50);
	}
}
