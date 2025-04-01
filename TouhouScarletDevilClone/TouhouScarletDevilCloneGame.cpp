#include "TouhouScarletDevilCloneGame.h"

#include "BHEnemy.h"
#include "BHPlayer.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "ImageManager.h"


void TouhouScarletDevilCloneGame::Init()
{

    bgImage = ImageManager::GetInstance()->AddImage("bgImage", TEXT("Image/backGround.bmp"));

    player = new BHPlayer();
    // D2DImage* image = ImageManager::GetInstance()->AddImage("Marisa_Move_Vertical",TEXT("Image/Marisa_Move_Vertical.bmp"), 4,1);
    player->Init("Marisa", 18, {WINSIZE_X / 2, WINSIZE_Y - 30}, 90.f);
    D2DImage* moveImage = ImageManager::GetInstance()->AddImage("Marisa_Move_Left", TEXT("Image/Marisa_Move_Left.bmp"), 8, 1);
    player->SetMoveImage(moveImage);

    enemy = new BHEnemy();

    // D2DImage* image2 = ImageManager::GetInstance()->AddImage("rocket",TEXT("Image/rocket.bmp"));
    enemy->Init("enemy", 26 , {WINSIZE_X / 2, 100}, DEG_TO_RAD(90.f));

    // enemyFactory = new EnemyFactory;
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
    // enemyFactory->Update(dt);
    for (auto i : enemyFactory->GetActive())
    {
        i->Update(dt);
    }
    
    if (frame >= 4)frame = 0;
    if (angle > 360) angle = 0;
    
    // CircleCollisionManager::GetInstance()->Update();
}

void TouhouScarletDevilCloneGame::Render(HDC hdc)
{
    if (bgImage) bgImage->Render(-WINSIZE_X / 2,-WINSIZE_Y / 2);

    if (player) player->Render(hdc);
    
    if (enemy) enemy->Render(hdc);

    for (auto i : enemyFactory->GetActive())
    {
        i->Render(hdc);
    }
    // CircleCollisionManager::GetInstance()->Render(hdc);
}
