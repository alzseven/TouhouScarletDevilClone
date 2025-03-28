#include "BHEnemy.h"

void BHEnemy::Init(Image* image, float hit, FPOINT position, float radianAngle)
{
    BHObject::Init(image, hit, position, radianAngle);
}

//TODO: Refactor as moveinfo
void BHEnemy::Move(FPOINT moveDirection)
{
}

void BHEnemy::Render(HDC hdc)
{
    BHObject::Render(hdc);
}

void BHEnemy::Update()
{
}

void BHEnemy::Shoot()
{
}
