#include "config.h"
#include "MainGame.h"
#include "Image.h"
#include "BHPlayer.h"

void MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}
	background = new Image();
	if (FAILED(background->Init(TEXT("Image/_.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/_.bmp 생성 실패"), TEXT("경고"), MB_OK);
	}

	player = new BHPlayer();
	Image* image = new Image();
	if (FAILED(image->Init(TEXT("Image/Label36.bmp"), 27, 36)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/_.bmp 생성 실패"), TEXT("경고"), MB_OK);
	}
	SHAPE* shape = new SHAPE{ TEXT("name"), 27, 18, image };
	player->Init(shape, {WINSIZE_X / 2, WINSIZE_Y - 30}, 90);
}

void MainGame::Release()
{
	if (player) {
		delete player;
		player = nullptr;
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
	player->Update();
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	background->Render(hBackBufferDC);
	backBuffer->Render(hBackBufferDC);

	player->Render(hBackBufferDC);

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
