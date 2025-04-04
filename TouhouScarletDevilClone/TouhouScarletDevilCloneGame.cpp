#include "TouhouScarletDevilCloneGame.h"
#include "InGame.h"
#include "BHEnemy.h"
#include "BHPlayer.h"
#include "BHItem.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "BHObjectManager.h"
#include "GameState.h"
#include "Shape.h"
// #include "UI.h"

void TouhouScarletDevilCloneGame::Init()
{
    bgImage = ImageManager::GetInstance()->AddImage("bgImage", TEXT("Image/eff01.png"));

    //gameState = new GameState();

    inGame = new InGame(GameStateManager::GetInstance()->GetGameState());

    //player = new BHPlayer();
    //player->Init("Marisa", 18, {GAME_CENTER_X, GAME_CENTER_Y}, 90.f);
    //D2DImage* moveImage = ImageManager::GetInstance()->AddImage("Marisa_Move_Left", TEXT("Image/Marisa_Move_Left.bmp"), 8, 1);
    //player->SetMoveImage(moveImage);

    // enemy = new BHEnemy();

    player = BHObjectManager::GetInstance()->GetPlayer();
    player->Init("marisa_idle", {GAME_CENTER_X, GAME_CENTER_Y});
    stageWaveManager = new StageWaveManager();
    stageWaveManager->Init();

}

void TouhouScarletDevilCloneGame::Release()
{
    // if (player)
    // {
    //     player->Release();
    //     delete player;
    //     player = nullptr;
    // }

    if (stageWaveManager)
    {
        stageWaveManager->Release();
		delete stageWaveManager;
        stageWaveManager = nullptr;
    }

    if (inGame)
    {
		delete inGame;
		inGame = nullptr;

    }
}


void TouhouScarletDevilCloneGame::Update(float dt)
{
    
    if (player) player->Update(dt);

    stageWaveManager->Update(dt);
    
//	if (item) item->Update(dt);
	if (inGame) inGame->Update(dt);
    
    BHObjectManager::GetInstance()->Update(dt);
    
    CircleCollisionManager::GetInstance()->Update();
    finishFlag = GameStateManager::GetInstance()->GetGameState()->PlayerHp == 0;

    
}

void TouhouScarletDevilCloneGame::Render(HDC hdc)
{
    if (bgImage) bgImage->RenderFrameScale(0,0,10,10,1);

    if (player) player->Render(hdc);
    
    BHObjectManager::GetInstance()->Render();
    
    CircleCollisionManager::GetInstance()->Render(hdc);
    EffectPlayer::GetInstance()->Render();
    if (inGame) inGame->Render(hdc);
    if (GameStateManager::GetInstance()->GetGameState()->isGameClear)
    {
        timer++;
        if (timer > 300)
        {
            EffectPlayer::GetInstance()->PlayEffect("result", { WINSIZE_X / 2,WINSIZE_Y / 2 });
        }
        return;
    }
}
