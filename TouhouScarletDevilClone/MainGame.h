#pragma once
#include "GameObject.h"

class MainGame : public GameObject
{
private:
	HDC hdc;

public:
	void Init();
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

