#include "MainGame.h"

void MainGame::Init()
{
	hdc = GetDC(g_hWnd);
}

void MainGame::Release()
{
	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{

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
