#pragma once
#include "config.h"

class Missile;
class MissileFactory
{
protected:
	list<Missile*> activeList;
	list<Missile*> freeList;

public:
	virtual ~MissileFactory() {};
	void Init(int size);

	void Update();
	void Render();
	void Release();

	Missile* active();
	void kill(Missile* t);


};

