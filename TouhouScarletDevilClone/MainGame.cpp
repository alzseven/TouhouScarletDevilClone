#include "config.h"
#include "MainGame.h"
#include "Image.h"
#include "TouhouScarletDevilCloneGame.h"

void MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Failed to create : BackBuffer"), TEXT("Warning"), MB_OK);
	}
	background = new Image();
	if (FAILED(background->Init(TEXT("Image/_.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Failed to create : Image/_.bmp"), TEXT("Warning"), MB_OK);
	}

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
	
	if (background)
	{
		background->Release();
		delete background;
		background = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	gameInstance->Update();
	
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	background->Render(hBackBufferDC);
	backBuffer->Render(hBackBufferDC);

	if (gameInstance) gameInstance->Render(hBackBufferDC);


	backBuffer->Render(hdc);
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
