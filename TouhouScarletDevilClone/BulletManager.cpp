#include "BulletManager.h"
#include "BHBullet.h"
#include "IBulletFactory.h"

// class BulletManager;
void BulletManager::Init(int capacity)
{
    vecBullets.reserve(capacity);
}

void BulletManager::Release()
{
    for (std::vector<BHBullet*>::iterator iter = vecBullets.begin(); iter != vecBullets.end(); ++iter)
    {
        // (*iter)->Release();
        delete (*iter);
    }
    vecBullets.clear();
}

void BulletManager::Update()
{
    for (std::vector<BHBullet*>::iterator iter = vecBullets.begin(); iter != vecBullets.end(); ++iter)
    {
        (*iter)->Update();
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
    if (bulletFactory)
    {
        bulletFactory->AddBullet(&vecBullets, pos, angle);
    }
}

void BulletManager::ChangeBulletFactory(IBulletFactory* newBulletFactory)
{
    if (bulletFactory)
    {
        delete bulletFactory;
    }
    bulletFactory = newBulletFactory;
}
