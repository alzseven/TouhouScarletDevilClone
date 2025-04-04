#pragma once
#include "config.h"

struct MoveTask
{
	float endTime;
	float angle;
	float angleRate;
	float speed;
	float speedRate;
};
class Shape;
class MissileManager;
class Enemy
{
protected:
	FPOINT pos = { -5000,-5000 };
	Shape* shape = nullptr;
	MissileManager* missileManager;
	//float endTime = 0.f;
	float current_angle = 0.f;
	float current_angleRate = 0.f;
	float current_speed = 0.f;
	float current_speedRate = 0.f;
	float timer = 0;
	vector<MoveTask> tasks;
	int taskIdx = 0;
	float bullettimer = 0.f;
	float delay = 0.f;
public:
	Enemy(MissileManager* mm);
	virtual void Init(string ShapeKey, FPOINT pos);
	virtual void Update(float dt);
	void Render();
	void Release();
	void Move(float dt);
	void pushTask(float endTime, float angle, float angleRate, float speed, float speedRate);
	bool isEnd();
};

class BasicEnemy : public Enemy
{
public:
	virtual void Update(float dt) override;
	void setMoveTask();
	void setMissileTask();
};

