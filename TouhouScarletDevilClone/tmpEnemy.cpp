#include "tmpEnemy.h"
#include "Missile.h"
#include "Shape.h"
#include "D2DImage.h"
#include "MissileFactory.h"

tmpEnemy::tmpEnemy()
{
	D2DImage* image = ImageManager::GetInstance()->AddImage("enemy", TEXT("Image/enemy1.png"), 4, 1);
	shape = ShapeManager::GetInstance()->AddShapeCharacter("enemy", image, 3.0f);
	m_factory = new MissileFactory();
	m_factory->Init(500);
}

void tmpEnemy::Init(FPOINT pos)
{
	this->pos = pos;
	e_angle = 0;

	m_size = 5.0f;
	m_angle = 90.0f;
	m_angleRate = 1.1f;
	m_speed = 5.0f;
	m_speedRate = 0.0f;

	d_timer = 0;
	delay = 0.01f;
}

void tmpEnemy::Update()
{
	d_timer += TimerManager::GetInstance()->GetDeltaTime();
	i_timer += TimerManager::GetInstance()->GetDeltaTime();
	if (d_timer >= delay)
	{
		d_timer -= delay;
		m_angle += 1.0f;
		for (int i = 0; i < 4; i++)
		{
			Missile* m = m_factory->active();
			if (m)
			{
				m->Init(pos, m_size,
					m_angle + i * 90, m_angleRate,
					m_speed, m_speedRate);
			}
			
		}
		
	}
	if (i_timer >= 0.2f)
	{
		i_timer -= 0.2f;
		idx++;
		if (idx >= shape->image->GetMaxFrame())
		{
			idx = 0;
		}
	}
	m_factory->Update();
}

void tmpEnemy::Render()
{
	shape->image->Middle_RenderFrame(pos.x, pos.y, idx);
	m_factory->Render();
}

void tmpEnemy::Release()
{
	if (m_factory)
	{
		m_factory->Release();
		delete m_factory;
		m_factory = nullptr;
	}
	
}
