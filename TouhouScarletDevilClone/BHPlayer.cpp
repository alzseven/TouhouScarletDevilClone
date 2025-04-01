#include "BHPlayer.h"
#include "config.h"
// #include "BulletManager.h"
#include "CommonFunction.h"
// #include "IBulletFactory.h"
#include "BulletManager.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "Shape.h"
// #include "Image.h"
// #include "BHEnemy.h"
// #include "BHBullet.h"

void BHPlayer::Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle)
{
    this->hitRadius = hitRadius;
    this->shape =  ShapeManager::GetInstance()->FindShape("Marisa");
    this->position = pos;
    this->radianAngle = radianAngle;
    isAlive = true;
    CircleCollisionManager::GetInstance()->AddCollisionObject(this);

    //TODO : Separate with weapon system?
    bulletManager = new BulletManager();
    bulletManager->Init();

    timeElapsed = 0;
    //TODO: Initialize delay in certain value from parameter
    shootDelay = 0.5f;
    moveDir = { 0,0 };
    SetCollisionLayer(LAYER_PLAYER, LAYER_ENEMY_BULLET | LAYER_ITEM);
}


// void BHPlayer::Init(D2DImage* image, float hit, FPOINT position, float radianAngle)
// {
//     BHObject::Init(image, hit, position, radianAngle);
//     
//     //TODO : Separate with weapon system?
//     bulletManager = new BulletManager();
//     bulletManager->Init();
//
//     timeElapsed = 0;
//     //TODO: Initialize delay in certain value from parameter
//     shootDelay = 0.5f;
//     
//     // subweaponBulletManager = new BulletManager();
//     // SubWeaponFactory = new MarisaSubWeaponBulletFactory();
//     // subweaponBulletManager->Init();
//     // subweaponBulletManager->ChangeBulletFactory(SubWeaponFactory);
//     //
//
//     moveDir = { 0,0 };
//     SetCollisionLayer(LAYER_PLAYER, LAYER_ENEMY_BULLET | LAYER_ITEM);
// }

void BHPlayer::Render(HDC hdc)
{
    if (abs(moveDir.x) > FLT_EPSILON)
    {
        if (moveImage)
        {
            moveImage->RenderFrame(position.x, position.y,frameIndex,0, moveDir.x > 0);
        }
    }
    else
    {
        if (shape && shape->GetImage())
        {
            //TODO: separate frameIndex
            shape->GetImage()->RenderFrame(position.x, position.y,frameIndex);
        }
        // if (image) {
        //     image->RenderFrame(position.x, position.y,frameIndex);
        // }
    }

    // HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
    // // 기존 펜 받아서
    // HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    // HBRUSH oldbrush = (HBRUSH)SelectObject( hdc, GetStockObject( NULL_BRUSH ) );
    //
    // RenderRectAtCenter(hdc, position.x, position.y, 27, 36);    // 다시 원래 펜으로
    //
    // SelectObject(hdc, hOldPen);
    // SelectObject(hdc, oldbrush);
    // // 삭제
    // DeleteObject(hPen);

    if (bulletManager)
    {
        bulletManager->Render(hdc);
    }

    // if (subweaponBulletManager)
    // {
    //     subweaponBulletManager->Render(hdc);
    // }
}




void BHPlayer::Move(FPOINT moveDirection, bool isPressingShift, float dt)
{
    if (abs(moveDirection.x) <= FLT_EPSILON && abs(moveDirection.y) <= FLT_EPSILON) return;

    float angle = atan2(moveDirection.x , moveDirection.y);
    
    //TODO: SetSpeed;
    Move(angle,(isPressingShift ? 25.f : 50.f), dt);
}

void BHPlayer::Move(float angle, float speed, float dt)
{
    position.x += sin(angle) * speed * dt;
    position.y += cos(angle) * speed * dt;
}


//TOOD: get deltaTime from param
void BHPlayer::Update(float dt)
{
    // timeElapsed += TEMP_DELTA_TIME;
#pragma region WASD_INPUT
    moveDir = { 0,0 };
    // W
    if (KeyManager::GetInstance()->IsStayKeyDown(0x57))
    {
        moveDir.y=-1;
    }
    // A
    if (KeyManager::GetInstance()->IsStayKeyDown(0x41))
    {
        moveDir.x=-1;
    }
    // S
    if (KeyManager::GetInstance()->IsStayKeyDown(0x53))
    {
        moveDir.y=1;
    }
    // D
    if (KeyManager::GetInstance()->IsStayKeyDown(0x44))
    {
        moveDir.x=1;
    }
#pragma endregion
    bool isPressingShift = KeyManager::GetInstance()->IsStayKeyDown(VK_SHIFT);
    
    Move(moveDir, isPressingShift, dt);
    
    MoveBackToBorder();

    frameIndex = frameIndex + 1 >= 4 ? 0 : frameIndex + 1;

    if (bulletManager)
    {
        bulletManager->Update(dt);
        if (KeyManager::GetInstance()->IsStayKeyDown(0x5A))
        {
            Shoot(position,DEG_TO_RAD(-90.f),DEG_TO_RAD(0.f),50.f,0.f);
            ShootSubWeapon(isPressingShift);
        }
        // if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
        // {
        //     bulletManager->ChangeBulletFactory(level2BulletFactory);
        // }
    }

    // if (subweaponBulletManager)
    // {
    //     subweaponBulletManager->Update();
    // }
}

void BHPlayer::OnHit(ICollideable* hitObject)
{
    int a = 0;
}

void BHPlayer::Shoot(float angle, int shootAmount)
{
    // if (timeElapsed >= shootDelay)
    // {
    bulletManager->AddBullet(position, angle);
    //     
    //     timeElapsed = 0.f;
    // }
}

void BHPlayer::Shoot(FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate)
{
    bulletManager->AddBullet(init_pos, angle, angleRate, shootSpeed, shootSpeedRate);
}


//TODO: 
void BHPlayer::ShootSubWeapon(bool isAccumulating)
{
    // subweaponBulletManager->AddBullet((isAccumulating ? FPOINT{position.x + 15, position.y - 15} : FPOINT{position.x + 45, position.y + 15}), DEG_TO_RAD(-90.f));
        
    // timeElapsed = 0.f;

}


void BHPlayer::MoveBackToBorder() {
    if (shape == nullptr) return;

    const float width = shape->GetImage()->GetWidth();
    const float height = shape->GetImage()->GetHeight();

    const float right = position.x + width / 2;
    const float left = position.x - width / 2;
    const float top = position.y - height / 2;
    const float bottom = position.y + height / 2;

    if (right < 0) position.x = width / 2;
    if (left > WINSIZE_X) position.x = WINSIZE_X - width / 2;
    if (top < 0) position.y = height / 2;
    if (bottom > WINSIZE_Y) position.y = WINSIZE_Y - height / 2;
}

void BHPlayer::Release()
{
    if (bulletManager)
    {
        bulletManager->Release();
        delete bulletManager;
    }
}