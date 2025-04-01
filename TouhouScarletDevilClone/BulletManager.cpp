#include "BulletManager.h"
#include "BHBullet.h"

#include "BulletShooter.h"

// class BulletManager;
void BulletManager::Init(int capacity)
{
    // vecBullets.reserve(capacity);
    bulletPool = new ObjectPool<BHBullet>();
    bulletPool->Init(1000);

    bulletShooter = new BulletShooter();
    bulletShooter->Init();
    
}

void BulletManager::Release()
{

    bulletPool->Clear();
    
    // for (std::vector<BHBullet*>::iterator iter = vecBullets.begin(); iter != vecBullets.end(); ++iter)
    // {
    //     (*iter)->Release();
    //     // delete (*iter);
    // }
    // vecBullets.clear();
    if (bulletShooter)
    {
        bulletShooter->Release();
        delete bulletShooter;
    }
}

void BulletManager::Update(float dt)
{
    vector<BHBullet*> active = bulletPool->GetActive();
    for (std::vector<BHBullet*>::iterator iter = active.begin() ; iter != active.end(); ++iter)
    {
        (*iter)->Update(dt);
    }
}

void BulletManager::Render(HDC hdc)
{
    vector<BHBullet*> active = bulletPool->GetActive();
    for (std::vector<BHBullet*>::iterator iter = active.begin() ; iter != active.end(); ++iter)
    {
        (*iter)->Render(hdc);
    }
}

// void BulletManager::AddBullet(FPOINT pos, float angle)
// {
//     if (bulletShooter)
//     {
//         bulletShooter->AddBullet(bulletPool, pos, angle);
//     }
// }


void BulletManager::ChangeBulletShooter(BulletShooter* newShooter)
{
    if (bulletShooter)
    {
        delete bulletShooter;
    }
    bulletShooter = newShooter;
}

void BulletManager::AddBullet(FPOINT pos, float angle, float angle_rate, float shoot_speed, float shoot_speed_rate)
{
    if (bulletShooter)
    {
        bulletShooter->AddBullet(bulletPool, pos, angle,angle_rate, shoot_speed, shoot_speed_rate);
    }
}
