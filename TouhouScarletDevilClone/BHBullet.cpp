#include "BHBullet.h"

#include "CircleCollisionManager.h"
#include "CommonFunction.h"
#include "D2DImage.h"
#include "Shape.h"

void BHBullet::Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle)
{
	this->hitRadius = hitRadius;
	this->shape = ShapeManager::GetInstance()->FindShape(shapeKey);
	this->position = pos;
	this->radianAngle = radianAngle;
	isAlive = true;
	CircleCollisionManager::GetInstance()->AddCollisionObject(this);
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
	// if (image)
	// {
	// 	image->Release();
	// 	delete image;
	// }
}

void BHBullet::Render(HDC hdc)
{
	if (isAlive == false) return;
	if (shape)
		shape->GetImage()->Middle_Render(position.x, position.y, imageAngle);

	
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
	// pool->ReleaseMarked();
}

void BHBullet::OnHit(ICollideable* hitObject)
{
	isAlive = false;
	Reset();
	// MarkForRelease();
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
	position = {WINSIZE_X * 2, WINSIZE_Y * 2};
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

	const float right = position.x + width;
	const float left = position.x - width;
	const float top = position.y - height;
	const float bottom = position.y + height;

	if (right < 0 || left > WINSIZE_X
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}