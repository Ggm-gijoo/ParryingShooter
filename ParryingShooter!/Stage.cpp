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
deque<BULLET*> bulletDeq;

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

void DrawStage(char Stage[StageHeight][StageWeight],PPLAYER pPlayer, PBOSS pBoss, PSHIELD pShield)
{
	setColor(9);
	cout << "           플레이어 HP  ";
	for (int i = 0; i < pPlayer->pHp; i++)
	{
		cout << "♥";
	}
	setColor(4);
	cout << "                            보스 HP  ";
	for (int i = 0; i < pBoss->bHp; i++)
	{
		cout << "♥";
	}
	cout << endl << endl;
	for (int i = 0; i < StageHeight; i++)
	{
		cout << "                       ";
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
				setColor(4);
				cout << "◀";
			}
			else if (pShield->shieldPos.x == j && pShield->shieldPos.y == i)
			{
				setColor(6);
				cout << " )";
			}
			else if (Check(j, i))
			{

			}
			else
			{
				switch (Stage[i][j])
				{
				case _WALL:
					setColor(wallColor);
					cout << "■";
					break;
				case _VOID:
					setColor(9);
					if (rand() % 15 < 14)
						cout << "  ";
					else
						cout << " .";
				}
			}
		}
		cout << endl;
	}
}

bool Check(int x, int y)
{
	for (int a = 0; a < bulletDeq.size(); a++)
	{
		if (bulletDeq[a]->bulletPos.x == x && bulletDeq[a]->bulletPos.y == y)
		{
			setColor(bulletDeq[a]->color);
			cout << "●";
			return true;
		}
	}
	return false;
}

void Parrying(char stage[StageHeight][StageWeight], PPLAYER pPlayer, PSHIELD pShield, PBOSS pBoss)
{
	if (pPlayer->pos.x + 1 <= StageWeight - 1)
	{
		if (pPlayer->pos.x + 1 == pBoss->bossPos.x && pPlayer->pos.y == pBoss->bossPos.y)
		{

		}
		else if (stage[pPlayer->pos.y][pPlayer->pos.x + 1] != '0' && !pPlayer->isParryinged)
		{
				pPlayer->isParryinged = true;
				pShield->shieldPos.y = pPlayer->pos.y;
				pShield->shieldPos.x = pPlayer->pos.x + 1;
		}
	}
}
void DestroyParrying(PPLAYER pPlayer, PSHIELD pShield)
{
	pPlayer->isParryinged = false;
	pShield->shieldPos.x = 1111;
	pShield->shieldPos.y = 1111;
}
void BulletMove(char stage[StageHeight][StageWeight], PPLAYER pPlayer, PSHIELD pShield, PBOSS pBoss)
{
	Wait(100);
	for (int i = 0; i < bulletDeq.size(); i++)
	{
		if (bulletDeq[i]->bulletPos.y == pPlayer->pos.y && bulletDeq[i]->bulletPos.x == pPlayer->pos.x && !bulletDeq[i]->isPar)
		{
			pPlayer->pHp--;
			bulletDeq.erase(bulletDeq.begin() + i);
		}
		else if (bulletDeq[i]->bulletPos.y == pShield->shieldPos.y && bulletDeq[i]->bulletPos.x == pShield->shieldPos.x && !bulletDeq[i]->isPar || bulletDeq[i]->bulletPos.y == pShield->shieldPos.y && bulletDeq[i]->bulletPos.x - 1 == pShield->shieldPos.x && !bulletDeq[i]->isPar)
		{
			PlayingEffect();
			bulletDeq[i]->color = 6;
			bulletDeq[i]->isPar = true;
		}
		else if (bulletDeq[i]->bulletPos.y == pBoss->bossPos.y && bulletDeq[i]->bulletPos.x == pBoss->bossPos.x && bulletDeq[i]->isPar)
		{
			pBoss->bHp--;
			bulletDeq.erase(bulletDeq.begin() + i);
		}
		else if (stage[bulletDeq[i]->bulletPos.y][bulletDeq[i]->bulletPos.x] == '0')
		{
			bulletDeq.erase(bulletDeq.begin() + i);
		}
		if (!bulletDeq[i]->isPar)
			bulletDeq[i]->bulletPos.x--;
		else
			bulletDeq[i]->bulletPos.x++;
	}
}

BULLET *BossInstantiateBullet(PBOSS pBoss, PPLAYER pPlayer)
{
	BULLET* bossBullet = new BULLET;

	bossBullet->bulletPos.x = pBoss->bossPos.x - 1;
	bossBullet->bulletPos.y = pBoss->bossPos.y;

	bulletDeq.push_back(bossBullet);
	return bossBullet;
}

void BossFire(PBOSS pBoss, PPLAYER pPlayer)
{
	BossInstantiateBullet(pBoss, pPlayer);
}

bool PlayerDie(PPLAYER pPlayer)
{
	if (pPlayer->pHp <= 0)
		return true;
	return false;
}

bool PlayerWin(PBOSS pBoss)
{
	if (pBoss->bHp <= 0)
		return true;
	return false;
}


void PMoveDown(char stage[StageHeight][StageWeight], PPLAYER pPlayer)
{
	if (pPlayer->pos.y + 1 <= StageHeight)
	{
		if (stage[pPlayer->pos.y+1][pPlayer->pos.x] != '0')
		{
			++pPlayer->pos.y;
		}
	}
}

void PMoveUp(char stage[StageHeight][StageWeight], PPLAYER pPlayer)
{
	if (pPlayer->pos.y - 1 >= 0)
	{
		if (stage[pPlayer->pos.y-1][pPlayer->pos.x] != '0')
		{
			--pPlayer->pos.y;
		}
	}
}

void PlayerMove(char stage[StageHeight][StageWeight], PPLAYER pPlayer)
{
	if (GetAsyncKeyState(VK_UP) & 0X8000)
	{
		PMoveUp(stage, pPlayer);
		Wait(30);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0X8000)
	{
		PMoveDown(stage, pPlayer);
		Wait(30);
	}
}

void BMoveDown(char stage[StageHeight][StageWeight], PBOSS pBoss)
{
	if (pBoss->bossPos.y + 1 <= StageHeight)
	{
		if (stage[pBoss->bossPos.y + 1][pBoss->bossPos.x] != '0')
		{
			++pBoss->bossPos.y;
		}
	}
}

void BMoveUp(char stage[StageHeight][StageWeight], PBOSS pBoss)
{
	if (pBoss->bossPos.y - 1 >= 0)
	{
		if (stage[pBoss->bossPos.y - 1][pBoss->bossPos.x] != '0')
		{
			--pBoss->bossPos.y;
		}
	}
}

void BossMove(char stage[StageHeight][StageWeight], PBOSS pBoss)
{
	int randomMove = rand() % 3;
	switch (randomMove)
	{
	case 0:
		BMoveDown(stage, pBoss);
		break;
	case 1:
		BMoveUp(stage, pBoss);
		break;
	default:
		break;
	}
}
