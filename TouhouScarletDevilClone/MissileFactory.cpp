// #include "MissileFactory.h"
// // #include "Missile.h"
//
// void MissileFactory::Init(int size)
// {
// 	for (int i = 0; i < size; i++)
// 	{
// 		Missile* m = new Missile;
// 		m->Init();
// 		freeList.push_back(m);
// 	}
// }
//
// void MissileFactory::Update(float dt)
// {
// 	for (auto iter = activeList.begin(); iter != activeList.end(); )
// 	{
// 		(*iter)->Update();
// 		if ((*iter)->IsOutofScreen())
// 		{
// 			freeList.push_back(*iter);
// 			iter = activeList.erase(iter);
// 		}
// 		else
// 		{
// 			++iter;
// 		}
// 	}
// }
//
// void MissileFactory::Render()
// {
// 	for (auto iter = activeList.begin(); iter != activeList.end(); iter++)
// 	{
// 		(*iter)->Render();
// 	}
// }
//
// void MissileFactory::Release()
// {
// 	for (auto iter = activeList.begin(); iter != activeList.end(); iter++)
// 	{
// 		(*iter)->Release();
// 		delete* iter;
// 		*iter = nullptr;
// 	}
// 	for (auto iter = freeList.begin(); iter != freeList.end(); iter++)
// 	{
// 		(*iter)->Release();
// 		delete* iter;
// 		*iter = nullptr;
// 	}
// 	activeList.clear();
// 	freeList.clear();
// }
//
// Missile* MissileFactory::active()
// {
// 	if (!freeList.empty())
// 	{
// 		Missile* node = freeList.front();
// 		freeList.pop_front();
// 		activeList.push_back(node);
// 		return node;
// 	}
// 	else
// 	{
// 		return nullptr;
// 	}
// }
//
// void MissileFactory::kill(Missile* t)
// {
// 	for (auto it = activeList.begin(); it != activeList.end(); it++)
// 	{
// 		if (*it == t)
// 		{
// 			freeList.push_back(*it);
// 			activeList.erase(it);
// 			break;
// 		}
// 	}
// }