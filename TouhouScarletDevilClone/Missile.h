#pragma once
#include "config.h"

class Shape;
class Missile
{
private:
	FPOINT		pos = { 0,0 };
	Shape*	shape = nullptr;
	float imageAngle = 0;

	float		angle = 0;
	float		angleRate = 0;
	float		speed = 0;
	float		speedRate = 0;

	

public:
	Missile();
	virtual ~Missile() {};
	virtual void Init();
	virtual void Init(string shapeId,FPOINT pos, float angle, float angleRate, float speed, float speedRate);
	virtual void Update();
	virtual void Render();
	virtual void Release();

	bool IsOutofScreen();
};

