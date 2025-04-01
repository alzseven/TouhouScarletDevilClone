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
    D2DImage* image = ImageManager::GetInstance()->AddImage("Marisa_Move_Vertical",TEXT("Image/Marisa_Move_Vertical.bmp"), 108, 36);
    // if (FAILED(image->Init(TEXT("Image/Marisa_Move_Vertical.bmp"), 108, 36, 4, 1, true, RGB(255,0,255))))
    // {
    //     MessageBox(g_hWnd,
    //                TEXT("Failed to create : Image/Marisa_Move_Vertical.bmp"), TEXT("Warning"), MB_OK);
    // }
    player->Init(image, 18, {WINSIZE_X / 2, WINSIZE_Y - 30}, 90.f);
    D2DImage* moveImage = ImageManager::GetInstance()->AddImage("Marisa_Move_Left", TEXT("Image/Marisa_Move_Left.bmp"), 256, 36);
    // if (FAILED(moveImage->Init(TEXT("Image/Marisa_Move_Left.bmp"), 256, 36, 8, 1, true, RGB(255,0,255))))
    // {
    //     MessageBox(g_hWnd,
    //                TEXT("Failed to create : Image/Marisa_Move_Left.bmp"), TEXT("Warning"), MB_OK);
    // }
    player->SetMoveImage(moveImage);

    enemy = new BHEnemy();

    D2DImage* image2 = ImageManager::GetInstance()->AddImage("rocket",TEXT("Image/rocket.bmp"));

    // if (FAILED(image2->Init(TEXT("Image/rocket.bmp"), 52, 64, 1, 1, true, RGB(255,0,255))))
    // {
    //     MessageBox(g_hWnd,
    //         TEXT("Failed to create : Image/rocket.bmp"), TEXT("Warning"), MB_OK);
    // }
    enemy->Init(image2, 26 , {WINSIZE_X / 2, 100}, 90.f);
}

void TouhouScarletDevilCloneGame::Release()
{
    
    // if (bgImage)
    // {
    //     bgImage->Release();
    //     delete bgImage;
    //     bgImage = nullptr;
    // }
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
    //if (player) player->Update(dt);
    //if (enemy) enemy->Update(dt);
    CircleCollisionManager::GetInstance()->Update();
}

void TouhouScarletDevilCloneGame::Render(HDC hdc)
{
    if (bgImage) bgImage->Render(-WINSIZE_X / 2, -WINSIZE_Y / 2);
    //if (player) player->Render(hdc);
    //if (enemy) enemy->Render(hdc);
    CircleCollisionManager::GetInstance()->Render(hdc);
}
