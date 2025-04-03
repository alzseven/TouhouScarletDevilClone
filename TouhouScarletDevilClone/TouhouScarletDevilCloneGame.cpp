#include "TouhouScarletDevilCloneGame.h"

#include "BHEnemy.h"
#include "BHPlayer.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "BHObjectManager.h"


void TouhouScarletDevilCloneGame::Init()
{
    bgImage = ImageManager::GetInstance()->AddImage("bgImage", TEXT("Image/backGround.bmp"));

    player = BHObjectManager::GetInstance()->GetPlayer();
    player->Init("Marisa", {GAME_CENTER_X, GAME_CENTER_Y});
    D2DImage* moveImage = ImageManager::GetInstance()->AddImage("Marisa_Move_Left", TEXT("Image/Marisa_Move_Left.bmp"), 8, 1);
    player->SetMoveImage(moveImage);
    
    stageWaveManager.Init();
}

void TouhouScarletDevilCloneGame::Release(){}

void TouhouScarletDevilCloneGame::Update(float dt)
{
    if (player) player->Update(dt);

    stageWaveManager.Update(dt);
    
    BHObjectManager::GetInstance()->Update(dt);
    
    CircleCollisionManager::GetInstance()->Update();
}

void TouhouScarletDevilCloneGame::Render(HDC hdc)
{
    if (bgImage) bgImage->Render(-350,-560);

    if (player) player->Render(hdc);
    

    BHObjectManager::GetInstance()->Render();
    
    CircleCollisionManager::GetInstance()->Render(hdc);
}
