#pragma once
#include "GameObject.h"
#include "GameScene.h"


class D2DImage;
class Intro
{
private:
	D2DImage* IntroImage = nullptr;
	GameScene* currentScene = nullptr;

public:
	Intro(GameScene* scene) :currentScene(scene) {}
	~Intro();
	void Init();
	void Release();
	void Update(float dt);
	void Render(HDC hdc);
};

