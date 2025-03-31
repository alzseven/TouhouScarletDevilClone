#pragma once
#include "config.h"

class Shape;
class Missile;
class MissileFactory;
class Pattern;
class VEnemy
{
protected:
	FPOINT pos = { -100,-100 };
	Shape* shape = nullptr;
	MissileFactory* m_factory = nullptr;
	float timer = 0;

	vector<Pattern> patterns;
	int current_pattern = -1;
	vector<pair<float, int>> patternMap;
	vector<pair<float, int>>::iterator iter;

	float shoot_cnt = 0;
	float shoot_next = 0;
	float frameNext = 0;
	float frameDelay = 0;
	int idx = 0;
public:
	VEnemy(MissileFactory* missileFactory);
	virtual ~VEnemy() {};
	virtual void Init(FPOINT pos);
	virtual void Update(float dt);
	virtual void Render();
	virtual void Release();
	bool checkTimer(float& nextTime, float delay);
	bool IsOutofScreen();
};

class Pattern
{
public:
	string shapeId;
	int			fireCount = 0;
	float		s_delay = 0;

	float		m_angle = 0;
	float		m_angleRate = 0;
	float		m_speed = 0;
	float		m_speedRate = 0;
};