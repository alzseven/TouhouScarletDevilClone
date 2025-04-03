#include "ScoreItem.h"
#include "ShapeManager.h"
#include "Shape.h"
#include "D2DImage.h"
#include "ScoreItemBehavior.h"
#include "GameStateManager.h"
#include "CircleCollisionManager.h"

void ScoreItem::Init(string shapeKey, FPOINT pos)
{
	
	this->shape = ShapeManager::GetInstance()->FindShape(shapeKey);
	if (shape) {
		this->hitRadius = shape->GetHitWidth() / 2;
	}
	this->position = pos;
	this->isAlive = true;


	point = 49200;
	isItemGet = false;
	speedY = -400.0f;
	gravity = 400.0f;
	itemBehavior = new ScoreItemBehavior(10000);
	SetCollisionLayer(LAYER_ITEM, LAYER_PLAYER);
}

void ScoreItem::Update(float dt)
{
	if (!isAlive) return;
	Move(dt);
}

void ScoreItem::Render(HDC hdc)
{
	if (!isAlive || !shape || !shape->GetImage()) return;
	shape->GetImage()->Render(position.x, position.y);
}

void ScoreItem::OnHit(ICollideable* hitObject)
{
	if (hitObject->GetLayer() == LAYER_PLAYER)
	{
		isItemGet = true;
		isAlive = false;

		CircleCollisionManager::GetInstance()->RemoveCollisionObject(this);

		if (gameState)
			itemBehavior->OnCollect(gameState);

	}
}

void ScoreItem::Move(float dt)
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
	if (position.y > WINSIZE_Y)
		isItemGet = false;
}

void ScoreItem::Move(float angle, float speed, float dt)
{
}

void ScoreItem::Release()
{
}

void ScoreItem::Shoot(string shapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate)
{
}
