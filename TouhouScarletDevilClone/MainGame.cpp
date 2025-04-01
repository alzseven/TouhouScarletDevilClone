#include "config.h"
#include "MainGame.h"
#include "TouhouScarletDevilCloneGame.h"
#include "D2DImage.h"
#include "EnemyFactory.h"
#include "VEnemy.h"

void MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	// backBuffer = new Image();
	// if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	// {
	// 	MessageBox(g_hWnd,
	// 		TEXT("Failed to create : BackBuffer"), TEXT("Warning"), MB_OK);
	// }
	// background = new Image();
	// if (FAILED(background->Init(TEXT("Image/_.bmp"), WINSIZE_X, WINSIZE_Y)))
	// {
	// 	MessageBox(g_hWnd,
	// 		TEXT("Failed to create : Image/_.bmp"), TEXT("Warning"), MB_OK);
	// }

	
	

	enemyFactory = new EnemyFactory;
	enemyFactory->Init(100);
	VEnemy* vEnemy = enemyFactory->active();
	vEnemy->Init({ 300,100 });
	gameInstance = new TouhouScarletDevilCloneGame();
	gameInstance->Init();
}

void MainGame::Release()
{
	if (gameInstance)
	{
		gameInstance->Release();
		delete gameInstance;
		gameInstance = nullptr;
	}
	
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
	if (enemyFactory)
	{
		enemyFactory->Release();
		delete enemyFactory;
		enemyFactory = nullptr;
	}
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update(float dt)
{
	gameInstance->Update(dt);
	
	InvalidateRect(g_hWnd, NULL, false);
	timer++;
	if (timer >= 5)
	{
		frame++;
		angle++;
		timer = 0;
	}
	enemyFactory->Update(dt);
	if (frame >= 4)frame = 0;
	if (angle > 360) angle = 0;
}

void MainGame::Render()
{
	D2DImage::BeginDraw();
	D2DImage::Clear(D2D1::ColorF(D2D1::ColorF::Black));
    

	// HDC hBackBufferDC = backBuffer->GetMemDC();
	//
	// background->Render(hBackBufferDC);
	// backBuffer->Render(hBackBufferDC);
	//
	// if (gameInstance) gameInstance->Render(hBackBufferDC);
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
	enemyFactory->Render();
	D2DImage::EndDraw();
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
