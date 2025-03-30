#include "BHPlayer.h"
#include "config.h"
// #include "BulletManager.h"
#include "CommonFunction.h"
// #include "IBulletFactory.h"
#include "BulletManager.h"
#include "Image.h"
// #include "BHEnemy.h"
// #include "BHBullet.h"

//TODO: Initialize delay in certain value from parameter
void BHPlayer::Init(Image* image, float hit, FPOINT position, float radianAngle)
{
    BHObject::Init(image, hit, position, radianAngle);
    
    // //TODO : Separate with weapon system?
    bulletManager = new BulletManager();
    // level1BulletFactory = new MarisaLevel1BulletFactory();
    // level2BulletFactory = new MarisaLevel2BulletFactory();
    bulletManager->Init();
    // bulletManager->ChangeBulletFactory(level1BulletFactory);

    timeElapsed = 0;
    shootDelay = 0.5f;
    
    // subweaponBulletManager = new BulletManager();
    // SubWeaponFactory = new MarisaSubWeaponBulletFactory();
    // subweaponBulletManager->Init();
    // subweaponBulletManager->ChangeBulletFactory(SubWeaponFactory);
    //

    moveDir = { 0,0 };
    SetCollisionLayer(LAYER_PLAYER, LAYER_ENEMY_BULLET | LAYER_ITEM);
}

// void BHPlayer::Init(Image* image, FPOINT position, float angle)
// {
//     // this->Shape = shape;
//     this->image = image;
//     this->position = position;
//     this->radianAngleDirection = angle;
//     scale = 1;
//     imgAlpha = 1;
//     isAlive = true;
// 	frameIndex = 0;
// }

// void BHPlayer::RenderSub(HDC hdc, Image* image, float size, float fade)
// {
//     if (image) {
//         image->FrameRender(hdc, position.x, position.y, 27, 36, 0);
//     }
// }
//
void BHPlayer::Render(HDC hdc)
{
    // RenderSub(hdc, Shape->Texture, Shape->Size, 1.f);
    if (abs(moveDir.x) > FLT_EPSILON)
    {
        if (moveImage)
        {
            moveImage->FrameRender(hdc, position.x, position.y, 27, 36, frameIndex, moveDir.x < 0);
        }
    }
    else
    {
        if (image) {
            image->FrameRender(hdc, position.x, position.y, 27, 36, frameIndex);
        }
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
            Shoot();
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

void BHPlayer::Shoot()
{
    // if (timeElapsed >= shootDelay)
    // {
    //     //TODO: Separate shooting angle;
    bulletManager->AddBullet(position, DEG_TO_RAD(-90.f));
    //     
    //     timeElapsed = 0.f;
    // }
}

//TODO: 
void BHPlayer::ShootSubWeapon(bool isAccumulating)
{
    // subweaponBulletManager->AddBullet((isAccumulating ? FPOINT{position.x + 15, position.y - 15} : FPOINT{position.x + 45, position.y + 15}), DEG_TO_RAD(-90.f));
        
    // timeElapsed = 0.f;

}


void BHPlayer::MoveBackToBorder() {
    //TODO: Move back(amount of size / 2) when go out screen
    if (position.x < 0) position.x = 0;
    if (position.x > WINSIZE_X) position.x = WINSIZE_X;
    if (position.y < 0) position.y = 0;
    if (position.y > WINSIZE_Y) position.y = WINSIZE_Y;
}

// void BHPlayer::OnCollide(BHObject* objectCollided)
// {	
//     //TODO: Check collision
//     //TODO: if collides with enemy or enemy bullet, than:
//     //TODO:  alive false
//     //TODO:  do something such as invincible...
//     BHEnemy* enemy = static_cast<BHEnemy*>(objectCollided);
//     if (enemy) {
//
//         return;
//     }
//     BHBullet* bullet = static_cast<BHBullet*>(objectCollided);
//     if (bullet) {
//         //...
//
//         return;
//     }
// }

void BHPlayer::Release()
{
    if (bulletManager)
    {
        bulletManager->Release();
        delete bulletManager;
    }
    
    // if (image)
    // {
    //     image->Release();
    //     delete image;
    // }
    // if (moveImage)
    // {
    //     moveImage->Release();
    //     delete moveImage;
    // }
    // if (position)
    // {
    //     delete position;
    //     position = nullptr;
    // }
}