#pragma once
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
    BulletShooter() = default;
    virtual ~BulletShooter() = default;
private:
    virtual BHBullet* CreateBullet(ObjectPool<BHBullet>* bulletPool, FPOINT pos, float radianAngle);

};
