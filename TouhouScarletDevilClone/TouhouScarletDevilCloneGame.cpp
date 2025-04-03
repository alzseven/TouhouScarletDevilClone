#include "TouhouScarletDevilCloneGame.h"
#include "UI.h"
#include "BHEnemy.h"
#include "BHPlayer.h"
#include "BHItem.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "GameState.h"
#include "Shape.h"
#include "PoolManager.h"


void TouhouScarletDevilCloneGame::Init()
{

    bgImage = ImageManager::GetInstance()->AddImage("bgImage", TEXT("Image/backGround.bmp"));
	
    gameState = new GameState();
    ui = new UI(gameState);

    player = new BHPlayer();

    player->Init("marisa_idle", {GAME_CENTER_X, GAME_CENTER_Y});
    D2DImage* moveImage = ImageManager::GetInstance()->AddImage("marisa_left", TEXT("Image/Character/Marisa/marisa_left.png"), 4, 1);
    player->SetMoveImage(moveImage);
	
    enemy = new BHEnemy();
    
	enemy->Init("marisa_idle",{GAME_CENTER_X, 100});
    enemy->SetItemList(items);
    enemy->SetGameState(gameState);

    enemyFactory = new ObjectPool<BHEnemy>();
    enemyFactory->Init(100);

    BHEnemy* enemy2 = enemyFactory->Allocate();
    enemy2->Init("enemy", {200, 100});

    // 아이템
 //   item->Init("smallScore", 16.f, { WINSIZE_X / 2 - 200, WINSIZE_Y / 2 }, 90);
	//item->InitGameState(gameState);


    // enemy = new BHEnemy();
    //
    // enemy->Init("enemy",{GAME_CENTER_X, 100});
    //
    // enemyFactory = new ObjectPool<BHEnemy>();
    // enemyFactory->Init(100);
    
    // BHEnemy* enemy2 = enemyFactory->Allocate();
    // enemy2->Init("enemy", {200, 100});

    stageWaveManager = new StageWaveManager();
    stageWaveManager->Init();

}

void TouhouScarletDevilCloneGame::Release()
{

    // if (enemy)
    // {
    //     enemy->Release();
    //     delete enemy;
    //     enemy = nullptr;
    // }
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

  //  if (item)
  //  {
		//item->Release();
		//delete item;
		//item = nullptr;
  //  }

    if (ui)
    {
		delete ui;
		ui = nullptr;
    }

    // if (enemyFactory)
    // {
    //     enemyFactory->Clear();
    //     delete enemyFactory;
    //     enemyFactory = nullptr;
    // }
}

void TouhouScarletDevilCloneGame::Update(float dt)
{
    if (player) player->Update(dt);
    if (enemy) enemy->Update(dt);
//	if (item) item->Update(dt);
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
    
    for (auto i : enemyFactory->GetActive())
    {
        i->Update(dt);
    }

    
    if (frame >= 4)frame = 0;
    if (angle > 360) angle = 0;

    stageWaveManager->Update(dt);
    
    PoolManager::GetInstance()->Update(dt);
    
    CircleCollisionManager::GetInstance()->Update();
}

void TouhouScarletDevilCloneGame::Render(HDC hdc)
{
    if (bgImage) bgImage->Render(-350,-560);

    if (player) player->Render(hdc);
    
    // if (enemy) enemy->Render(hdc);

	for (auto it : items)
	{
		it->Render(hdc);
	}

	if (ui) ui->Render(hdc);

    for (auto i : enemyFactory->GetActive())
    {
        i->Render(hdc);
    }

    PoolManager::GetInstance()->Render();
    
    CircleCollisionManager::GetInstance()->Render(hdc);
}
