#include "tmpEnemy.h"
#include "Missile.h"
#include "D2DImage.h"
#include "MissileFactory.h"

tmpEnemy::tmpEnemy()
{
	image = ImageManager::GetInstance()->AddImage("enemy", TEXT("Image/enemy1.png"), 4, 1);
	m_factory = new MissileFactory();
	m_factory->Init(500);
}

void tmpEnemy::Init(FPOINT pos)
{
	this->pos = pos;
	e_angle = 0;

	m_size = 5.0f;
	m_angle = 90.0f;
	m_angleRate = -0.5f;
	m_speed = 2.0f;
	m_speedRate = 0.01f;

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
		m_angle += 95.0f;
		m_factory->active()->Init(pos, m_size,
			m_angle, m_angleRate,
			m_speed, m_speedRate);
	}
	if (i_timer >= 0.2f)
	{
		i_timer -= 0.2f;
		idx++;
		if (idx >= image->GetMaxFrame())
		{
			idx = 0;
		}
	}
	m_factory->Update();
}

void tmpEnemy::Render()
{
	image->Middle_RenderFrame(pos.x, pos.y, idx);
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
