#pragma once
#include "BHBullet.h"
#include "config.h"
#include "ObjectPool.h"

class Shape;
// class Missile;
// class MissileFactory;
class Pattern;
class VEnemy
{
protected:
	FPOINT pos = { -100,-100 };
	Shape* shape = nullptr;
	// MissileFactory* m_factory = nullptr;
	ObjectPool<BHBullet>* bulletPool = nullptr;
	float timer = 0;

	vector<Pattern*> patterns;
	int current_pattern = -1;
	vector<pair<float, int>> patternMap;
	vector<pair<float, int>>::iterator iter;

	float shoot_cnt = 0;
	float shoot_next = 0;
	float frameNext = 0;
	float frameDelay = 0;
	int idx = 0;
public:
	VEnemy();
	virtual ~VEnemy() {};
	virtual void Init(FPOINT pos);
	virtual void Update(float dt);
	virtual void Render();
	virtual void Release();
	bool checkTimer(float& nextTime, float delay);
	bool IsOutofScreen();
};

