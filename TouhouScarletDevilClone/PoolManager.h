#pragma once

#include "BHBullet.h"
#include "BHEnemy.h"
#include "ObjectPool.h"
#include "Singleton.h"

class PoolManager : public Singleton<PoolManager>
{
    ObjectPool<BHBullet> playerBulletPool;
    ObjectPool<BHBullet> enemyBulletPool;
    ObjectPool<BHEnemy> enemyPool;
public:
    void Init();
    void Update(float dt);
    void Release();
    void Render();
    ObjectPool<BHBullet>* GetPlayerBulletPool() { return &playerBulletPool; }
    ObjectPool<BHBullet>* GetEnemyBulletPool() { return &enemyBulletPool; }
    ObjectPool<BHEnemy>* GetEnemyPool() { return &enemyPool; }
};
