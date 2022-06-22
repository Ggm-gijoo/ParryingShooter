#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <Digitalv.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <chrono>
#include <queue>

#pragma comment(lib,"winmm.lib")

void gotoxy(int x, int y);

void setColor(int color);

void setScreenSize();

void fullscreen();

void PlayingBgm();

void PlayingEffect();

void Wait(DWORD dwMilliSec);

void CursorHide();

bool IsKeyDown(int vKey);


