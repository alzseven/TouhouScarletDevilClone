#include "config.h"
#include "MainGame.h"
#include "TouhouScarletDevilCloneGame.h"
#include "InGame.h"
#include "D2DImage.h"
#include "BHObjectManager.h"
#include "BHitem.h"
#include "Intro.h"
#include "Menu.h"
#include "Level.h"

void MainGame::Init()
{
	KeyManager::GetInstance()->Init();
	BHObjectManager::GetInstance()->Init();
	
	D2DImage::InitD2D(g_hWnd);
	ShapeManager::GetInstance()->Init();
	

	gameInstance = new TouhouScarletDevilCloneGame();
	gameInstance->Init();
	eSpawn = 100;
	
	//SoundPlayer::GetInstance()->SoundOn("background");
	currentScene = IntroUi;
	prevScene = Finish;
	result_image = ImageManager::GetInstance()->FindImage("result");
}

void MainGame::Release()
{
	if (gameInstance)
	{
		gameInstance->Release();
		delete gameInstance;
		gameInstance = nullptr;
	}

	KeyManager::GetInstance()->Release();
	BHObjectManager::GetInstance()->Release();

	if (intro)
	{
		intro->Release();
		delete intro;
		intro = nullptr;
	}

	if (menu)
	{
		menu->Release();
		delete menu;
		menu = nullptr;
	}

	if (level)
	{
		level->Release();
		delete level;
		level = nullptr;
	}

	// if (backBuffer)
	// {
	// 	backBuffer->Release();
	// 	delete backBuffer;
	// 	backBuffer = nullptr;
	// }



	// if (background)
	// {
	// 	background->Release();
	// 	delete background;
	// 	background = nullptr;
	// }
	//
	// if (backBuffer)
	// {
	// 	backBuffer->Release();
	// 	delete backBuffer;
	// 	backBuffer = nullptr;
	// }

	
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update(float dt)
{

	eTimer += dt;
	//gameInstance->Update(dt);

	if (prevScene != currentScene)
	{
		ChangeScene(currentScene);
		prevScene = currentScene;
	}
	switch (currentScene)
	{
	case IntroUi:
		if(intro) intro->Update(dt);
		break;
	case mainMenu:
		if (menu) menu->Update(dt);
		break;
	case DifficultyLevel:
		if (level)level->Update(dt);
		break;
	case InStage:
		gameInstance->Update(dt);
		// go to ending or main something
		if (GameStateManager::GetInstance()->GetGameState()->isFinish)
		{
			SoundPlayer::GetInstance()->SoundOff("stage1_boss");
			SoundPlayer::GetInstance()->SoundOn("title");
			currentScene = IntroUi;
		}
		break;
	case Finish:
		break;
	default:
		break;
	}

	InvalidateRect(g_hWnd, NULL, false);

	EffectPlayer::GetInstance()->Update(dt);
	/*if (eTimer >= enTimer)
	{
		enTimer += 2.f;
		eCount++;
		if (eCount > eSpawn) eCount = 0;
		EffectPlayer::GetInstance()->PlayEffect("Hit_blue", { 100.0f, 200.0f });
		EffectPlayer::GetInstance()->PlayEffect("Hit_white", { 150.0f, 200.0f });
		EffectPlayer::GetInstance()->PlayEffect("Hit_red", { 200.0f, 200.0f });
		EffectPlayer::GetInstance()->PlayEffect("Hit_green", { 250.0f, 200.0f });
		EffectPlayer::GetInstance()->PlayEffect("Kill", { 100, 250 });
		EffectPlayer::GetInstance()->PlayEffect("MagicCircle", { 150, 250 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_black", { 200, 250 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_blue", { 250, 250 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_green", { 100, 300 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_purple", { 150, 300 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_red", { 200, 300 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_sky", { 250, 300 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_yellow", { 100, 350 });
		EffectPlayer::GetInstance()->PlayEffect("NormalShoot_white", { 150, 350 });
		EffectPlayer::GetInstance()->PlayEffect("Kill_zako", { 100, 400 });
		EffectPlayer::GetInstance()->PlayEffect("Boss_phase", { 200, 400 });
		EffectPlayer::GetInstance()->PlayEffect("marisa_bomb", { 100, 400 });
	}*/

}

void MainGame::Render()
{
	D2DImage::BeginDraw();
	D2DImage::Clear(D2D1::ColorF(D2D1::ColorF::Black));

	//if (gameInstance) gameInstance->Render(hdc);
	
	
	SoundPlayer::GetInstance()->Update();


	switch (currentScene)
	{
	case IntroUi:
		if (intro) intro->Render(NULL);
		break;
	case mainMenu:
		if (menu) menu->Render(NULL);
		break;
	case DifficultyLevel:
		if (level) level->Render(NULL);
		break;
	case InStage:
		if (gameInstance)
		{
			gameInstance->Render(NULL);
			if (GameStateManager::GetInstance()->GetGameState()->isGameClear)
			{
				timer++;
				if (timer > 300)
				{
					result_image->Middle_RenderFrameScale(WINSIZE_X / 2, WINSIZE_Y / 2, 1.4f, 1.4f, 1);
				}
				if (timer > 1000)
				{
					GameStateManager::GetInstance()->GetGameState()->isFinish = true;
				}
			}
			
		}

		break;
	case Finish:
		break;
	default:
		break;
	}

	// HDC hBackBufferDC = backBuffer->GetMemDC();
	//
	// background->Render(hBackBufferDC);
	// backBuffer->Render(hBackBufferDC);
	//
	//if (gameInstance) gameInstance->Render(hdc);
	//
	//
	//
	// backBuffer->Render(hdc);
	/*for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			testImage->Middle_RenderFrameScale(j * 18,i * 18,2,2, frame, angle, false, false, 1.0f);
		}
	}*/
	/*testImage->RenderFrameScale(0,0, 4, 4, frame, 0, false, false, 1.0f);
	testImage->RenderFrameScale(0, 0, 2, 2, frame, 0, false, false, 1.0f);*/
	
	// HDC hBackBufferDC = backBuffer->GetMemDC();
	//
	// backBuffer->Render(hBackBufferDC);
	


	// enemyFactory->Render();
	//
	// backBuffer->Render(hdc);
	
	//도형 출력 예제
	// D2DImage image;
	// image.DrawLine({ 200,100 }, { 200,500 }, 4, 4);
	// image.DrawCircle({ 100,100 }, 20, 1, 2);
	// image.DrawRect({ 300,200 }, {400,300}, 2, 5);

	D2DImage::EndDraw();
}

void MainGame::ChangeScene(GameScene nextScene)
{
	switch (prevScene) {
	case IntroUi:
		if (intro) {
			intro->Release();
			delete intro;
			intro = nullptr;
		}
		break;
	case mainMenu:
		if (menu) {
			menu->Release();
			delete menu;
			menu = nullptr;
		}
		break;
	case DifficultyLevel:
		if (level) {
			level->Release();
			delete level;
			level = nullptr;
		}
		break;
	case InStage:
		if (gameInstance) {
			gameInstance->Release();
			delete gameInstance;
			gameInstance = nullptr;
		}
		break;
	case Finish:
		break;
	}

	switch (nextScene) {
	case IntroUi:
		
		intro = new Intro(&currentScene);
		intro->Init();
		break;
	case mainMenu:
		
		menu = new Menu(&currentScene);
		menu->Init();
		break;
	case DifficultyLevel:
		level = new Level(&currentScene);
		level->Init();
		break;
	case InStage:
		
		
		gameInstance = new TouhouScarletDevilCloneGame();
		gameInstance->Init();
		break;
	}
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
