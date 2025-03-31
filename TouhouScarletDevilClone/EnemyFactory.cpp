#include "EnemyFactory.h"
#include "MissileFactory.h"
#include "VEnemy.h"

void EnemyFactory::Init(int size)
{
	missileFactory = new MissileFactory();
	missileFactory->Init(1000);
	for (int i = 0; i < size; i++)
	{
		VEnemy* m = new VEnemy(missileFactory);
		freeList.push_back(m);
	}
	
}

void EnemyFactory::Update(float dt)
{
	missileFactory->Update(dt);
	for (auto iter = activeList.begin(); iter != activeList.end(); )
	{
		(*iter)->Update(dt);
		if ((*iter)->IsOutofScreen())
		{
			freeList.push_back(*iter);
			iter = activeList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void EnemyFactory::Render()
{
	missileFactory->Render();
	for (auto iter = activeList.begin(); iter != activeList.end(); iter++)
	{
		(*iter)->Render();
	}
}

void EnemyFactory::Release()
{
	for (auto iter = activeList.begin(); iter != activeList.end(); iter++)
	{
		(*iter)->Release();
		delete* iter;
		*iter = nullptr;
	}
	for (auto iter = freeList.begin(); iter != freeList.end(); iter++)
	{
		(*iter)->Release();
		delete* iter;
		*iter = nullptr;
	}
	activeList.clear();
	freeList.clear();

	if (missileFactory)
	{
		missileFactory->Release();
		delete missileFactory;
		missileFactory = nullptr;
	}
}

VEnemy* EnemyFactory::active()
{
	if (!freeList.empty())
	{
		VEnemy* node = freeList.front();
		freeList.pop_front();
		activeList.push_back(node);
		return node;
	}
	else
	{
		return nullptr;
	}
}

void EnemyFactory::kill(VEnemy* t)
{
	for (auto it = activeList.begin(); it != activeList.end(); it++)
	{
		if (*it == t)
		{
			freeList.push_back(*it);
			activeList.erase(it);
			break;
		}
	}
}


