#pragma once
#include "BulletManager.h"
#include "config.h"
#include "ObjectPool.h"

class BHBullet;

class BulletShooter
{
private:
    // ObjectPool<BHBullet>* bulletPool;
public:
    void Init();
    void AddBullet(ObjectPool<BHBullet>* bulletPool, FPOINT pos, float radianAngle);
    
    // void AddBullet(std::vector<BHBullet*>* vecBullets, FPOINT pos, float radianAngle);
    void Release();
    BHBullet* CreateBullet(ObjectPool<BHBullet>* object_pool, FPOINT pos, float angle, float angle_rate, float shoot_speed, float shoot_speed_rate);
    void AddBullet(ObjectPool<BHBullet>* object_pool, FPOINT pos, float angle, float angle_rate, float shoot_speed, float shoot_speed_rate);
    
    BulletShooter() = default;
    virtual ~BulletShooter() = default;
private:
    virtual BHBullet* CreateBullet(ObjectPool<BHBullet>* bulletPool, FPOINT pos, float radianAngle);

};
