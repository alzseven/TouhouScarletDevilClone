#pragma once
#include "GameObject.h"

class TouhouScarletDevilCloneGame;

class D2DImage;
class EnemyFactory;
class MainGame : public GameObject
{
private:
	HDC hdc;
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

