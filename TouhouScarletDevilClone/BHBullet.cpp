#include "BHBullet.h"

#include "CommonFunction.h"
// #include "Image.h"
#include "D2DImage.h"

void BHBullet::Init(D2DImage* image, float hit, FPOINT position, float radianAngle)
{
	BHObject::Init(image, hit, position, radianAngle);
}

void BHBullet::Init(D2DImage* image, float hit, FPOINT position, float radianAngle, float angleRate, float speedRate,
	float movementSpeed)
{
	Init(image, hit, position, radianAngle);
	this->AngleRate = angleRate;
	this->SpeedRate = speedRate;
	this->movementSpeed = movementSpeed;
	//TODO:
	// if (angleRate < 0)
	// {
	// 	SetCollisionLayer(LAYER_PLAYER_BULLET, LAYER_ENEMY);		
	// }
	// else
	// {
		SetCollisionLayer(LAYER_ENEMY_BULLET, LAYER_PLAYER);
	// }

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
	BHObject::Render(hdc);
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	// 기존 펜 받아서
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH oldbrush = (HBRUSH)SelectObject( hdc, GetStockObject( NULL_BRUSH ) );
    
	RenderRectAtCenter(hdc, position.x, position.y, 27, 36);    // 다시 원래 펜으로

	SelectObject(hdc, hOldPen);
	SelectObject(hdc, oldbrush);
	// 삭제
	DeleteObject(hPen);
}

void BHBullet::Update(float dt)
{
	if (isAlive == false) return;
	Move(radianAngle, movementSpeed, dt);
	
	// add angularaccel to radAngle
	radianAngle += AngleRate * dt;
	
	// add accel to movementSpeed;
	movementSpeed += SpeedRate * dt;
	
	//TODO: Check if bullet go out of screen
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
	position = {WINSIZE_X * 2, WINSIZE_Y * 2};
	radianAngle = 0;
	AngleRate = 0;
	SpeedRate = 0;
	movementSpeed = 0;
}

