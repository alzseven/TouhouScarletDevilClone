#pragma once
#include "config.h"

class Missile;
class MissileManager
{
private:
	list<Missile*> activeMissile;
	list<Missile*> freeMissile;
public:
	void Init(int size);
	void Update(float dt);
	void Render();
	void Release();

	Missile* AddMissile();
};

