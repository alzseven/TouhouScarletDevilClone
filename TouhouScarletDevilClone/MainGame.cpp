#include "config.h"
#include "MainGame.h"
#include "TouhouScarletDevilCloneGame.h"
#include "UI.h"
#include "D2DImage.h"
#include "EnemyFactory.h"
#include "VEnemy.h"

void MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	ui = new UI();

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

	// if (backBuffer)
	// {
	// 	backBuffer->Release();
	// 	delete backBuffer;
	// 	backBuffer = nullptr;
	// }

	if (ui)
	{
		delete ui;
		ui = nullptr;
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
	ui->Update(dt);
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
	
	// HDC hBackBufferDC = backBuffer->GetMemDC();
	//
	// backBuffer->Render(hBackBufferDC);

	if (gameInstance) gameInstance->Render(NULL);
	ui->Render(NULL);
	//
	// backBuffer->Render(hdc);
	
	//도형 출력 예제
	D2DImage image;
	image.DrawLine({ 200,100 }, { 200,500 }, 4, 4);
	image.DrawCircle({ 100,100 }, 20, 1, 2);
	image.DrawRect({ 300,200 }, {400,300}, 2, 5);
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
