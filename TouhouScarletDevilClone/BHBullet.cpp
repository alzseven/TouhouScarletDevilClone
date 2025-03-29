#include "BHBullet.h"

#include "CommonFunction.h"
#include "Image.h"

void BHBullet::Init(Image* image, float hit, FPOINT position, float radianAngle)
{
	BHObject::Init(image, hit, position, radianAngle);
}

void BHBullet::Init(Image* image, float hit, FPOINT position, float radianAngle, float angleRate, float speedRate,
	float movementSpeed)
{
	Init(image, hit, position, radianAngle);
	this->AngleRate = angleRate;
	this->SpeedRate = speedRate;
	this->movementSpeed = movementSpeed;
}

void BHBullet::Release()
{
	if (image)
	{
		image->Release();
		delete image;
	}
	if (position)
	{
		delete position;
		position = nullptr;
	}
}

void BHBullet::Render(HDC hdc)
{
	BHObject::Render(hdc);
	RenderEllipseAtCenter(hdc, position->x, position->y, hit*2, hit*2);
}

void BHBullet::Update()
{
	Move(radianAngle, movementSpeed);
	
	// add angularaccel to radAngle
	radianAngle += AngleRate;
	
	// add accel to movementSpeed;
	movementSpeed += SpeedRate;
	
	//TODO: Check if bullet go out of screen
}

void BHBullet::OnHit(ICircleCollideable* hitObject)
{
	
}

void BHBullet::Move(float angle, float speed)
{
	// update position with using angle and movement speed
	position->x += speed * cosf(angle);
	position->y += speed * sinf(angle);


}

