#include "Missile.h"
#include "D2DImage.h"
#include "Shape.h"

Missile::Missile()
{
}

void Missile::Init(string ShapeKey, FPOINT pos)
{
	this->shape = ShapeManager::GetInstance()->FindShape(ShapeKey);
	this->pos = pos;
	timer = 0;
}



void Missile::Update(float dt)
{
	if (taskIdx >= tasks.size()) return;
	MissileTask& currentTask = tasks[taskIdx];
	if (currentTask.endTime <= timer)
	{
		taskIdx++;
	}
	current_angle = currentTask.angle;
	current_angleRate = currentTask.angleRate;
	current_speed = currentTask.speed;
	current_speedRate = currentTask.speedRate;

	current_angle += current_angleRate;
	current_speed += current_speedRate;
	pos.x += cosf(DEG_TO_RAD(current_angle)) * current_speed * dt;
	pos.y += sinf(DEG_TO_RAD(current_angle)) * current_speed * dt;
}

void Missile::Render()
{
	shape->GetImage()->Middle_RenderFrame(pos.x, pos.y, 1);
}

void Missile::Release()
{
	pos = { -5000,-5000 };
	shape = nullptr;
	endTime = 0;
	current_angle = 0;
	current_angleRate = 0;
	current_speed = 0;
	current_speedRate = 0;
	tasks.clear();
	taskIdx = 0;
	timer = 0;
}

bool Missile::isEnd()
{
	if (pos.x<-WINSIZE_X / 2 || pos.x>WINSIZE_X * 1.5 || pos.y<-WINSIZE_Y / 2 || pos.y>WINSIZE_Y * 1.5)
		return true;
	if (timer >= endTime)
		return true;
	return false;
}

void Missile::pushTask(float endTime, float angle, float angleRate, float speed, float speedRate)
{
	this->endTime = max(this->endTime, endTime);
	tasks.push_back({ endTime,  angle,  angleRate,  speed,  speedRate });
}

void Missile::pushTask(MissileTask task)
{
	tasks.push_back(task);
}
