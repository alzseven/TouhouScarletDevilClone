#include "BulletShooter.h"
#include "BHBullet.h"
// #include "Image.h"
#include "ImageManager.h"

void BulletShooter::Init()
{
    // bulletPool = new ObjectPool<BHBullet>();
    // bulletPool->Init(1000);
}

void BulletShooter::AddBullet(ObjectPool<BHBullet>* bulletPool, FPOINT pos, float radianAngle)
{
    BHBullet* bullet = CreateBullet(bulletPool, pos, radianAngle);

    // vecBullets->push_back(bullet);
    // int size = sizeof(bullets) / sizeof(*bullets);
    // for (int i=0; i < bullets.second; ++i)
    // {
    //     vecBullets->push_back(&bullets.first[i]);
    // }
}

void BulletShooter::Release()
{
    // if(bulletPool != nullptr)
    // {
    //     bulletPool->Clear();
    //     delete bulletPool;
    // }
}

BHBullet* BulletShooter::CreateBullet(ObjectPool<BHBullet>* bulletPool, FPOINT pos, float radianAngle)
{
    // D2DImage* image = ImageManager::GetInstance()->AddImage("Marisa_Bullet",TEXT("Image/Marisa_Bullet.bmp"));
    // if (FAILED(image->Init(TEXT("Image/Marisa_Bullet.bmp"), 16, 32, 1, 1, true, RGB(255,0,255))))
    // {
    //     MessageBox(g_hWnd,
    //         TEXT("Image/Marisa_Bullet.bmp 생성 실패"), TEXT("경고"), MB_OK);
    // }
    BHBullet* bullet = bulletPool->Allocate();
    bullet->Init("Marisa_Bullet", 16.f, {pos.x, pos.y}, radianAngle);
    bullet->Launch(0 , 0 ,40.f, pos.y > WINSIZE_Y / 2);
    bullet->SetPool(bulletPool);
    return bullet;
}
