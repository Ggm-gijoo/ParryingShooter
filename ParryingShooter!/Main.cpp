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
	cout << "�ƹ� Ű�� ������ �����ض�." << endl;
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