#include "BHItem.h"
#include "D2DImage.h"
#include "Shape.h"

void BHItem::Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle)
{
	this->hitRadius = hitRadius;
	this->shape = ShapeManager::GetInstance()->FindShape(shapeKey);
	this->position = pos;
	this->radianAngle = radianAngle;
	this->isAlive = true;


	isItemGet = false;
	speedY = -400.0f;
	gravity = 400.0f;

	SetCollisionLayer(LAYER_ITEM, LAYER_PLAYER);
}

void BHItem::Update(float dt)
{
	Move(dt);
}

void BHItem::Render(HDC hdc)
{
	if (!isAlive) return;
	if (shape && shape->GetImage())
		shape->GetImage()->Render(position.x, position.y);
}

void BHItem::OnHit(ICollideable* hitObject)
{
	if (hitObject->GetLayer() == LAYER_PLAYER)
	{
		isItemGet = true;
		isAlive = false;
	}
}

void BHItem::Move(float dt)
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

void BHItem::Move(float angle, float speed, float dt)
{
}

void BHItem::Shoot(FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate)
{
}

void BHItem::Release()
{
}
