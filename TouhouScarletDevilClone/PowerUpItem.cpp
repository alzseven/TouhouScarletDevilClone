#include "PowerUpItem.h"
#include "ShapeManager.h"
#include "Shape.h"
#include "D2DImage.h"
#include "PowerUpItemBehavior.h"
#include "GameStateManager.h"
#include "CircleCollisionManager.h"

void PowerUpItem::Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle)
{
    this->hitRadius = hitRadius;
    this->shape = ShapeManager::GetInstance()->FindShape(shapeKey);
    this->position = pos;
    this->radianAngle = radianAngle;
    this->isAlive = true;

    point = 0;
    isItemGet = false;
    speedY = -400.0f;
    gravity = 400.0f;
    itemBehavior = new PowerUpItemBehavior(1);
    SetCollisionLayer(LAYER_ITEM, LAYER_PLAYER);
}

void PowerUpItem::Update(float dt)
{
    if (!isAlive) return;
    Move(dt);
}

void PowerUpItem::Render(HDC hdc)
{
    if (!isAlive || !shape || !shape->GetImage()) return;
    shape->GetImage()->Render(position.x, position.y);
}

void PowerUpItem::OnHit(ICollideable* hitObject)
{
    if (hitObject->GetLayer() == LAYER_PLAYER)
    {
        isItemGet = true;
        isAlive = false;

        CircleCollisionManager::GetInstance()->RemoveCollisionObject(this);

        if (gameState && itemBehavior)
            itemBehavior->OnCollect(gameState);
    }
}

void PowerUpItem::Move(float dt)
{
    if (isGoingUpItem)
    {
        speedY += gravity * dt;
        position.y += speedY * dt;
        if (speedY >= 0.0f)
        {
            isGoingUpItem = false;
            gravity = 0.0f;
        }
    }
    else
    {
        position.y += 130.0f * dt;
    }
}

void PowerUpItem::Move(float angle, float speed, float dt)
{
}

void PowerUpItem::Release()
{
}

void PowerUpItem::Shoot(FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate)
{
}
