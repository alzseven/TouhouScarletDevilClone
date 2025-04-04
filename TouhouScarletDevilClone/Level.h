#pragma once
#include "GameObject.h"
#include "GameScene.h"

enum class LevelState
{
	easy,
	normal,
	hard,
	lunatic
};

class D2DImage;
class Level
{
private:

	D2DImage* difficultyLevelBG = nullptr;
	D2DImage* easyImage = nullptr;
	D2DImage* normalImage = nullptr;
	D2DImage* hardImage = nullptr;
	D2DImage* lunaticImage = nullptr;
	D2DImage* choice = nullptr;
	D2DImage* characterUpperBody = nullptr;
	D2DImage* characterLowerBody = nullptr;


	FPOINT easyPos{ 0, 0 };
	FPOINT normalPos{ 0, 0 };
	FPOINT hardPos{ 0, 0 };
	FPOINT lunaticPos{ 0, 0 };
	FPOINT choicePos{};
	FPOINT characterUpperBodyPos{ 0, 0 };
	FPOINT characterLowerBodyPos{ 0, 0 };

	bool isSelected;
	//bool allDone

	const int levelCount = 4;
	const float levelPosY[4] = { 160,260,360,460 };

	int bgFrame = 1;
	float bgTimer = 0.0f;
	float bgFrameDelay = 2.0f;
	const int bgTotalFrames = 45;

public:
	Level(GameScene* scene) : currentScene(scene) {}
	~Level() = default;
	void Init();
	void Release();
	void Update(float dt);
	void Render(HDC hdc);
	void selectLevel(float dt);
	int GetLevelIndex(LevelState state);
	LevelState GetLevelStateFromIndex(int index);
	GameScene* currentScene = nullptr;
	LevelState levelState = LevelState::easy;

	void MoveNSEW(FPOINT& pos, const FPOINT& target, float speed, float dt);
	bool IsPositionReached(const FPOINT& pos, const FPOINT& target, float threshold = 1.0f);
};

