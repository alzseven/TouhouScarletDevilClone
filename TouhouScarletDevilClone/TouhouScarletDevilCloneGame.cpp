#include "TouhouScarletDevilCloneGame.h"
#include "InGame.h"
#include "BHEnemy.h"
#include "BHPlayer.h"
#include "BHItem.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "GameState.h"


void TouhouScarletDevilCloneGame::Init()
{

    bgImage = ImageManager::GetInstance()->AddImage("bgImage", TEXT("Image/backGround.bmp"));
	
    gameState = new GameState();
    inGame = new InGame(gameState);

    player = new BHPlayer();
    player->Init("Marisa", 18, {GAME_CENTER_X, GAME_CENTER_Y}, 90.f);
    D2DImage* moveImage = ImageManager::GetInstance()->AddImage("Marisa_Move_Left", TEXT("Image/Marisa_Move_Left.bmp"), 8, 1);
    player->SetMoveImage(moveImage);

    enemy = new BHEnemy();
    
    enemy->Init("enemy", 26 , {GAME_CENTER_X, 100}, DEG_TO_RAD(90.f));
    enemy->SetItemList(items);
    enemy->SetGameState(gameState);
    enemyFactory = new ObjectPool<BHEnemy>();
    enemyFactory->Init(100);

    BHEnemy* enemy2 = enemyFactory->Allocate();
    enemy2->Init("enemy", 26, {200, 100}, DEG_TO_RAD(90.f));

    // 아이템
 //   item->Init("smallScore", 16.f, { WINSIZE_X / 2 - 200, WINSIZE_Y / 2 }, 90);
	//item->InitGameState(gameState);
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

  //  if (item)
  //  {
		//item->Release();
		//delete item;
		//item = nullptr;
  //  }

    if (inGame)
    {
		delete inGame;
		inGame = nullptr;
    }
}

void TouhouScarletDevilCloneGame::Update(float dt)
{
    if (player) player->Update(dt);
    if (enemy) enemy->Update(dt);
//	if (item) item->Update(dt);
	if (inGame) inGame->Update(dt);
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
    if (timer >= 500)
    {
        frame++;
        angle++;
        timer = 0;
		finishFlag = true;
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

	for (auto it : items)
	{
		it->Render(hdc);
	}

	if (inGame) inGame->Render(hdc);

    for (auto i : enemyFactory->GetActive())
    {
        i->Render(hdc);
    }
    CircleCollisionManager::GetInstance()->Render(hdc);
}
