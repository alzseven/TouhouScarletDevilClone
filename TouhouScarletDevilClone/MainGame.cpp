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

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update(float dt)
{
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
		if (terminalReason == TerminalReason::None)
		{
			gameInstance->Update(dt);			

			// 반드시 Update 반환 뒤 terminal flag 확인
			if (GameStateManager::GetInstance()->GetGameState()->isGameClear)
			{
				terminalReason = TerminalReason::Clear;
				terminalElapsed = 0.0f;
			}
			else if (GameStateManager::GetInstance()->GetGameState()->isGameOver)
			{
				terminalReason = TerminalReason::GameOver;
				terminalElapsed = 0.0f;
			}
		}
		else
		{
			terminalElapsed += dt;
			
			// go to ending or main something
			if (terminalElapsed > 3.0f)
			{
				BHObjectManager::GetInstance()->ClearItems();
				SoundPlayer::GetInstance()->SoundOff("stage1_boss");
				// SoundPlayer::GetInstance()->SoundOn("title");
				currentScene = IntroUi;
			}
		}
		break;
	case Finish:
		break;
	default:
		break;
	}

	InvalidateRect(g_hWnd, NULL, false);

	EffectPlayer::GetInstance()->Update(dt);

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
			gameInstance->Render();
			if (terminalReason == TerminalReason::Clear)
			{
				if (terminalElapsed > 1.0f)
				{
					result_image->Middle_RenderFrameScale(WINSIZE_X / 2, WINSIZE_Y / 2, 1.4f, 1.4f, 1);
				}
				//timer++;

				// if (terminalElapsed > 40.0f)
				// {
				// }
				// if (timer > 300)
				// {
				// }
				// if (timer > 1000)
				// {
				// 	GameStateManager::GetInstance()->GetGameState()->isFinish = true;
				// }
			}
			
		}

		break;
	case Finish:
		break;
	default:
		break;
	}


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
		GameStateManager::GetInstance()->Reset();
		terminalReason = TerminalReason::None;
		terminalElapsed = 0.0f;
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
