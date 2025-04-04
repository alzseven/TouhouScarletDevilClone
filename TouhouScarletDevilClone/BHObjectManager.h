#pragma once

#include "BHBoss.h"
#include "BHBullet.h"
#include "BHEnemy.h"
#include "BHPlayer.h"
#include "ObjectPool.h"
#include "Singleton.h"

class BHObjectManager : public Singleton<BHObjectManager>
{
    BHPlayer player;
    ObjectPool<BHBullet> playerBulletPool;
    ObjectPool<BHBullet> enemyBulletPool;
    ObjectPool<BHEnemy> enemyPool;
    ObjectPool<BHBoss> bossPool;
    vector<BHItem*>* items;
public:
    void Init();
    void Update(float dt);
    void Release();
    void Render();
    BHPlayer* GetPlayer() { return &player; }
    ObjectPool<BHBullet>* GetPlayerBulletPool() { return &playerBulletPool; }
    ObjectPool<BHBullet>* GetEnemyBulletPool() { return &enemyBulletPool; }
    ObjectPool<BHEnemy>* GetEnemyPool() { return &enemyPool; }
    ObjectPool<BHBoss>* GetBossPool() { return &bossPool; }
    vector<BHItem*>* GetItems() const { return items; }
    void ClearEnemyBullets();
};
