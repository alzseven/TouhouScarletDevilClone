#include "BHEnemy.h"

#include "BHBullet.h"
#include "BulletManager.h"
#include "D2DImage.h"
#include "EnemyController.h"
#include "CircleCollisionManager.h"
#include "Shape.h"


void BHEnemy::Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle)
{
    this->hitRadius = hitRadius;
    this->shape =  ShapeManager::GetInstance()->FindShape(shapeKey);
    this->position = pos;
    this->radianAngle = radianAngle;
    isAlive = true;
    SetCollisionLayer(LAYER_ENEMY, LAYER_PLAYER_BULLET);

    bulletManager = new BulletManager();
    bulletManager->Init();


    //TEST
    ec = new EnemyController();
    ec->SetTarget(this);
    ec->Init();
}


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
        shape->GetImage()->Middle_RenderFrame(position.x, position.y, frameIndex);

        // Debug
        const float width = shape->GetImage()->GetWidth() / shape->GetImage()->GetMaxFrameX();
        const float height= shape->GetImage()->GetHeight() / shape->GetImage()->GetMaxFrameY();
        shape->GetImage()->DrawRect(
            {position.x - width / 2, position.y - height / 2},
            {position.x + width / 2 , position.y + height / 2},
            2, 1);
    }
    if (bulletManager)
    {
        bulletManager->Render(hdc);
    }
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
}

void BHEnemy::GetDamaged()
{
    //TODO: Do something(drop score/power ups...)
    isAlive = false;
}
