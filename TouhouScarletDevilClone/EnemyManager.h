#pragma once
#include "config.h"

class Enemy;
class MissileManager;
class EnemyManager
{
private:
	list<Enemy*> activeEnemy;
	list<Enemy*> freeEnemy;
	MissileManager* missileManager;
public:
	void Init(int size);
	void Update(float dt);
	void Render();
	void Release();

	Enemy* AddEnemy();
};

