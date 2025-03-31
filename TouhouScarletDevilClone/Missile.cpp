#include "Missile.h"
#include "Shape.h"
#include "D2DImage.h"

Missile::Missile()
{
	
}

void Missile::Init()
{
}

void Missile::Init(string shapeId,FPOINT pos, float angle, float angleRate, float speed, float speedRate)
{
	this->shape = ShapeManager::GetInstance()->FindShape(shapeId);
	this->pos = pos;
	this->angle = angle;
	this->angleRate = angleRate;
	this->speed = speed;
	this->speedRate = speedRate;

}

void Missile::Update()
{
	speed += speedRate;
	angle += angleRate;
	FPOINT next = { cosf(DEG_TO_RAD(angle)) * speed ,sinf(DEG_TO_RAD(angle)) * speed };
	imageAngle = atan2(next.x, next.y);
	imageAngle = -imageAngle * (180.0f / 3.14159265f);
	pos.x += next.x;
	pos.y += next.y;
}

void Missile::Render()
{
	shape->image->Middle_Render(pos.x, pos.y, imageAngle);
}

void Missile::Release()
{
}

bool Missile::IsOutofScreen()
{
	float width = shape->image->GetWidth();
	float height = shape->image->GetHeight();

	float right = pos.x + width / 2;
	float left = pos.x - width / 2;
	float top = pos.y - height / 2;
	float bottom = pos.y + height / 2;

	if (right < 0 || left > WINSIZE_X
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}