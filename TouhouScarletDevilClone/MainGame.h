#pragma once
#include "GameObject.h"

class TouhouScarletDevilCloneGame;

class UI;
class D2DImage;
class MainGame : public GameObject
{
private:
	HDC hdc;
	
	TouhouScarletDevilCloneGame* gameInstance;
	UI* ui;

	int timer = 0;
	int frame = 0;
	float angle = 0;

	float eTimer = 0;
	float enTimer = 0;
	int eCount = 0;
	int eSpawn = 0;
	int scene = 0;
public:
	void Init();
	void Release();
	void Update(float dt);
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

