#include "TouhouScarletDevilCloneGame.h"
#include "UI.h"
#include "BHEnemy.h"
#include "BHPlayer.h"
#include "BHItem.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "BHObjectManager.h"
#include "GameState.h"
#include "Shape.h"

void TouhouScarletDevilCloneGame::Init()
{
    bgImage = ImageManager::GetInstance()->AddImage("bgImage", TEXT("Image/backGround.bmp"));
    
    ui = new UI(&gameState);

    player = BHObjectManager::GetInstance()->GetPlayer();
    player->Init("marisa_idle", {GAME_CENTER_X, GAME_CENTER_Y});
    stageWaveManager.Init();
}

void TouhouScarletDevilCloneGame::Release()
{
    if (ui)
    {
        delete ui;
        ui = nullptr;
    }
}


void TouhouScarletDevilCloneGame::Update(float dt)
{
    if (player) player->Update(dt);
    stageWaveManager.Update(dt);

    if (ui) ui->Update(dt);
    for (auto it = items.begin(); it != items.end(); )
    {
        BHItem* item = *it;

        if (!item)
        {
            it = items.erase(it);
            continue;
        }

        // Update 전에 유효성 체크
        if (!item->IsValid() || item->IsOutofScreen())
        {
            delete item;
            it = items.erase(it);
        }
        else
        {
            item->Update(dt);
            ++it;
        }
    }
    timer++;
    /*if (timer >= 5)
    {
        frame++;
        angle++;
        timer = 0;
    }*/
    if (timer > 1000)
    {
        //SoundPlayer::GetInstance()->SoundOff("stage3_boss");
    }
    
    BHObjectManager::GetInstance()->Update(dt);
    
    CircleCollisionManager::GetInstance()->Update();
}

void TouhouScarletDevilCloneGame::Render(HDC hdc)
{
    if (bgImage) bgImage->Render(-350,-560);

    if (player) player->Render(hdc);
    for (auto it : items)
    {
        it->Render(hdc);
    }

    


    BHObjectManager::GetInstance()->Render();
    
    CircleCollisionManager::GetInstance()->Render(hdc);

    if (ui) ui->Render(hdc);
}
