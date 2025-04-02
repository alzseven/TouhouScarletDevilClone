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
#include <queue>
#include <list>
#include <unordered_set>
#include <algorithm>
#include <deque>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "ShapeManager.h"

#define PI			3.141592f
#define WINSIZE_X	900
#define WINSIZE_Y	680

#define GAME_LEFT		50
#define GAME_TOP		60
#define GAME_RIGHT		530
#define GAME_BOTTOM		620

#define GAME_CENTER_X	290
#define GAME_CENTER_Y	340

#define GAME_WIDTH		480
#define GAME_HEIGHT		560

#define DEG_TO_RAD(degree) ((3.141592f / 180.f) * degree)
#define RAD_TO_DEG(radian) ((180.f / 3.141592f) * radian)

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;
#include "EffectPlayer.h"
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


