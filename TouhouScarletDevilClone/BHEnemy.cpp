#include "BHEnemy.h"

#include "BHBullet.h"
#include "BHObjectController.h"
#include "CommonFunction.h"
#include "IBHObjectControllerState.h"
#include "Image.h"
// #include "IPatternInfo.h"

void BHEnemy::Init(Image* image, float hit, FPOINT position, float radianAngle)
{
    BHObject::Init(image, hit, position, radianAngle);

    BHObjectInitialMove* moveState = new BHObjectInitialMove();
    moveState->Init(this, 10.f);
    moveState->Launch(DEG_TO_RAD(radianAngle), DEG_TO_RAD(0.f), 1.f, 0.f);
    
    controller->SetStates(moveState);
    controller->Init();
    // patterns = new IPatternInfo[5];
    // currentPattern = &patterns[0];
    // currentPattern->OnEnter();
}

//TODO: Refactor as moveinfo
void BHEnemy::Move(float angle, float speed)
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
    controller->Update();
    //TODO: how do we change patterns?
}

void BHEnemy::Shoot()
{
    if (isAlive == false) return;
}

void BHEnemy::OnHit(ICircleCollideable* hitObject)
{
    // GetDamaged();
    //TODO: Determine with other way...
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
    //TODO: Do something(drop score/power ups...)
    isAlive = false;
}
