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

void DrawStage(char Stage[StageHeight][StageWeight],PPLAYER pPlayer, PBOSS pBoss, PBULLET pBullet, PSHIELD pShield)
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
			else if (pShield->shieldPos.x == j && pShield->shieldPos.y == i)
			{
				setColor(6);
				cout << " )";
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
				}
			}
		}
		cout << endl;
	}
}

void Parrying(char stage[StageHeight][StageWeight], PPLAYER pPlayer, PSHIELD pShield)
{
	if (pPlayer->pos.x + 1 <= StageWeight - 1)
	{
		if (stage[pPlayer->pos.y][pPlayer->pos.x + 1] != '0' && stage[pPlayer->pos.y][pPlayer->pos.x + 1] != '3')
		{
				parryingTimer = (float)time(NULL);
				pPlayer->isParryinged = true;
				pShield->shieldPos.y = pPlayer->pos.y;
				pShield->shieldPos.x = pPlayer->pos.x + 1;
		}
	}
}
deque<BULLET*> bulletDeq;
void BulletMove(char stage[StageHeight][StageWeight], PBULLET pBullet, PPLAYER pPlayer, PSHIELD pShield, PBOSS pBoss)
{
	bulletDeq.push_back(pBullet);
	Sleep(100);
	for (int i = 0; i < bulletDeq.size(); i++)
	{
		if (stage[bulletDeq[i]->bulletPos.y][bulletDeq[i]->bulletPos.x] == stage[pPlayer->pos.y][pPlayer->pos.x] && !bulletDeq[i]->isPar)
		{
			pPlayer->pHp--;
		}
		else if (pShield->shieldPos != nullptr && stage[bulletDeq[i]->bulletPos.y][bulletDeq[i]->bulletPos.x] == stage[pShield->shieldPos.y][pShield->shieldPos.x] && !bulletDeq[i]->isPar)
		{
			bulletDeq[i]->isPar = true;
		}
		else if (stage[bulletDeq[i]->bulletPos.y][bulletDeq[i]->bulletPos.x] == stage[pBoss->bossPos.y][pBoss->bossPos.x] && bulletDeq[i]->isPar)
		{
			pBoss->bHp--;
		}
		if (!bulletDeq[i]->isPar)
			bulletDeq[i]->bulletPos.x--;
		else
			bulletDeq[i]->bulletPos.x++;
		cout << bulletDeq[i]->bulletPos.x;
	}
}

BULLET *BossFire(PBOSS pBoss, PPLAYER pPlayer)
{
	BULLET *bossBullet = new BULLET;

	if (bossBullet->bulletPos.x == bossBullet->bulletPos.y && bossBullet->bulletPos.y == -842150451)
	{
		bossBullet->bulletPos.x = pBoss->bossPos.x - 1;
		bossBullet->bulletPos.y = pBoss->bossPos.y;
	}
	return bossBullet;	
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
