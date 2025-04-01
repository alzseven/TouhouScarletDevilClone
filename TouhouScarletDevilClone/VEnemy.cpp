#include "VEnemy.h"
// #include "Missile.h"
#include "Shape.h"
#include "D2DImage.h"
// #include "MissileFactory.h"
#include "Pattern.h"

VEnemy::VEnemy()
{

	shape = ShapeManager::GetInstance()->FindShape("enemy");
	if (shape == nullptr)
	{
		return;
	}
	bulletPool = new ObjectPool<BHBullet>();
	bulletPool->Init(1000);
	// m_factory = missileFactory;
}

void VEnemy::Init(FPOINT pos)
{
	this->pos = pos;
	
	patterns.push_back(new Pattern{"kunai",5, 0.1f,90.0f,0,10.0f,0});
	patterns.push_back(new Pattern{ "ball_green",5, 0.1f,45.0f,0,10.0f,0 });
	patternMap.push_back({ 0.0f,0 });
	patternMap.push_back({ 1.f,0 });
	patternMap.push_back({ 2.f,1 });
	patternMap.push_back({ 3.f,1 });
	patternMap.push_back({ 4.f,0 });
	patternMap.push_back({ 5.f,0 });
	iter = patternMap.begin();
	frameDelay = 0.2f;
}

void VEnemy::Update(float dt)
{
	timer += dt;
	
	if ((iter != patternMap.end())&&(iter->first - timer <= 0.0f))
	{
		current_pattern = iter->second;
		++iter;
	}
	
	if (current_pattern != -1)
	{
		Pattern* p = patterns[current_pattern];
		if (checkTimer(shoot_next, p->s_delay))
		{
			shoot_cnt++;
			BHBullet* bullet = bulletPool->Allocate();
			bullet->Init(p->shapeId, 10.f, pos, 
				p->m_angle + shoot_cnt * 10);
			bullet->Launch(p->m_angleRate, 
				p->m_speed, p->m_speedRate, false);
		}
		if (shoot_cnt >= p->fireCount)
		{
			shoot_cnt = 0;
			current_pattern = -1;
			if (iter == patternMap.end())
			{
				bulletPool->Clear();
				pos = { -100,-100 };
				return;
			}
		}
	}
	
	if (checkTimer(frameNext, frameDelay))
	{
		idx++;
		if (idx >= shape->GetImage()->GetMaxFrame())
		{
			idx = 0;
		}
	}
	//m_factory->Update();

	std::vector<BHBullet*> active = bulletPool->GetActive();
	for (std::vector<BHBullet*>::iterator it = active.begin(); it != active.end(); ++it)
	{
		(*it)->Update(dt);
	}
}

void VEnemy::Render()
{
	shape->GetImage()->Middle_RenderFrame(pos.x, pos.y, idx);
	
	std::vector<BHBullet*> active = bulletPool->GetActive();
	for (std::vector<BHBullet*>::iterator it = active.begin(); it != active.end(); ++it)
	{
		(*it)->Render(NULL);
	}
}

void VEnemy::Release()
{
	

}

bool VEnemy::checkTimer(float& nextTime, float delay)
{
	if (timer >= nextTime)
	{
		nextTime = timer + delay;
		return true;
	}
	else return false;
}

bool VEnemy::IsOutofScreen()
{
	float width = shape->GetImage()->GetWidth();
	float height = shape->GetImage()->GetHeight();

	float right = pos.x + width / 2;
	float left = pos.x - width / 2;
	float top = pos.y - height / 2;
	float bottom = pos.y + height / 2;

	if (right < 0 || left > WINSIZE_X
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}

