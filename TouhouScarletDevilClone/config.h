// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <cmath>
#include <vector>
#include <map>
#include <list>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "ShapeManager.h"


#define PI			3.1415926535
#define WINSIZE_X	600
#define WINSIZE_Y	800
#define DEG_TO_RAD(degree) ((3.1415926535 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.1415926535) * radian)
#define TEMP_DELTA_TIME 0.001666667f

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;

// class Image;
// struct SHAPE {
// 	const wchar_t* TextureName;
// 	float Size;
// 	float Hit;
// 	Image* Texture;
// };


struct EnemyPatternInfo
{
	float startTime;
	float angle;
	float angleRate;
	float movementSpeed;
	float movementSpeedRate;
};

// class Task
// {
// private:
// 	bool valid = false;
// 	// float angle = 0.0f;
// 	// float speed = GAME_SPEED;
// 	int tick = 0;
// 	int currentTick = 0;
// 	int colors = 0;
// 	float size = 10;
//
// 	float accuracy = 1;
// 	bool targetValid = false;
// 	FP* target;
//
// public:
// 	Task();
// 	~Task();
// 	//¿œπ›≈∫
// 	void pushTask(float angle, float speed, int tick, int size, int colors);
// 	//¿Øµµ≈∫
// 	void pushTask(float angle, float speed, int tick, int color, int size, FP* target, int accuracy);
// 	void Update(FP& pos, int& taskIdx);
// 	FP calcNextMove();
// 	void ReleaseTask(int& counter);
//
// 	float getSize();
// 	int getColor();
// };