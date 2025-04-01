#pragma once
#include "KeyManager.h"

struct KeyBinding {
	int left;
	int right;
	int up;
	int down;
};

class InputManager
{

public:
	static bool isMoveLeft(void);
	static bool isMoveRight(void);
	static bool isMoveUp(void);
	static bool isMoveDown(void);
	static bool isFire(void);


};

