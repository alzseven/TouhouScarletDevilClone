#include "BHPlayer.h"
#include "config.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "BHObjectManager.h"
#include "Shape.h"

void BHPlayer::Init(string shapeKey, FPOINT pos)
{
    BHObject::Init(shapeKey, pos);

    moveShape = ShapeManager::GetInstance()->FindShape("marisa_left");
    moveStartShape = ShapeManager::GetInstance()->FindShape("marisa_goleft");
    subShape = ShapeManager::GetInstance()->FindShape("marisa_sub");
    
    timeElapsed = 0;
    //TODO: Initialize delay in certain value from parameter
    mainShootDelay = 0.6f;
    subShootDelay = 1.2f;
    moveDir = { 0,0 };
    isPreviousStateHorizontalMove = false;
    SetCollisionLayer(LAYER_PLAYER, LAYER_ENEMY_BULLET | LAYER_ITEM);
}

void BHPlayer::Render(HDC hdc)
{
    if (abs(moveDir.x) > FLT_EPSILON)
    {
        if (isPreviousStateHorizontalMove)
        {
            if (moveShape)
            {
                moveShape->GetImage()->Middle_RenderFrame(position.x, position.y,frameIndex,0, moveDir.x > 0);
            }
        }
        else
        {
            isPreviousStateHorizontalMove = true;
            // frameIndex = 0;
            if (moveStartShape)
            {
                moveStartShape->GetImage()->Middle_RenderFrame(position.x, position.y,frameIndex,0, moveDir.x > 0);
            }
        }

    }
    else
    {
        isPreviousStateHorizontalMove = false;
        if (shape && shape->GetImage())
        {
            //TODO: separate frameIndex
            shape->GetImage()->Middle_RenderFrame(position.x, position.y, frameIndex);
            
            // // Debug
            // const float width = shape->GetImage()->GetWidth() / shape->GetImage()->GetMaxFrameX();
            // const float height= shape->GetImage()->GetHeight() / shape->GetImage()->GetMaxFrameY();
            // shape->GetImage()->DrawRect(
            //     {position.x - width / 2, position.y - height / 2},
            //     {position.x + width / 2 , position.y + height / 2},
            //     2, 1);
        }
    }

    if (subShape)
    {
        subShape->GetImage()->Middle_RenderFrame((isPressingShift ? position.x - 10 : position.x - 30), (isPressingShift ? position.y - 15 : position.y), 1);
        subShape->GetImage()->Middle_RenderFrame((isPressingShift ? position.x + 10 : position.x + 30),(isPressingShift ? position.y - 15 : position.y), 1);
    }
    
    // if (bulletManager)
    // {
    //     bulletManager->Render(hdc);
    // }

    // if (subweaponBulletManager)
    // {
    //     subweaponBulletManager->Render(hdc);
    // }
}




void BHPlayer::Move(FPOINT moveDirection, bool isPressingShift, float dt)
{
    if (abs(moveDirection.x) <= FLT_EPSILON && abs(moveDirection.y) <= FLT_EPSILON)
    {
        // isPreviousStateHorizontalMove = false;
        return;
    }
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
    mainWeaponTimer += dt;
    subWeaponTimer += dt;
    // timeElapsed += dt;
#pragma region ARROW_INPUT
    moveDir = { 0,0 };
    // UP
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP))
    {
        moveDir.y=-1;
    }
    // LEFT
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))
    {
        moveDir.x=-1;
    }
    // DOWN
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN))
    {
        moveDir.y=1;
    }
    // RIGHT
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
    {
        moveDir.x=1;
    }
#pragma endregion
    isPressingShift = KeyManager::GetInstance()->IsStayKeyDown(VK_SHIFT);
    
    Move(moveDir, isPressingShift, dt);
    
    MoveBackToBorder();

    frameIndex = frameIndex + 1 >= 4 ? 0 : frameIndex + 1;
    
    if (KeyManager::GetInstance()->IsStayKeyDown(0x5A))
    {
        Shoot("Jewel_blue",{position.x , position.y - 10},DEG_TO_RAD(-90.f),DEG_TO_RAD(0.f),600.f,0.f);
        ShootSubWeapon(isPressingShift);
    }
}

void BHPlayer::OnHit(ICollideable* hitObject)
{
    
}

void BHPlayer::Shoot(string bulletShapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate)
{
    if (mainWeaponTimer >= mainShootDelay)
    {
        BHBullet* bullet = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
        bullet->Init(bulletShapeKey, init_pos);
        bullet->Launch(angle, angleRate, shootSpeed, shootSpeedRate);
        mainWeaponTimer = 0.f;
    }
}


//TODO: 
void BHPlayer::ShootSubWeapon(bool isAccumulating)
{
    if (subWeaponTimer >= subShootDelay)
    {
        BHBullet* bullet1 = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
        bullet1->Init("EllipseBullet_green",{isAccumulating ? position.x - 10 : position.x - 30,isAccumulating ? position.y - 15 : position.y });
        bullet1->Launch(DEG_TO_RAD(-90.f),DEG_TO_RAD(0.f), 300.f, 0.f);

        BHBullet* bullet2 = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
        bullet2->Init("EllipseBullet_green",{isAccumulating ? position.x + 10 : position.x + 30,isAccumulating ? position.y - 15 : position.y });
        bullet2->Launch(DEG_TO_RAD(-90.f),DEG_TO_RAD(0.f), 300.f, 0.f);
        subWeaponTimer = 0.f;
    }
}


void BHPlayer::MoveBackToBorder() {
    if (shape == nullptr) return;

    const float width = shape->GetImage()->GetWidth() / shape->GetImage()->GetMaxFrameX();
    const float height = shape->GetImage()->GetHeight() / shape->GetImage()->GetMaxFrameY();

    const float right = position.x + width / 2;
    const float left = position.x - width / 2;
    const float top = position.y - height / 2;
    const float bottom = position.y + height / 2;

    if (left < GAME_LEFT) position.x = GAME_LEFT + width / 2;
    if (right > GAME_RIGHT) position.x = GAME_RIGHT - width / 2;
    if (top < GAME_TOP) position.y = GAME_TOP + height / 2;
    if (bottom > GAME_BOTTOM) position.y = GAME_BOTTOM - height / 2;
}

void BHPlayer::Release()
{
    // if (bulletManager)
    // {
    //     bulletManager->Release();
    //     delete bulletManager;
    // }
}