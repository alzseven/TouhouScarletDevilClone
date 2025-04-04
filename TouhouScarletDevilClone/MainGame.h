#pragma once
#include "GameObject.h"
#include "GameScene.h"

class BHItem;
class TouhouScarletDevilCloneGame;


class InGame;
class Intro;
class Level;
class Menu;
class D2DImage;
class MainGame : public GameObject
{
private:
	HDC hdc;
	
	GameScene currentScene = IntroUi;
	GameScene prevScene = IntroUi;
	TouhouScarletDevilCloneGame* gameInstance;

	InGame* ui;
	Intro* intro;
	Menu* menu;
	Level* level;

	BHItem* item;

	int timer = 0;
	int frame = 0;
	float angle = 0;

	float eTimer = 0;
	float enTimer = 0;
	int eCount = 0;
	int eSpawn = 0;

public:
	void Init();
	void Release();
	void Update(float dt);
	void Render();
	void ChangeScene(GameScene nextScene);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

