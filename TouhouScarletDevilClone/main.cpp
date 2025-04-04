// main.cpp

#include "config.h"
#include "MainGame.h"
#include "Timer.h"
#include "D2DImage.h"

HINSTANCE g_hInstance;
HWND g_hWnd;
LPCWSTR g_lpszClassName = (LPCWSTR)TEXT("������ API ����ϱ�");
MainGame g_mainGame;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	g_hInstance = hInstance;

	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 2068;
	wndClass.cbWndExtra = 2068;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(g_hInstance, IDC_ARROW);
	wndClass.hIcon = LoadIcon(g_hInstance, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHIELD));

	RegisterClassEx(&wndClass);

	RECT rcWindowSize = { 0, 0, WINSIZE_X, WINSIZE_Y };
	AdjustWindowRect(&rcWindowSize, WS_OVERLAPPEDWINDOW, FALSE);
	int width = rcWindowSize.right - rcWindowSize.left;
	int height = rcWindowSize.bottom - rcWindowSize.top;

	g_hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, g_lpszClassName, g_lpszClassName,
		WS_OVERLAPPEDWINDOW, 50, 50, width, height,
		NULL, NULL, g_hInstance, NULL);

	ShowWindow(g_hWnd, nCmdShow);

	Timer timer;
	timer.Init();
	CoInitialize(NULL);
	D2DImage::InitD2D(g_hWnd);
	ImageManager::GetInstance()->Init();
	ShapeManager::GetInstance()->Init();
	EffectPlayer::GetInstance()->Init(500);
	SoundPlayer::GetInstance()->Init();
	GameStateManager::GetInstance()->Init();

	g_mainGame.Init();
	
	MSG message;
	while (true)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			timer.Tick();
			g_mainGame.Update(timer.GetDeltaTime());
			g_mainGame.Render();
		}
	}
	CoUninitialize();
	g_mainGame.Release();
	timer.Release();
	GameStateManager::GetInstance()->ReleaseInstance();
	SoundPlayer::GetInstance()->Release();
	EffectPlayer::GetInstance()->Release();
	ShapeManager::GetInstance()->Release();
	ImageManager::GetInstance()->Release();
	
	return message.wParam;
}

LRESULT WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}
