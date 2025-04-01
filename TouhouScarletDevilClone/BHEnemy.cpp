#include "BHEnemy.h"

#include "BHBullet.h"
// #include "BHObjectController.h"
#include "CommonFunction.h"
// #include "IBHObjectControllerState.h"
#include "BulletManager.h"
#include "D2DImage.h"
#include "EnemyController.h"
// #include "Image.h"
#include "CircleCollisionManager.h"
#include "IObjectActionPattern.h"
#include "Shape.h"
// #include "IPatternInfo.h"

// void BHEnemy::Init(D2DImage* image, float hit, FPOINT position, float radianAngle)
// {
//     BHObject::Init(image, hit, position, radianAngle);
//
//     bulletManager = new BulletManager();
//     bulletManager->Init();
//     SetCollisionLayer(LAYER_ENEMY, LAYER_PLAYER_BULLET);
//
//     //TEST
//     ec = new EnemyController();
//     ec->SetTarget(this);
//     ec->Init();
// }

void BHEnemy::Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle)
{
    this->hitRadius = hitRadius;
    this->shape =  ShapeManager::GetInstance()->FindShape(shapeKey);
    // this->shape = ShapeManager::GetInstance()->AddShapeCircle(shapeKey,TEXT("enemy1.png"),hitRadius);
    this->position = pos;
    this->radianAngle = radianAngle;
    isAlive = true;
    CircleCollisionManager::GetInstance()->AddCollisionObject(this);

    bulletManager = new BulletManager();
    bulletManager->Init();
    SetCollisionLayer(LAYER_ENEMY, LAYER_PLAYER_BULLET);

    //TEST
    ec = new EnemyController();
    ec->SetTarget(this);
    ec->Init();
}

//TODO: Refactor as moveinfo
void BHEnemy::Move(float angle, float speed, float dt)
{
    if (isAlive == false) return;
    position.x += sin(angle) * speed * dt;
    position.y += cos(angle) * speed * dt;
}

void BHEnemy::Render(HDC hdc)
{
    static int frameIndex = 0;
    
    if (isAlive == false) return;
    if (shape && shape->GetImage())
    {
        shape->GetImage()->RenderFrame(position.x, position.y, frameIndex);
    }
    if (bulletManager)
    {
        bulletManager->Render(hdc);
    }
    
    // HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
    // // 기존 펜 받아서
    // HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    // HBRUSH oldbrush = (HBRUSH)SelectObject( hdc, GetStockObject( NULL_BRUSH ) );
    //
    // RenderRectAtCenter(hdc, position.x, position.y, 27, 36);    // 다시 원래 펜으로
    //
    // SelectObject(hdc, hOldPen);
    // SelectObject(hdc, oldbrush);
    // // 삭제
    // DeleteObject(hPen);
}

void BHEnemy::Update(float dt)
{
    if (isAlive == false) return;
    ec->Update(dt);
    
    if (bulletManager)
    {
        bulletManager->Update(dt);
    }
}

// void BHEnemy::Shoot(float angle, int shootAmount)
// {
//     if (isAlive == false) return;
//     for (int i=1; i<= shootAmount; ++i)
//     {
//         bulletManager->AddBullet(position, angle + DEG_TO_RAD(360.f / shootAmount * i));
//     }
// }

void BHEnemy::Shoot(FPOINT init_pos,
    float angle, float angleRate,
    float shootSpeed, float shootSpeedRate)
{
    if (isAlive == false) return;
    
    bulletManager->AddBullet(init_pos, angle, angleRate, shootSpeed, shootSpeedRate);
}

void BHEnemy::OnHit(ICollideable* hitObject)
{
    GetDamaged();

    // TODO: Determine with other way...
    // BHBullet* bHBullet = dynamic_cast<BHBullet*>(hitObject);
    // if (bHBullet)
    // {
    //     GetDamaged();
    // }
}

void BHEnemy::Release()
{
    // if (image)
    // {
    //     image->Release();
    //     delete image;
    // }
    // if (position)
    // {
    //     delete position;
    //     position = nullptr;
    // }
}

void BHEnemy::GetDamaged()
{
    //TODO: Do something(drop score/power ups...)
    isAlive = false;
}
