#include "Console.h"
#include "Stage.h"
using namespace std;

char Stage[StageHeight][StageWeight];
//timeBeginPeriod(1);
//timeGetTime();
//clock_t // ms 자료형
//clock();
//clock_t cur;
//clock_t nex;
//cur = clock();
//if ((clock() - cur)==1)
//{
//
//}
int main()
{
	fullscreen();
	 setColor(4);
	 wcout << " /$$$$$$$                                          /$$                    "<<endl;
	 wcout << "| $$__  $$                                        |__/                    "<<endl; 
	 wcout << "| $$  \\ $$ /$$$$$$   /$$$$$$   /$$$$$$  /$$   /$$  /$$ /$$$$$$$   /$$$$$$ "<<endl;
	 wcout << "| $$$$$$$/|____  $$ /$$__  $$ /$$__  $$| $$  | $$ | $$| $$__  $$ /$$__  $$"<<endl; 
	 wcout << "| $$____/  /$$$$$$$| $$  \\__/| $$  \\__/| $$  | $$ | $$| $$  \\ $$| $$  \\ $$"<<endl;
	 wcout << "| $$      /$$__  $$| $$      | $$      | $$  | $$ | $$| $$  | $$| $$  | $$"<<endl; setColor(12);
	 wcout << "| $$     |  $$$$$$$| $$      | $$      |  $$$$$$$ | $$| $$  | $$|  $$$$$$$"<<endl;
	 wcout << "|__/      \\_______/|__/      |__/       \\____  $$ |__/|__/  |__/ \\____  $$"<<endl; 
	 wcout << "                                        /$$  | $$                /$$  \\ $$"<<endl; 
	 wcout << "                                       |  $$$$$$/               |  $$$$$$/"<<endl; setColor(14);
	 wcout << "                                        \\______/                 \\______/ " << endl << endl;
	 setColor(1);
	 wcout << "  /$$$$$$  /$$                              /$$                           "<<endl;
	 wcout << " /$$__  $$| $$                             | $$                           "<<endl;
	 wcout << "| $$  \\__/| $$$$$$$   /$$$$$$    /$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$    "<<endl;
	 wcout << "|  $$$$$$ | $$__  $$ /$$__  $$  /$$__  $$|_  $$_/   /$$__  $$ /$$__  $$   "<<endl;
	 wcout << " \\____  $$| $$  \\ $$| $$  \\ $$ | $$  \\ $$  | $$    | $$$$$$$$| $$  \\__/   "<<endl; setColor(3);
	 wcout << " /$$  \\ $$| $$  | $$| $$  | $$ | $$  | $$  | $$ /$$| $$_____/| $$         "<<endl;
	 wcout << "|  $$$$$$/| $$  | $$|  $$$$$$/ |  $$$$$$/  |  $$$$/|  $$$$$$$| $$         "<<endl; setColor(11);
	 wcout << " \\______/ |__/  |__/ \\______/   \\______/    \\___/   \\_______/|__/         " << endl << endl;
												 
												 
												 
	POS tStartPos;
	PLAYER tPlayer;
	tPlayer.isParryinged = false;
	SetStage(Stage,&tPlayer,&tStartPos);
	cout << "아무 키나 눌러서 시작해라." << endl;
	char startInput = _getch();
	system("cls");
	while (true)
	{
		gotoxy(0, 10);
		DrawStage(Stage, &tPlayer);
		char cinput = _getch();
		if (cinput == VK_ESCAPE)
		{
			cout << "게임을 종료합니다 . " << endl;
			cout << "예(Y)  아니오(N) " << endl;
			char yesNoInput = _getch();
			switch (yesNoInput)
			{
			case 'y': case 'Y':
				return false;
				break;
			case 'n': case 'N':
				break;
			default:
				break;
			}
			system("cls");
		}
		if (cinput == VK_SPACE)
		{
			Parrying(Stage, &tPlayer);
		}
		PlayerMove(Stage, &tPlayer);
	}
}