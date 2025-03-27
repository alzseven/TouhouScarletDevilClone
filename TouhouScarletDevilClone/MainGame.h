#pragma once
#include "GameObject.h"

class Image;
class BHPlayer;
class MainGame : public GameObject
{
private:
	HDC hdc;
	Image* backBuffer;
	Image* background;
	BHPlayer* player;
public:
	void Init();
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

