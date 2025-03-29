#pragma once
#include "config.h"

class D2DImage;
class Missile
{
private:
	FPOINT		pos = { 0,0 };
	D2DImage*	image = nullptr;

	float imageAngle = 0;

	float		angle = 0;
	float		angleRate = 0;
	float		speed = 0;
	float		speedRate = 0;
public:
	Missile();
	virtual ~Missile() {};
	virtual void Init(FPOINT pos,float angle, float angleRate, float speed, float speedRate);
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

