#include "BulletShooter.h"
#include "BHBullet.h"
// #include "Image.h"
#include "ImageManager.h"
#include "Shape.h"
void BulletShooter::Init()
{

}

void BulletShooter::Release()
{
}

BHBullet* BulletShooter::CreateBullet(ObjectPool<BHBullet>* object_pool, FPOINT pos, float angle, float angle_rate,
    float shoot_speed, float shoot_speed_rate)
{
    BHBullet* bullet = object_pool->Allocate();
    Shape* sh = ShapeManager::GetInstance()->FindShape("NormalBullet_red");
    bullet->Init("NormalBullet_red", sh->GetHitHeight()/2.f, {pos.x, pos.y}, angle);
    bullet->Launch(angle_rate , shoot_speed_rate ,shoot_speed, pos.y > WINSIZE_Y / 2);
    EffectPlayer::GetInstance()->PlayEffect("NormalShoot_red", pos);
    bullet->SetPool(object_pool);
    return bullet;
}

void BulletShooter::AddBullet(ObjectPool<BHBullet>* object_pool, FPOINT pos, float angle, float angle_rate,
                              float shoot_speed, float shoot_speed_rate)
{
    BHBullet* bullet = CreateBullet(object_pool, pos, angle, angle_rate, shoot_speed, shoot_speed_rate);
}
