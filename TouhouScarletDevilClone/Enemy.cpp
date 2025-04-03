#include "Enemy.h"
#include "Shape.h"
#include "D2DImage.h"
#include "MissileManager.h"
#include "Missile.h"

Enemy::Enemy(MissileManager* mm)
{
	this->missileManager = mm;
}

void Enemy::Init(string ShapeKey, FPOINT pos)
{
	this->shape = ShapeManager::GetInstance()->FindShape(ShapeKey);
	this->pos = pos;
	timer = 0; 
	bullettimer = 0;
	delay = 1;
}



void Enemy::Update(float dt)
{
	
	
}

void Enemy::Render()
{
	shape->GetImage()->Middle_RenderFrame(pos.x, pos.y, 1);
}

void Enemy::Release()
{
	pos = { -5000,-5000 };
	shape = nullptr;
	//endTime = 0;
	current_angle = 0;
	current_angleRate = 0;
	current_speed = 0;
	current_speedRate = 0;
	tasks.clear();
	taskIdx = 0;
	timer = 0;
}

void Enemy::Move(float dt)
{
	if (taskIdx >= tasks.size()) return;
	MoveTask& currentTask = tasks[taskIdx];
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

bool Enemy::isEnd()
{
	if (pos.x<-WINSIZE_X / 2 || pos.x>WINSIZE_X * 1.5 || pos.y<-WINSIZE_Y / 2 || pos.y>WINSIZE_Y * 1.5)
		return true;
	/*if (timer >= endTime)
		return true;*/
	return false;
}
void Enemy::pushTask(float endTime, float angle, float angleRate, float speed, float speedRate)
{
	//this->endTime = max(this->endTime, endTime);
	tasks.push_back({ endTime,  angle,  angleRate,  speed,  speedRate });
}


void BasicEnemy::Update(float dt)
{
	Move(dt);
	bullettimer += dt;
	timer += dt;
	if (bullettimer >= delay)
	{
		for (int i = 0; i < 10; i++)
		{
			Missile* missile = missileManager->AddMissile();
			if (missile)
			{
				missile->Init("NormalBullet_purple", pos);
				missile->pushTask(3, i * 36, 0, 50, 0);
			}
		}
		bullettimer = 0;
	}

}

void BasicEnemy::setMoveTask()
{
	Init("zako_pink", { 300,100 });
	pushTask(10, 90, 0, 20, 0);
}

