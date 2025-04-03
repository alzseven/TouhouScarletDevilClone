#include "BHObject.h"

#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "Shape.h"

BHObject::BHObject()
{
	CircleCollisionManager::GetInstance()->AddCollisionObject(this);
}

void BHObject::Init(string shapeKey, FPOINT pos)
{
	this->shape = ShapeManager::GetInstance()->FindShape(shapeKey);
	if (shape)
	{
		//TODO:
		this->hitRadius = shape->GetHitWidth() / 2;
	}
	this->position = pos;
	isAlive = true;
}

void BHObject::Render(HDC hdc)
{
	if (shape && shape->GetImage())
	{
		shape->GetImage()->Render(position.x, position.y);
#pragma region DEBUG_RENDER_SHAPE
		// Debug
		// const float width = shape->GetImage()->GetWidth() / shape->GetImage()->GetMaxFrameX();
		// const float height= shape->GetImage()->GetHeight() / shape->GetImage()->GetMaxFrameY();
		// shape->GetImage()->DrawRect(
		// 	{position.x - width / 2, position.y - height / 2},
		// 	{position.x + width / 2 , position.y + height / 2},
		// 	2, 1);
#pragma endregion
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