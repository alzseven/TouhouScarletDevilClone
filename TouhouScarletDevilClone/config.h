// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <cmath>
#include <vector>
#include <array>
#include <map>

using namespace std;

#include "KeyManager.h"

#define PI			3.1415926535
#define WINSIZE_X	900
#define WINSIZE_Y	680
#define DEG_TO_RAD(degree) ((3.1415926535 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.1415926535) * radian)

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;


enum CollisionLayerMask {
	LAYER_PLAYER        = 0x0001,
	LAYER_ENEMY         = 0x0002,
	LAYER_PLAYER_BULLET = 0x0004,
	LAYER_ENEMY_BULLET  = 0x0008,
	LAYER_ITEM          = 0x0010
};
typedef uint16_t CollisionLayer;
struct CollisionMatrixEntry {
	CollisionLayer layer1;
	CollisionLayer layer2;
};


