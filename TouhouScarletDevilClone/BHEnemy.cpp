#include "BHEnemy.h"

#include "BHBullet.h"
#include "D2DImage.h"
#include "EnemyController.h"
#include "CircleCollisionManager.h"
#include "BHObjectManager.h"
#include "Shape.h"


void BHEnemy::Init(string shapeKey, FPOINT pos)
{
    this->shape = ShapeManager::GetInstance()->FindShape(shapeKey);
    if (shape)
    {
        this->hitRadius = shape->GetHitWidth()/2;
    }
    this->position = pos;
    isAlive = true;
    SetCollisionLayer(LAYER_ENEMY, LAYER_PLAYER_BULLET);
    
    //TEST
    ec = new EnemyController();
    ec->SetTarget(this);
    ec->Init();
}

void BHEnemy::Init(string shapeKey, FPOINT pos, std::vector<IObjectActionPattern*> patterns)
{
    BHEnemy::Init(shapeKey, pos);
    for (std::vector<IObjectActionPattern*>::iterator it = patterns.begin(); it != patterns.end(); ++it)
    {
        ec->SetActionPatterns((*it));
    }

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
}

void BHEnemy::Update(float dt)
{
    if (isAlive == false) return;
    ec->Update(dt);
}

void BHEnemy::Shoot(string bulletShapeKey, FPOINT init_pos,
    float angle, float angleRate,
    float shootSpeed, float shootSpeedRate)
{
    if (isAlive == false) return;

    BHBullet* bullet = BHObjectManager::GetInstance()->GetEnemyBulletPool()->Allocate();
    bullet->Init(bulletShapeKey, init_pos);
    bullet->Launch(angle, angleRate, shootSpeed, shootSpeedRate);
}

void BHEnemy::OnHit(ICollideable* hitObject)
{
    GetDamaged(1);
}

void BHEnemy::Release()
{
    if (ec) delete ec;
}

void BHEnemy::GetDamaged(int damage)
{
    //TODO: Do something(drop score/power ups...)
    isAlive = false;
}
