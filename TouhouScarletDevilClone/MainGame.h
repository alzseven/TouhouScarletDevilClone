#pragma once
#include "GameObject.h"

class TouhouScarletDevilCloneGame;

class UI;
class D2DImage;
class BHItem;
class MainGame : public GameObject
{
private:
	HDC hdc;
	
	TouhouScarletDevilCloneGame* gameInstance;
	UI* ui;
	BHItem* item;
	int timer = 0;
	int frame = 0;
	float angle = 0;

public:
	void Init();
	void Release();
	void Update(float dt);
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

