#pragma once
#include "config.h"

struct MissileTask
{
	float endTime;
	float angle;
	float angleRate;
	float speed;
	float speedRate;
};

class Shape;
class Missile
{
private:
	FPOINT pos = {-5000,-5000 };
	Shape* shape = nullptr;
	float endTime = 0.f;
	float current_angle = 0.f;
	float current_angleRate = 0.f;
	float current_speed = 0.f;
	float current_speedRate = 0.f;
	vector<MissileTask> tasks;
	int taskIdx = 0;
	float timer= 0.f;

public:
	Missile();
	void Init(string ShapeKey,FPOINT pos);
	void Update(float dt);
	void Render();
	void Release();

	bool isEnd();
	void pushTask(float endTime, float angle, float angleRate, float speed, float speedRate);
	void pushTask(MissileTask task);
};

