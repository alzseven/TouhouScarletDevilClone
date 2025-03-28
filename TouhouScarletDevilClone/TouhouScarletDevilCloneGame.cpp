#include "TouhouScarletDevilCloneGame.h"

#include "BHPlayer.h"
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
    if (FAILED(image->Init(TEXT("Image/Marisa_Move_Vertical.bmp"), 216, 72, 4, 1, true, RGB(255,0,255))))
    {
        MessageBox(g_hWnd,
            TEXT("Failed to create : Image/Marisa_Move_Vertical.bmp"), TEXT("Warning"), MB_OK);
    }
    // SHAPE* shape = new SHAPE{ TEXT("name"), 27, 18, image };
    player->Init(image, 54 , {WINSIZE_X / 2, WINSIZE_Y - 30}, 90.f);
    Image* moveImage = new Image();
    if (FAILED(moveImage->Init(TEXT("Image/Marisa_Move_Left.bmp"), 512, 72, 8, 1, true, RGB(255,0,255))))
    {
        MessageBox(g_hWnd,
            TEXT("Failed to create : Image/Marisa_Move_Left.bmp"), TEXT("Warning"), MB_OK);
    }
    player->SetMoveImage(moveImage);
}

void TouhouScarletDevilCloneGame::Release()
{
    if (player) {
        delete player;
        player = nullptr;
    }

    if (bgImage)
    {
        bgImage->Release();
        delete bgImage;
        bgImage = nullptr;
    }
}

void TouhouScarletDevilCloneGame::Update()
{
    player->Update();
}

void TouhouScarletDevilCloneGame::Render(HDC hdc)
{
    bgImage->Render(hdc);
    player->Render(hdc);
}
