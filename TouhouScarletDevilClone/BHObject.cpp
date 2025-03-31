#include "BHObject.h"

#include "CircleCollisionManager.h"
#include "D2DImage.h"
// #include "Image.h"

void BHObject::Init(D2DImage* image, float hit,  FPOINT position, float radianAngle)
{
	this->image = image;
	this->position = position;
	this->radianAngle = radianAngle;
	this->hitRadius = hit;
	isAlive = true;
	CircleCollisionManager::GetInstance()->AddCollisionObject(this);
}

void BHObject::Render(HDC hdc)
{
	if (image)
	{
		image->Render(position.x, position.y);
		// image->FrameRender(hdc, position.x, position.y, 16, 32, 0, true);
	}
}

