#include "EnemyManager.h"
#include "Enemy.h"
#include "MissileManager.h"
void EnemyManager::Init(int size)
{
	missileManager = new MissileManager;
	missileManager->Init(500);
	for (int i = 0; i < size; i++)
	{
		Enemy* m = new Enemy(missileManager);
		freeEnemy.push_back(m);
	}
}

void EnemyManager::Update(float dt)
{
	missileManager->Update(dt);
	for (auto it = activeEnemy.begin(); it != activeEnemy.end(); )
	{
		Enemy* Enemy = *it;
		if (Enemy->isEnd())
		{
			freeEnemy.push_back(Enemy);
			it = activeEnemy.erase(it);
		}
		else
		{
			Enemy->Update(dt);
			++it;
		}
	}
}

void EnemyManager::Render()
{
	missileManager->Render();
	for (auto it = activeEnemy.begin(); it != activeEnemy.end(); it++)
	{
		(*it)->Render();
	}
}

void EnemyManager::Release()
{
	for (auto& iter : activeEnemy)
	{
		if (iter)
		{
			iter->Release();
			delete iter;
			iter = nullptr;
		}
	}
	activeEnemy.clear();
	for (auto& iter : freeEnemy)
	{
		if (iter)
		{
			iter->Release();
			delete iter;
			iter = nullptr;
		}
	}
	freeEnemy.clear();
	if (missileManager)
	{
		missileManager->Release();
		delete missileManager;
		missileManager = nullptr;
	}
}

Enemy* EnemyManager::AddEnemy()
{
	if (!freeEnemy.empty())
	{
		Enemy* Enemy = freeEnemy.front();
		freeEnemy.pop_front();
		activeEnemy.push_back(Enemy);
		return Enemy;
	}
	else return nullptr;
}
