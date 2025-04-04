#include "BHEnemy.h"

#include "BHBullet.h"
#include "D2DImage.h"
#include "EnemyController.h"
#include "CircleCollisionManager.h"
#include "BHObjectManager.h"
#include "Shape.h"
#include "ScoreItem.h"
#include "GameStateManager.h"
#include "PowerUpItem.h"



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

    MoveBackToBorder();
}

void BHEnemy::Render(HDC hdc)
{
    static int frameIndex = 0;
    
    if (isAlive == false) return;
    if (shape && shape->GetImage())
    {
        shape->GetImage()->Middle_RenderFrame(position.x, position.y, frameIndex);

        // Debug
        //const float width = shape->GetImage()->GetWidth() / shape->GetImage()->GetMaxFrameX();
        //const float height= shape->GetImage()->GetHeight() / shape->GetImage()->GetMaxFrameY();
        //shape->GetImage()->DrawRect(
        //    {position.x - width / 2, position.y - height / 2},
        //    {position.x + width / 2 , position.y + height / 2},
        //    2, 1);
    }
}

void BHEnemy::Update(float dt)
{
    if (isAlive == false) return;
    ec->Update(dt);
}

void BHEnemy::MoveBackToBorder() {
    if (shape == nullptr) return;

    const float width = shape->GetImage()->GetWidth() / shape->GetImage()->GetMaxFrameX();
    const float height = shape->GetImage()->GetHeight() / shape->GetImage()->GetMaxFrameY();

    const float right = position.x + width / 2;
    const float left = position.x - width / 2;
    const float top = position.y - height / 2;
    const float bottom = position.y + height / 2;

    if (left < GAME_LEFT) position.x = GAME_LEFT + width / 2;
    if (right > GAME_RIGHT) position.x = GAME_RIGHT - width / 2;
    if (top < GAME_TOP) position.y = GAME_TOP + height / 2;
    if (bottom > GAME_BOTTOM) position.y = GAME_BOTTOM - height / 2;
}

void BHEnemy::Shoot(string bulletShapeKey, FPOINT init_pos,
    float angle, float angleRate,
    float shootSpeed, float shootSpeedRate)
{
    if (isAlive == false) return;

    BHBullet* bullet = BHObjectManager::GetInstance()->GetEnemyBulletPool()->Allocate();
    bullet->Init(bulletShapeKey, init_pos, false);
    bullet->Launch(angle, angleRate, shootSpeed, shootSpeedRate);
}

void BHEnemy::OnHit(ICollideable* hitObject)
{
    EffectPlayer::GetInstance()->PlayEffect("Hit_white", position);
    SoundPlayer::GetInstance()->SoundOn("hit");
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
    GameStateManager::GetInstance()->GetGameState()->Score += 1000;
    // ������ ����
	if (items && gameState)
	{
        if (rand() % 2 == 0) // 50% Ȯ��
        {
            ScoreItem* item = new ScoreItem();
            item->Init("smallScore",this->position);
            item->InitGameState(gameState);
            items->push_back(item);
        }
        else
        {
            PowerUpItem* item = new PowerUpItem();
            item->Init("smallPower", this->position);
            item->InitGameState(gameState);
            items->push_back(item);
        }

	}
}
