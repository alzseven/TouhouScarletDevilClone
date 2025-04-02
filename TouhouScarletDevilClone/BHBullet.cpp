#include "BHBullet.h"

#include "CircleCollisionManager.h"
#include "CommonFunction.h"
#include "D2DImage.h"
#include "PoolManager.h"
#include "Shape.h"

// BHBullet::BHBullet()
// {
// 	CircleCollisionManager::GetInstance()->AddCollisionObject(this);
// }

// void BHBullet::Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle)
// {
// 	this->hitRadius = hitRadius;
// 	this->shape = ShapeManager::GetInstance()->FindShape(shapeKey);
// 	this->position = pos;
// 	this->radianAngle = radianAngle;
// 	isAlive = true;
// 	pool = PoolManager::GetInstance()->GetEnemyBulletPool();
// }

void BHBullet::Init(string shapeKey, FPOINT pos)
{
	this->shape = ShapeManager::GetInstance()->FindShape(shapeKey);
	if (shape)
	{
		//TODO:
		this->hitRadius = shape->GetHitWidth() / 2;
	}
	this->position = pos;

	isAlive = true;
	pool = PoolManager::GetInstance()->GetEnemyBulletPool();
	
	//TODO: on create
	if (pos.y > GAME_HEIGHT / 2)
	{
		SetCollisionLayer(LAYER_PLAYER_BULLET, LAYER_ENEMY);		
	}
	else
	{
		SetCollisionLayer(LAYER_ENEMY_BULLET, LAYER_PLAYER);
	}
}

void BHBullet::Launch(float angle, float angleRate, float movementSpeed, float moveSpeedRate)
{
	this->radianAngle = angle;
	this->angleRate = angleRate;
	this->movementSpeed = movementSpeed;
	this->speedRate = moveSpeedRate;
}

void BHBullet::Launch(float angleRate, float speedRate, float movementSpeed, bool isPlayerBullet)
{
	this->angleRate = angleRate;
	this->speedRate = speedRate;
	this->movementSpeed = movementSpeed;
	
	if (isPlayerBullet)
	{
		SetCollisionLayer(LAYER_PLAYER_BULLET, LAYER_ENEMY);		
	}
	else
	{
		SetCollisionLayer(LAYER_ENEMY_BULLET, LAYER_PLAYER);
	}
}

void BHBullet::Release()
{
	isAlive = false;
	Reset();
}

void BHBullet::Render(HDC hdc)
{
	if (isAlive == false) return;
	if (shape)
	{
		shape->GetImage()->Middle_Render(position.x, position.y, imageAngle);

		// Debug
		// const float width = shape->GetImage()->GetWidth() / shape->GetImage()->GetMaxFrameX();
		// const float height= shape->GetImage()->GetHeight() / shape->GetImage()->GetMaxFrameY();
		// shape->GetImage()->DrawRect(
		// 	{position.x - width / 2, position.y - height / 2},
		// 	{position.x + width / 2 , position.y + height / 2},
		// 	2, 1);
	}
}

void BHBullet::Update(float dt)
{
	if (isAlive == false) return;

	FPOINT prev = position;
	Move(radianAngle, movementSpeed, dt);
	
	imageAngle = atan2( prev.x - position.x, -prev.y + position.y);
	imageAngle = RAD_TO_DEG(imageAngle);
	
	// add angular accel to radAngle
	radianAngle += angleRate * dt;
	
	// add accel to movementSpeed;
	movementSpeed += speedRate * dt;
	
	if (IsOutofScreen())
	{
		isAlive = false;
		Reset();
		pool->Release(this);
	}
}

void BHBullet::OnHit(ICollideable* hitObject)
{
	isAlive = false;
	Reset();
	pool->Release(this);
}

void BHBullet::Move(float angle, float speed, float dt)
{
	if (isAlive == false) return;
	// update position with using angle and movement speed
	position.x += speed * cosf(angle) * dt;
	position.y += speed * sinf(angle) * dt;
}

void BHBullet::Reset()
{
	position = {0,0};
	radianAngle = 0;
	angleRate = 0;
	speedRate = 0;
	movementSpeed = 0;
}

bool BHBullet::IsOutofScreen()
{
	if (shape == nullptr) return false;

	const float width = shape->GetImage()->GetWidth();
	const float height = shape->GetImage()->GetHeight();

	const float right = position.x - width;
	const float left = position.x + width;
	const float top = position.y + height;
	const float bottom = position.y - height;

	if (right > GAME_RIGHT || left < GAME_LEFT
		|| bottom > GAME_BOTTOM || top < GAME_TOP)
		return true;

	return false;
}