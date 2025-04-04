#pragma once
#include "GameObject.h"
#include "GameScene.h"

class Ending
{
private:
	D2DImage* EndingImage = nullptr;
	GameScene* currentScene = nullptr;

public:
	Ending(GameScene* scene) :currentScene(scene) {}
	~Ending() = default;
	void Init();
	void Release();
	void Update(float dt);
	void Render(HDC hdc);
};

