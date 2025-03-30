#pragma once
#include "GameObject.h"

class TouhouScarletDevilCloneGame;
class Image;
class MainGame
{
private:
	HDC hdc;
	Image* backBuffer;
	Image* background;
	TouhouScarletDevilCloneGame* gameInstance;

public:
	void Init();
	void Release();
	void Update(float dt);
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

