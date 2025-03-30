#include "TouhouScarletDevilCloneGame.h"

#include "BHEnemy.h"
#include "BHPlayer.h"
#include "CircleCollisionManager.h"
#include "Image.h"


void TouhouScarletDevilCloneGame::Init()
{
    bgImage = new Image();
    if (FAILED(bgImage->Init(TEXT("Image/backGround.bmp"), WINSIZE_X, WINSIZE_Y)))
    {
        MessageBox(g_hWnd,
                   TEXT("Failed to create : Image/backGround.bmp"), TEXT("Warning"), MB_OK);
    }

    player = new BHPlayer();
    Image* image = new Image();
    if (FAILED(image->Init(TEXT("Image/Marisa_Move_Vertical.bmp"), 108, 36, 4, 1, true, RGB(255,0,255))))
    {
        MessageBox(g_hWnd,
                   TEXT("Failed to create : Image/Marisa_Move_Vertical.bmp"), TEXT("Warning"), MB_OK);
    }
    // SHAPE* shape = new SHAPE{ TEXT("name"), 27, 18, image };
    player->Init(image, 18, {WINSIZE_X / 2, WINSIZE_Y - 30}, 90.f);
    Image* moveImage = new Image();
    if (FAILED(moveImage->Init(TEXT("Image/Marisa_Move_Left.bmp"), 256, 36, 8, 1, true, RGB(255,0,255))))
    {
        MessageBox(g_hWnd,
                   TEXT("Failed to create : Image/Marisa_Move_Left.bmp"), TEXT("Warning"), MB_OK);
    }
    player->SetMoveImage(moveImage);

    enemy = new BHEnemy();
    Image* image2 = new Image();
    if (FAILED(image2->Init(TEXT("Image/rocket.bmp"), 52, 64, 1, 1, true, RGB(255,0,255))))
    {
        MessageBox(g_hWnd,
            TEXT("Failed to create : Image/rocket.bmp"), TEXT("Warning"), MB_OK);
    }
    enemy->Init(image2, 26 , {WINSIZE_X / 2, 100}, 90.f);
}

void TouhouScarletDevilCloneGame::Release()
{
    if (bgImage)
    {
        bgImage->Release();
        delete bgImage;
        bgImage = nullptr;
    }
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
}

void TouhouScarletDevilCloneGame::Update(float dt)
{
    if (player) player->Update(dt);
    if (enemy) enemy->Update(dt);
    CircleCollisionManager::GetInstance()->Update();
}

void TouhouScarletDevilCloneGame::Render(HDC hdc)
{
    if (bgImage) bgImage->Render(hdc);
    if (player) player->Render(hdc);
    if (enemy) enemy->Render(hdc);
    CircleCollisionManager::GetInstance()->Render(hdc);
}
