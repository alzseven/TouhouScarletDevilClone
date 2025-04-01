#include "config.h"
#include "MainGame.h"
#include "TouhouScarletDevilCloneGame.h"
#include "UI.h"
#include "D2DImage.h"

void MainGame::Init()
{
	D2DImage::InitD2D(g_hWnd);
	ShapeManager::GetInstance()->Init();

	ui = new UI();

	
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
	
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update(float dt)
{
	gameInstance->Update(dt);
	ui->Update(dt);
	InvalidateRect(g_hWnd, NULL, false);
	
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
	if (gameInstance) gameInstance->Render(hdc);
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

	ui->Render(NULL);
	//
	// backBuffer->Render(hdc);
	
	//도형 출력 예제
	D2DImage image;
	image.DrawLine({ 200,100 }, { 200,500 }, 4, 4);
	image.DrawCircle({ 100,100 }, 20, 1, 2);
	image.DrawRect({ 300,200 }, {400,300}, 2, 5);

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
