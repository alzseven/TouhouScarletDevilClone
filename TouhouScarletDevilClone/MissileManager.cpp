#include "MissileManager.h"
#include "Missile.h"

void MissileManager::Init(int size)
{
	for (int i = 0; i < size; i++)
	{
		Missile* m = new Missile();
		freeMissile.push_back(m);
	}
}

void MissileManager::Update(float dt)
{
	for (auto it = activeMissile.begin(); it != activeMissile.end(); )
	{
		Missile* missile = *it;
		if (missile->isEnd())
		{
			freeMissile.push_back(missile);
			it = activeMissile.erase(it);
		}
		else
		{
			missile->Update(dt); 
			++it;
		}
	}
}

void MissileManager::Render()
{
	for (auto it = activeMissile.begin(); it != activeMissile.end(); it++)
	{
		(*it)->Render();
	}
}

void MissileManager::Release()
{
	for (auto& iter : activeMissile)
	{
		if (iter)
		{
			iter->Release();
			delete iter;
			iter = nullptr;
		}
	}
	activeMissile.clear();
	for (auto& iter : freeMissile)
	{
		if (iter)
		{
			iter->Release();
			delete iter;
			iter = nullptr;
		}
	}
	freeMissile.clear();
}

Missile* MissileManager::AddMissile()
{
	if (!freeMissile.empty())
	{
		Missile* missile = freeMissile.front();
		freeMissile.pop_front();
		activeMissile.push_back(missile);
		return missile;
	}
	else return nullptr;
}
