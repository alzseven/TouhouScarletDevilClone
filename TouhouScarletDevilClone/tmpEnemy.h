#pragma once
#include "config.h"

class D2DImage;
class Missile;
class tmpEnemy
{
private:
	FPOINT pos;
	D2DImage* image = nullptr;

	float e_angle = 0;

	float		m_angle = 0;
	float		m_angleRate = 0;
	float		m_speed = 0;
	float		m_speedRate = 0;

	int timer = 0;
public:
	tmpEnemy();
	virtual ~tmpEnemy() {};
	virtual void Init(FPOINT pos);
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

