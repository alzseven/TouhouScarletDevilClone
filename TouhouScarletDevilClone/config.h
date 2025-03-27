// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <cmath>
#include <vector>

using namespace std;

//#include "KeyManager.h"
//#include "ImageManager.h"
//#include "TimerManager.h"


#define WINSIZE_X	600
#define WINSIZE_Y	800
#define DEG_TO_RAD(degree) ((3.1415926535 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.1415926535) * radian)

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;