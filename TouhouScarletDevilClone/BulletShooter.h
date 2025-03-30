#pragma once
#include "config.h"
#include "ObjectPool.h"

class BHBullet;

class BulletShooter
{
private:
    ObjectPool<BHBullet>* bulletPool;
public:
    void Init();
    void AddBullet(std::vector<BHBullet*>* vecBullets, FPOINT pos, float radianAngle);
    void Release();
    BulletShooter() = default;
    virtual ~BulletShooter() = default;
private:
    virtual BHBullet* CreateBullet(FPOINT pos, float radianAngle);

};
