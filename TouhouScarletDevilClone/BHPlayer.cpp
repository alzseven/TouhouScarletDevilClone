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

    moveSpeed = 130.f;
    slowSpeed = 60.f;
    lv = 5;
    //µô·¹ÀÌ
    mainShootDelay[0] = 0.2f;
    mainShootDelay[1] = 0.2;
    mainShootDelay[2] = 0.2;
    mainShootDelay[3] = 0.15;
    mainShootDelay[4] = 0.15;
    mainShootDelay[5] = 0.15;
    mainShootDelay[6] = 0.15;
    mainShootDelay[7] = 0.15;
    mainShootDelay[8] = 0.15;

    subShootDelay[0] = 0.0f;
    subShootDelay[1] = 0.8f;
    subShootDelay[2] = 0.6f;
    subShootDelay[3] = 0.6;
    subShootDelay[4] = 0.5;
    subShootDelay[5] = 0.5;
    subShootDelay[6] = 0.3;
    subShootDelay[7] = 0.3;
    subShootDelay[8] = 0.3;

    //°¹¼ö
    mainShootCount[0] = 1;
    mainShootCount[1] = 1;
    mainShootCount[2] = 1;
    mainShootCount[3] = 1;
    mainShootCount[4] = 1;
    mainShootCount[5] = 2;
    mainShootCount[6] = 2;
    mainShootCount[7] = 2;
    mainShootCount[8] = 3;

    subShootCount[0] = 0;
    subShootCount[1] = 1;
    subShootCount[2] = 1;
    subShootCount[3] = 1;
    subShootCount[4] = 1;
    subShootCount[5] = 1;
    subShootCount[6] = 1;
    subShootCount[7] = 2;
    subShootCount[8] = 2;

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
    float currentSpeed = isPressingShift ? slowSpeed : moveSpeed;
    position.x += sin(angle) * currentSpeed * dt;
    position.y += cos(angle) * currentSpeed * dt;
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
        
        Shoot("marisa_mainbullet", { position.x , position.y - 10 }, DEG_TO_RAD(-90), DEG_TO_RAD(0.f), 600.f, 0.f);
        
        
        ShootSubWeapon(isPressingShift);
    }
}

void BHPlayer::OnHit(ICollideable* hitObject)
{
    
}

void BHPlayer::Shoot(string bulletShapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate)
{
    if (mainWeaponTimer >= mainShootDelay[lv])
    {
        
        float shootAngle = 0;
        for (int i = 0; i < mainShootCount[lv]; i++)
        {
            BHBullet* bullet = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
            bullet->Init(bulletShapeKey, init_pos);
            if (mainShootCount[lv] % 2 == 0) shootAngle = -90 + (i - mainShootCount[lv] / 2 + 0.5f) * 3.0f;
            else shootAngle = -90 + (i - mainShootCount[lv] / 2) * 3.0f;
            bullet->Launch(DEG_TO_RAD(shootAngle), angleRate, shootSpeed, shootSpeedRate);
        }
        
        
        
        mainWeaponTimer = 0.f;
    }
}


//TODO: 
void BHPlayer::ShootSubWeapon(bool isAccumulating)
{
    if (subWeaponTimer >= subShootDelay[lv])
    {
        float shootAngle = 0;
        for (int i = 0; i < subShootCount[lv]; i++)
        {
            if (subShootCount[lv] % 2 == 0) shootAngle = -90 + (i - subShootCount[lv] / 2 + 0.5f) * 3.0f;
            else shootAngle = -90 + (i - subShootCount[lv] / 2) * 3.0f;
            BHBullet* bullet1 = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
            bullet1->Init("marisa_subbullet", { isAccumulating ? position.x - 10 : position.x - 30,isAccumulating ? position.y - 15 : position.y });
            bullet1->Launch(DEG_TO_RAD(shootAngle), DEG_TO_RAD(0.f), 500.f, 0.f);
            BHBullet* bullet2 = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
            bullet2->Init("marisa_subbullet", { isAccumulating ? position.x + 10 : position.x + 30,isAccumulating ? position.y - 15 : position.y });
            bullet2->Launch(DEG_TO_RAD(shootAngle), DEG_TO_RAD(0.f), 500.f, 0.f);
            subWeaponTimer = 0.f;
        }
        
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

void BHPlayer::setLV(int power)
{
    if (power == 128) lv = 8;
    else if (power >= 96) lv = 7;
    else if (power >= 80) lv = 6;
    else if (power >= 64) lv = 5;
    else if (power >= 48) lv = 4;
    else if (power >= 32) lv = 3;
    else if (power >= 16) lv = 2;
    else if (power >= 8) lv = 1;
    else lv = 0;
}
