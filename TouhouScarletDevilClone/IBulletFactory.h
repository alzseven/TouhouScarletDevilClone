#pragma once
#include "config.h"

class Image;
class BHBullet;
class IBulletFactory
{
public:
    void AddBullet(std::vector<BHBullet*>* vecBullets, FPOINT pos, float radianAngle);
    IBulletFactory() = default;
    virtual ~IBulletFactory() = default;
private:
    virtual pair<BHBullet*, int> CreateBullet(FPOINT pos, float radianAngle) = 0;

};

class MarisaSubWeaponBulletFactory : public IBulletFactory
{
private:
    virtual pair<BHBullet*, int> CreateBullet(FPOINT pos, float radianAngle);
};


class MarisaLevel1BulletFactory : public IBulletFactory
{
private:
    virtual pair<BHBullet*, int> CreateBullet(FPOINT pos, float radianAngle);
};

class MarisaLevel2BulletFactory : public IBulletFactory
{
private:
    virtual pair<BHBullet*, int> CreateBullet(FPOINT pos, float radianAngle);
};

// class MarisaLevel3BulletFactory : public IBulletFactory
// {
// private:
//     virtual pair<BHBullet*, int> CreateBullet(FPOINT pos, float radianAngle);
// };
//
// class MarisaLevel4BulletFactory : public IBulletFactory
// {
// private:
//     virtual pair<BHBullet*, int> CreateBullet(FPOINT pos, float radianAngle);
// };
