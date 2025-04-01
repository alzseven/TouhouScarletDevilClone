#include "BHObject.h"

#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "Shape.h"
// #include "Image.h"

BHObject::BHObject()
{
	CircleCollisionManager::GetInstance()->AddCollisionObject(this);
}

void BHObject::Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle)
{
	this->hitRadius = hitRadius;
	this->shape = ShapeManager::GetInstance()->AddShapeCircle(shapeKey,TEXT(" "),hitRadius);
	this->position = pos;
	this->radianAngle = radianAngle;
	isAlive = true;

}

// void BHObject::Init(D2DImage* image, float hitRadius,  FPOINT position, float radianAngle)
// {
// 	this->image = image;
// 	this->position = position;
// 	this->radianAngle = radianAngle;
// 	this->hitRadius = hitRadius;
// 	isAlive = true;
// 	CircleCollisionManager::GetInstance()->AddCollisionObject(this);
// }

void BHObject::Render(HDC hdc)
{
	if (shape && shape->GetImage())
	{
		shape->GetImage()->Render(position.x, position.y);
	}
	// if (image)
	// {
	// 	image->Render(position.x, position.y);
	// }
}

bool BHObject::IsOutofScreen()
{
	if (shape == nullptr) return false;

	const float width = shape->GetImage()->GetWidth();
	const float height = shape->GetImage()->GetHeight();

	const float right = position.x + width / 2;
	const float left = position.x - width / 2;
	const float top = position.y - height / 2;
	const float bottom = position.y + height / 2;

	if (right < 0 || left > WINSIZE_X
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}