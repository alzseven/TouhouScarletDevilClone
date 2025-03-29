#include "Missile.h"
#include "D2DImage.h"

Missile::Missile()
{
	image = ImageManager::GetInstance()->AddImage("Missile", TEXT("Image/Marisa_Bullet.bmp"));
}

void Missile::Init(FPOINT pos, float angle, float angleRate, float speed, float speedRate)
{
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
	FPOINT next = { cosf(angle) * speed ,sinf(angle) * speed };
	imageAngle = atan2(next.x, next.y);
	imageAngle = imageAngle * (180.0f / 3.14159265f);
	pos.x += next.x;
	pos.y += next.y;
}

void Missile::Render()
{
	image->Middle_Render(pos.x, pos.y, imageAngle);
}

void Missile::Release()
{
}
