#include "BHEnemy.h"

#include "BHBullet.h"
#include "CommonFunction.h"
#include "Image.h"

void BHEnemy::Init(Image* image, float hit, FPOINT position, float radianAngle)
{
    BHObject::Init(image, hit, position, radianAngle);
}

//TODO: Refactor as moveinfo
void BHEnemy::Move(FPOINT moveDirection)
{
    if (isAlive == false) return;
}

void BHEnemy::Render(HDC hdc)
{
    if (isAlive == false) return;
    if (image)
    {
        //TODO : index how, size how
        image->FrameRender(hdc, position->x, position->y, 52, 64, 0, true);
    }
    RenderEllipseAtCenter(hdc, position->x, position->y, hit*2, hit*2);
}

void BHEnemy::Update()
{
    if (isAlive == false) return;
}

void BHEnemy::Shoot()
{
    if (isAlive == false) return;
}

void BHEnemy::OnHit(ICircleCollideable* hitObject)
{
    // GetDamaged();
    BHBullet* bHBullet = dynamic_cast<BHBullet*>(hitObject);
    if (bHBullet)
    {
        GetDamaged();
    }
}

void BHEnemy::Release()
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

void BHEnemy::GetDamaged()
{
    isAlive = false;
}
