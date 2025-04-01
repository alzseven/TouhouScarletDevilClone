#pragma once
#include "BulletManager.h"
#include "config.h"
#include "ObjectPool.h"

class BHBullet;

class BulletShooter
{

public:
    void Init();
    void Release();
    void AddBullet(ObjectPool<BHBullet>* object_pool, FPOINT pos, float angle, float angle_rate, float shoot_speed, float shoot_speed_rate);
    
    BulletShooter() = default;
    virtual ~BulletShooter() = default;
private:
    virtual BHBullet* CreateBullet(ObjectPool<BHBullet>* object_pool, FPOINT pos, float angle, float angle_rate, float shoot_speed, float shoot_speed_rate);
};
