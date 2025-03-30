#include "BHEnemy.h"

#include "BHBullet.h"
// #include "BHObjectController.h"
#include "CommonFunction.h"
// #include "IBHObjectControllerState.h"
#include "BulletManager.h"
#include "Image.h"
// #include "IPatternInfo.h"

void BHEnemy::Init(Image* image, float hit, FPOINT position, float radianAngle)
{
    BHObject::Init(image, hit, position, radianAngle);

    bulletManager = new BulletManager();
    bulletManager->Init();
    
    // BHObjectInitialMove* moveState = new BHObjectInitialMove();
    // moveState->Init(this, 10.f);
    // moveState->Launch(DEG_TO_RAD(radianAngle), DEG_TO_RAD(0.f), 1.f, 0.f);
    //
    // controller->SetStates(moveState);
    // controller->Init();
    // patterns = new IPatternInfo[5];
    // currentPattern = &patterns[0];
    // currentPattern->OnEnter();
    SetCollisionLayer(LAYER_ENEMY, LAYER_PLAYER_BULLET);

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
        image->FrameRender(hdc, position.x, position.y, 52, 64, 0, true);
    }
    if (bulletManager)
    {
        bulletManager->Render(hdc);
    }
    
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
    // 기존 펜 받아서
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH oldbrush = (HBRUSH)SelectObject( hdc, GetStockObject( NULL_BRUSH ) );
    
    RenderRectAtCenter(hdc, position.x, position.y, 27, 36);    // 다시 원래 펜으로

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, oldbrush);
    // 삭제
    DeleteObject(hPen);
}

void BHEnemy::Update(float dt)
{
    if (isAlive == false) return;
    static float elapsed;
    elapsed += dt;
    if (bulletManager)
    {
        bulletManager->Update(dt);
        if (elapsed >= 0.5f)
        {
            Shoot();
            elapsed -= 0.5f;
        }
    }
    // controller->Update();
    //TODO: how do we change patterns?
}

void BHEnemy::Shoot()
{
    if (isAlive == false) return;
    bulletManager->AddBullet(position, DEG_TO_RAD(90));
}

void BHEnemy::OnHit(ICollideable* hitObject)
{
    GetDamaged();

    // TODO: Determine with other way...
    // BHBullet* bHBullet = dynamic_cast<BHBullet*>(hitObject);
    // if (bHBullet)
    // {
    //     GetDamaged();
    // }
}

void BHEnemy::Release()
{
    // if (image)
    // {
    //     image->Release();
    //     delete image;
    // }
    // if (position)
    // {
    //     delete position;
    //     position = nullptr;
    // }
}

void BHEnemy::GetDamaged()
{
    //TODO: Do something(drop score/power ups...)
    isAlive = false;
}
