#pragma once
#include "GameObject.h"

class TouhouScarletDevilCloneGame;
class Image;

class D2DImage;
class tmpEnemy;
class MainGame : public GameObject
{
private:
	HDC hdc;
	Image* backBuffer;
	Image* background;
	TouhouScarletDevilCloneGame* gameInstance;
	D2DImage* testImage;
	tmpEnemy* tenemy;
	int timer = 0;
	int frame = 0;
	float angle = 0;
public:
	void Init();
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

