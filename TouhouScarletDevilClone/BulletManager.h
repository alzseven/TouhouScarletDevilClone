#pragma once
#include "config.h"

class IBulletFactory;
class BHBullet;

class BulletManager
{
private:
    vector<BHBullet*> vecBullets;
    IBulletFactory* bulletFactory;
    
public:
    void Init(int capacity = 1024);
    void Release();
    void Update();
    void Render(HDC hdc);
    void AddBullet(FPOINT pos, float angle);
    void ChangeBulletFactory(IBulletFactory* newBulletFactory);
};
