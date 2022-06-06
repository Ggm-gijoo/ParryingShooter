#include "Console.h"
#include "Stage.h"
using namespace std;

char Stage[StageHeight][StageWeight];

int main()
{
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
		if (cinput == VK_SPACE)
		{
			Parrying(Stage, &tPlayer);
		}
		PlayerMove(Stage, &tPlayer);
	}
}