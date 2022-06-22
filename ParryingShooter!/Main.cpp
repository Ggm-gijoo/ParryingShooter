#include "Console.h"
#include "Stage.h"
using namespace std;

char Stage[StageHeight][StageWeight];

int main()
{
	PlayingBgm();
	CursorHide();
	setScreenSize();
	 setColor(4);
	 wcout << "        /$$$$$$$                                          /$$                    "<<endl;
	 wcout << "       | $$__  $$                                        |__/                    "<<endl; 
	 wcout << "       | $$  \\ $$ /$$$$$$   /$$$$$$   /$$$$$$  /$$   /$$  /$$ /$$$$$$$   /$$$$$$ "<<endl;
	 wcout << "       | $$$$$$$/|____  $$ /$$__  $$ /$$__  $$| $$  | $$ | $$| $$__  $$ /$$__  $$"<<endl; 
	 wcout << "       | $$____/  /$$$$$$$| $$  \\__/| $$  \\__/| $$  | $$ | $$| $$  \\ $$| $$  \\ $$"<<endl;
	 wcout << "       | $$      /$$__  $$| $$      | $$      | $$  | $$ | $$| $$  | $$| $$  | $$"<<endl; setColor(12);
	 wcout << "       | $$     |  $$$$$$$| $$      | $$      |  $$$$$$$ | $$| $$  | $$|  $$$$$$$"<<endl;
	 wcout << "       |__/      \\_______/|__/      |__/       \\____  $$ |__/|__/  |__/ \\____  $$"<<endl; 
	 wcout << "                                               /$$  | $$                /$$  \\ $$"<<endl; 
	 wcout << "                                              |  $$$$$$/               |  $$$$$$/"<<endl; setColor(14);
	 wcout << "                                               \\______/                 \\______/ " << endl << endl;
	 setColor(1);
	 wcout << "         /$$$$$$  /$$                              /$$                           "<<endl;
	 wcout << "        /$$__  $$| $$                             | $$                           "<<endl;
	 wcout << "       | $$  \\__/| $$$$$$$   /$$$$$$    /$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$    "<<endl;
	 wcout << "       |  $$$$$$ | $$__  $$ /$$__  $$  /$$__  $$|_  $$_/   /$$__  $$ /$$__  $$   "<<endl;
	 wcout << "        \\____  $$| $$  \\ $$| $$  \\ $$ | $$  \\ $$  | $$    | $$$$$$$$| $$  \\__/   "<<endl; setColor(3);
	 wcout << "        /$$  \\ $$| $$  | $$| $$  | $$ | $$  | $$  | $$ /$$| $$_____/| $$         "<<endl;
	 wcout << "       |  $$$$$$/| $$  | $$|  $$$$$$/ |  $$$$$$/  |  $$$$/|  $$$$$$$| $$         "<<endl; setColor(11);
	 wcout << "        \\______/ |__/  |__/ \\______/   \\______/    \\___/   \\_______/|__/         " << endl << endl;
												 
												 
												 
	POS tStartPos;
	POS tBossPos;
	PLAYER tPlayer;
	SHIELD tShield;
	BULLET tBullet;
	BOSS tBoss;
	tPlayer.isParryinged = false;
	SetStage(Stage, &tPlayer, &tBoss, &tStartPos, &tBossPos);
	cout << endl << "                                 아무 키나 눌러서 시작" << endl;
	char startInput = _getch();
	int whileCountRand = 0;
	int whileCount = 0;
	system("cls");
	while (true)
	{
		gotoxy(0, 4);
		cout << "                        이동 : 방향키 \t 패링 : 스페이스 바" << endl;
		cout << "                                  종료키 : ESC" << endl << endl;
		DrawStage(Stage, &tPlayer, &tBoss, &tShield);
		if (whileCountRand >= 14)
		{
			BossFire(&tBoss, &tPlayer);
			whileCountRand = 0;
		}
		if (whileCount >= 2)
		{
			DestroyParrying(&tPlayer, &tShield);
			BossMove(Stage, &tBoss);
			whileCount = 0;
		}
		BulletMove(Stage, &tPlayer, &tShield, &tBoss);
		
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
				Wait(100);
				char yesNoInput;
				setColor(15);
				cout << "                                 게임을 종료합니다 . " << endl;
				cout << "                                 예(Y)  아니오(N) " << endl;
				yesNoInput = _getch();
				switch (yesNoInput)
				{
				case 'y': case 'Y':
					return false;
					break;
				case 'n': case 'N':
					break;
				system("cls");
			}
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			Parrying(Stage, &tPlayer, &tShield, &tBoss);
		}

		PlayerMove(Stage, &tPlayer);

		if (PlayerWin(&tBoss))
		{
			system("cls");
			gotoxy(0, 4);
			setColor(9);
			cout << "                                 네가 이겼단다..." << endl << endl << endl;
			break;
		}
		else if (PlayerDie(&tPlayer))
		{
			system("cls");
			gotoxy(0, 4);
			setColor(4);
			cout << "                                 네가 졌단다..." << endl << endl << endl;
			break;
		}
		whileCountRand+= rand()%3+1;
		whileCount++;
	}
}