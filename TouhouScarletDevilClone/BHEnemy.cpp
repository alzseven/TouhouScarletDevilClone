#include "BHEnemy.h"

#include "BHBullet.h"
// #include "BHObjectController.h"
#include "CommonFunction.h"
// #include "IBHObjectControllerState.h"
#include "BulletManager.h"
#include "D2DImage.h"
#include "EnemyController.h"
// #include "Image.h"
#include "IObjectActionPattern.h"
// #include "IPatternInfo.h"

void BHEnemy::Init(D2DImage* image, float hit, FPOINT position, float radianAngle)
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

    //TEST
    ec = new EnemyController();
    ec->SetTarget(this);
    ec->Init();

    
    // patterns[0] = new MoveStraightDirectionPattern();
    // patterns[0]->SetTarget(this);
    // patterns[0]->SetPatternEndTime(5.f);
    // patterns[0]->Launch(30.f,0.f,DEG_TO_RAD(90.f),DEG_TO_RAD(0.f));
    // patterns[1] = new ShootStraightPattern();
    // patterns[1]->SetTarget(this);
    // patterns[1]->SetPatternEndTime(5.f);
    // patterns[1]->SetShootParams(0.5f, 1, DEG_TO_RAD(90.f));
    // actions.push_back(patterns[0]);
    // actions.push_back(patterns[1]);
}

//TODO: Refactor as moveinfo
void BHEnemy::Move(float angle, float speed, float dt)
{
    if (isAlive == false) return;
    position.x += sin(angle) * speed * dt;
    position.y += cos(angle) * speed * dt;
}

void BHEnemy::Render(HDC hdc)
{
    if (isAlive == false) return;
    if (image)
    {
        //TODO : index how, size how
        image->Render(position.x, position.y);
        // image->FrameRender(hdc, position.x, position.y, 52, 64, 0, true);
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
    ec->Update(dt);

    // static bool isPatternValid = true;
    // static int cnt = 0;
    // static float elapsed;
    // elapsed += dt;
    // // if (isPatternValid) Move(radianAngle, 20.f, dt);
    if (bulletManager)
    {
        bulletManager->Update(dt);
        // if (elapsed >= 0.5f && isPatternValid)
        // {
        //     Shoot(DEG_TO_RAD(90.f),1);
        //     elapsed -= 0.5f;
        //     // radianAngle += DEG_TO_RAD(-10.f);
        //     cnt++;
        //     if (cnt >= 10) isPatternValid = false;
        // }
    }

    //TODO: how do we change patterns?
}

void BHEnemy::Shoot(float angle, int shootAmount)
{
    if (isAlive == false) return;
    for (int i=1; i<= shootAmount; ++i)
    {
        bulletManager->AddBullet(position, angle + DEG_TO_RAD(360.f / shootAmount * i));
    }
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
