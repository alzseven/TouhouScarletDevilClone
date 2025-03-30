#include "BulletShooter.h"
#include "BHBullet.h"
#include "Image.h"

void BulletShooter::Init()
{
    bulletPool = new ObjectPool<BHBullet>();
    bulletPool->Init(1000);
}

void BulletShooter::AddBullet(std::vector<BHBullet*>* vecBullets, FPOINT pos, float radianAngle)
{
    BHBullet* bullet = CreateBullet(pos, radianAngle);

    vecBullets->push_back(bullet);
    // int size = sizeof(bullets) / sizeof(*bullets);
    // for (int i=0; i < bullets.second; ++i)
    // {
    //     vecBullets->push_back(&bullets.first[i]);
    // }
}

BHBullet* BulletShooter::CreateBullet(FPOINT pos, float radianAngle)
{
    Image* image = new Image();
    if (FAILED(image->Init(TEXT("Image/Marisa_Bullet.bmp"), 16, 32, 1, 1, true, RGB(255,0,255))))
    {
        MessageBox(g_hWnd,
            TEXT("Image/Marisa_Bullet.bmp 생성 실패"), TEXT("경고"), MB_OK);
    }
    BHBullet* bullet = bulletPool->Allocate();
    bullet->Init(image, 16.f, {pos.x, pos.y}, radianAngle, 0 , 0 ,40.f);
    bullet->SetPool(bulletPool);
    return bullet;
}
