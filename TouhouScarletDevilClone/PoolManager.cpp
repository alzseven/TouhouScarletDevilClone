#include "PoolManager.h"

void PoolManager::Init()
{
    enemyBulletPool.Init(2000);
    playerBulletPool.Init(1000);
    enemyPool.Init(50);
}

void PoolManager::Update(float dt)
{
    //TODO:
    for (std::vector<BHEnemy*>::iterator iter = enemyPool.GetActive().begin(); iter != enemyPool.GetActive().end(); ++iter)
    {
        (*iter)->Update(dt);
    }

    for (std::vector<BHBullet*>::iterator iter = enemyBulletPool.GetActive().begin(); iter != enemyBulletPool.GetActive().end(); ++iter)
    {
        (*iter)->Update(dt);
    }

    for (std::vector<BHBullet*>::iterator iter = playerBulletPool.GetActive().begin(); iter != playerBulletPool.GetActive().end(); ++iter)
    {
        (*iter)->Update(dt);
    }
    
    enemyPool.UpdateActive();
    playerBulletPool.UpdateActive();
    enemyBulletPool.UpdateActive();
}

void PoolManager::Release()
{
    enemyPool.Clear();
    enemyBulletPool.Clear();
    playerBulletPool.Clear();

    ReleaseInstance();
}

void PoolManager::Render()
{
    //TODO:
    for (std::vector<BHEnemy*>::iterator iter = enemyPool.GetActive().begin(); iter != enemyPool.GetActive().end(); ++iter)
    {
        (*iter)->Render(NULL);
    }

    for (std::vector<BHBullet*>::iterator iter = enemyBulletPool.GetActive().begin(); iter != enemyBulletPool.GetActive().end(); ++iter)
    {
        (*iter)->Render(NULL);
    }

    for (std::vector<BHBullet*>::iterator iter = playerBulletPool.GetActive().begin(); iter != playerBulletPool.GetActive().end(); ++iter)
    {
        (*iter)->Render(NULL);
    }
}
