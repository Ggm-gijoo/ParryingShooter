#include "Console.h"

MCI_OPEN_PARMS OpenBgm;
MCI_PLAY_PARMS PlayBgm;

MCI_OPEN_PARMS OpenEffect;
MCI_PLAY_PARMS PlayEffect;

UINT dwID;
UINT dwID2;

void gotoxy(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

void setColor(int color)
{
	// 배경색은 0000 0000 nnnn 0000 (그래서 << 4 해줌)
	// 글자색은 0000 0000 0000 nnnn
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setScreenSize()
{
	system("mode con: cols=90 lines=25");
}

void fullscreen()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}

void PlayingBgm()
{
	OpenBgm.lpstrElementName = TEXT("creativeminds.mp3");
	OpenBgm.lpstrDeviceType = L"mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&OpenBgm);
	dwID = OpenBgm.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&PlayBgm);
}

void PlayingEffect()
{
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&PlayEffect);
	OpenEffect.lpstrElementName = TEXT("pickupCoin.wav");
	OpenBgm.lpstrDeviceType = L"waveaudio";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&OpenEffect);
	dwID2 = OpenEffect.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&PlayEffect);
}
