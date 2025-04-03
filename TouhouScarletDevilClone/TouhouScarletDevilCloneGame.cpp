#include "TouhouScarletDevilCloneGame.h"

#include "BHEnemy.h"
#include "BHPlayer.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "Shape.h"

void TouhouScarletDevilCloneGame::Init()
{

    bgImage = ImageManager::GetInstance()->AddImage("bgImage", TEXT("Image/backGround.bmp"));

    player = new BHPlayer();
    player->Init("marisa_idle", 18, {GAME_CENTER_X, GAME_CENTER_Y}, 90.f);
    //D2DImage* moveImage = ImageManager::GetInstance()->AddImage("Marisa_Move_Left", TEXT("Image/Marisa_Move_Left.bmp"), 8, 1);
    //player->SetMoveImage(moveImage);
    Shape* tshape = ShapeManager::GetInstance()->FindShape("marisa_left");
    D2DImage* timage = tshape->GetImage();
    player->SetMoveImage(timage);
    enemy = new BHEnemy();
    
    enemy->Init("marisa_idle", 26 , {GAME_CENTER_X, 100}, DEG_TO_RAD(90.f));

    enemyFactory = new ObjectPool<BHEnemy>();
    enemyFactory->Init(100);

    BHEnemy* enemy2 = enemyFactory->Allocate();
    enemy2->Init("enemy", 26, {200, 100}, DEG_TO_RAD(90.f));
}

void TouhouScarletDevilCloneGame::Release()
{

    if (enemy)
    {
        enemy->Release();
        delete enemy;
        enemy = nullptr;
    }
    if (player)
    {
        player->Release();
        delete player;
        player = nullptr;
    }

    if (enemyFactory)
    {
        enemyFactory->Clear();
        delete enemyFactory;
        enemyFactory = nullptr;
    }
}

void TouhouScarletDevilCloneGame::Update(float dt)
{
    if (player) player->Update(dt);
    if (enemy) enemy->Update(dt);

    timer++;
    if (timer >= 5)
    {
        frame++;
        angle++;
        timer = 0;
    }

    for (auto i : enemyFactory->GetActive())
    {
        i->Update(dt);
    }
    
    if (frame >= 4)frame = 0;
    if (angle > 360) angle = 0;
    
    CircleCollisionManager::GetInstance()->Update();
}

void TouhouScarletDevilCloneGame::Render(HDC hdc)
{
    if (bgImage) bgImage->Render(-350,-560);

    if (player) player->Render(hdc);
    
    if (enemy) enemy->Render(hdc);

    for (auto i : enemyFactory->GetActive())
    {
        i->Render(hdc);
    }
    CircleCollisionManager::GetInstance()->Render(hdc);
}
