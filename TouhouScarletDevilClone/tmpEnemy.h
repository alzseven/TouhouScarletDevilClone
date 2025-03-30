#pragma once
#include "config.h"

class Shape;
class Missile;
class MissileFactory;

class tmpEnemy
{
private:
	FPOINT pos;
	Shape* shape = nullptr;
	MissileFactory* m_factory = nullptr;

	float e_angle = 0;

	float		m_size = 0;
	float		m_angle = 0;
	float		m_angleRate = 0;
	float		m_speed = 0;
	float		m_speedRate = 0;

	float d_timer = 0;
	float delay = 0;
	float i_timer = 0;
	int idx = 0;
public:
	tmpEnemy();
	virtual ~tmpEnemy() {};
	virtual void Init(FPOINT pos);
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

