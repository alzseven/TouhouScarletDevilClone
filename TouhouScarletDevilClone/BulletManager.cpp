#include "BulletManager.h"
#include "BHBullet.h"

#include "BulletShooter.h"

// class BulletManager;
void BulletManager::Init(int capacity)
{
    vecBullets.reserve(capacity);
    bulletShooter = new BulletShooter();
    bulletShooter->Init();
}

void BulletManager::Release()
{
    for (std::vector<BHBullet*>::iterator iter = vecBullets.begin(); iter != vecBullets.end(); ++iter)
    {
        (*iter)->Release();
        // delete (*iter);
    }
    vecBullets.clear();
    if (bulletShooter)
    {
        delete bulletShooter;
    }
}

void BulletManager::Update(float dt)
{
    for (std::vector<BHBullet*>::iterator iter = vecBullets.begin(); iter != vecBullets.end(); ++iter)
    {
        (*iter)->Update(dt);
    }
}

void BulletManager::Render(HDC hdc)
{
    for (std::vector<BHBullet*>::iterator iter = vecBullets.begin(); iter != vecBullets.end(); ++iter)
    {
        (*iter)->Render(hdc);
    }
}

void BulletManager::AddBullet(FPOINT pos, float angle)
{
    if (bulletShooter)
    {
        bulletShooter->AddBullet(&vecBullets, pos, angle);
    }
}

void BulletManager::ChangeBulletShooter(BulletShooter* newShooter)
{
    if (bulletShooter)
    {
        delete bulletShooter;
    }
    bulletShooter = newShooter;
}
