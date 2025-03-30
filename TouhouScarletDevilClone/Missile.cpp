#include "Missile.h"
#include "Shape.h"
#include "D2DImage.h"

Missile::Missile()
{
	shape = ShapeManager::GetInstance()->AddShapeCircle("Missile", TEXT("Image/Marisa_Bullet.bmp"), 3.0f);
}

void Missile::Init()
{
}

void Missile::Init(FPOINT pos,float size, float angle, float angleRate, float speed, float speedRate)
{
	this->pos = pos;
	this->size = size;
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
	float right = pos.x + size / 2;
	float left = pos.x - size / 2;
	float top = pos.y - size / 2;
	float bottom = pos.y + size / 2;

	if (right < 0 || left > WINSIZE_X
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}