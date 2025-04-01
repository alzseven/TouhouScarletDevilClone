#pragma once
#include "config.h"

class VEnemy;
class MissileFactory;
class EnemyFactory
{
protected:
	list<VEnemy*> activeList;
	list<VEnemy*> freeList;
	MissileFactory* missileFactory;
public:
	virtual ~EnemyFactory() {};
	void Init(int size);

	void Update(float dt);
	void Render();
	void Release();

	VEnemy* active();
	void kill(VEnemy* t);


};
