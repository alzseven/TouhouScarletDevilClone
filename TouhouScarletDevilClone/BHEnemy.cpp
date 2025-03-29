#include "BHEnemy.h"
#include "Image.h"

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
    if (image)
    {
        //TODO : index how, size how
        image->FrameRender(hdc, position.x, position.y, 52, 64, 0, true);
    }
}

void BHEnemy::Update()
{
}

void BHEnemy::Shoot()
{
}
