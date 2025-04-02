#include "BulletShooter.h"
#include "BHBullet.h"
// #include "Image.h"
#include "ImageManager.h"
#include "PoolManager.h"

void BulletShooter::Init()
{

}

void BulletShooter::Release()
{
}

BHBullet* BulletShooter::CreateBullet(FPOINT pos, float angle, float angle_rate,
    float shoot_speed, float shoot_speed_rate)
{
    BHBullet* bullet = pos.y > WINSIZE_Y / 2 ? PoolManager::GetInstance()->GetPlayerBulletPool()->Allocate() : PoolManager::GetInstance()->GetEnemyBulletPool()->Allocate();
    bullet->Init("kunai", 16.f, {pos.x, pos.y}, angle);
    bullet->Launch(angle_rate , shoot_speed_rate ,shoot_speed, pos.y > WINSIZE_Y / 2);
    // bullet->SetPool(object_pool);
    return bullet;
}

void BulletShooter::AddBullet(FPOINT pos, float angle, float angle_rate,
                              float shoot_speed, float shoot_speed_rate)
{
    BHBullet* bullet = CreateBullet(pos, angle, angle_rate, shoot_speed, shoot_speed_rate);
}
