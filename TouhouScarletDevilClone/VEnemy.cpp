#include "VEnemy.h"
#include "Missile.h"
#include "Shape.h"
#include "D2DImage.h"
#include "MissileFactory.h"

VEnemy::VEnemy(MissileFactory* missileFactory)
{

	shape = ShapeManager::GetInstance()->FindShape("enemy");
	if (shape == nullptr)
	{
		return;
	}

	m_factory = missileFactory;
}

void VEnemy::Init(FPOINT pos)
{
	this->pos = pos;
	
	patterns.push_back({"kunai",5, 0.1f,90.0f,0,5.0f,0});
	patterns.push_back({ "ball_green",5, 0.1f,45.0f,0,5.0f,0 });
	patternMap.push_back({ 0.0f,0 });
	patternMap.push_back({ 1.f,0 });
	patternMap.push_back({ 2.f,1 });
	patternMap.push_back({ 3.f,1 });
	patternMap.push_back({ 4.f,0 });
	patternMap.push_back({ 10.f,0 });
	iter = patternMap.begin();
	frameDelay = 0.2;
	Course.SetOffset(pos);
	Segment seg;
	seg.startTime = 1.f;
	seg.endTime = 3.f;
	seg.points = {
	{0.f, 0.f},
	{57.f, 55.f},
	{106.f, 98.f},
	{158.f, 143.f}
	};
	Course.segments.push_back(seg);
	seg.startTime = 4.f;
	seg.endTime = 5.f;
	seg.points = {
	{0.f, 0.f},
	{0.f, -41.f},
	{0.f, -78.f},
	{-1.f, -109.f}
	};
	Course.segments.push_back(seg);
	seg.startTime = 6.f;
	seg.endTime = 7.f;
	seg.points = {
	{0.f, 0.f},
	{-30.f, 28.f},
	{-59.f, 48.f},
	{-103.f, 80.f},
	{-128.f, 102.f}
	};
	Course.segments.push_back(seg);
}

void VEnemy::Update(float dt)
{
	timer += dt;
	pos = Course.GetCurrentPos(timer);
	if ((iter != patternMap.end())&&(iter->first - timer <= 0.0f))
	{
		current_pattern = iter->second;
		iter++;
	}
	
	if (current_pattern != -1)
	{
		Pattern& p = patterns[current_pattern];
		if (checkTimer(shoot_next, p.s_delay))
		{
			shoot_cnt++;
			m_factory->active()->Init(p.shapeId, { pos.x,pos.y } ,
				p.m_angle + shoot_cnt * 10, p.m_angleRate, 
				p.m_speed, p.m_speedRate);
		}
		if (shoot_cnt >= p.fireCount)
		{
			shoot_cnt = 0;
			current_pattern = -1;
			if (iter == patternMap.end())
			{
				pos = { -100,-100 };
				return;
			}
		}
	}
	
	if (checkTimer(frameNext, frameDelay))
	{
		idx++;
		if (idx >= shape->image->GetMaxFrame())
		{
			idx = 0;
		}
	}
	//m_factory->Update();
}

void VEnemy::Render()
{
	
	shape->image->Middle_RenderFrame(pos.x, pos.y , idx);
	//m_factory->Render();
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
	float width = shape->image->GetWidth();
	float height = shape->image->GetHeight();

	float right = pos.x + width / 2;
	float left = pos.x - width / 2;
	float top = pos.y - height / 2;
	float bottom = pos.y + height / 2;

	if (right < 0 || left > WINSIZE_X
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}

