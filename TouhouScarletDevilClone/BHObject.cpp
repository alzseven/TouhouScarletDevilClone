#include "BHObject.h"

#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "Shape.h"

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

void BHObject::Render(HDC hdc)
{
	if (shape && shape->GetImage())
	{
		shape->GetImage()->Render(position.x, position.y);
		//Debug
		// shape->GetImage()->DrawRect(
		// {position.x, position.y,},
		// { position.x + shape->GetImage()->GetWidth(), position.y + shape->GetImage()->GetHeight(),},
		// 2, 1);
	}
}

bool BHObject::IsOutofScreen()
{
	if (shape == nullptr) return false;

	const float width = shape->GetImage()->GetWidth();
	const float height = shape->GetImage()->GetHeight();

	const float right = position.x - width / 2;
	const float left = position.x + width / 2;
	const float top = position.y + height / 2;
	const float bottom = position.y - height / 2;

	if (right > GAME_RIGHT || left < GAME_LEFT
		|| bottom > GAME_BOTTOM || top < GAME_TOP)
		return true;

	return false;
}