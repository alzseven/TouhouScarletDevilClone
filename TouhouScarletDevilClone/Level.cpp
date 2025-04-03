#include "Level.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "config.h"
#include "KeyManager.h"

void Level::Init()
{
	difficultyLevelBG = ImageManager::GetInstance()->AddImage("Level_BG", TEXT("Image/Intro/ani/MergeImage.png"),1,100);
	easyImage = ImageManager::GetInstance()->AddImage("easy", TEXT("Image/Intro/UI_easy.png"));
	normalImage = ImageManager::GetInstance()->AddImage("normal", TEXT("Image/Intro/UI_normal.png"));
	hardImage = ImageManager::GetInstance()->AddImage("hard", TEXT("Image/Intro/UI_hard.png"));
	lunaticImage = ImageManager::GetInstance()->AddImage("lunatic", TEXT("Image/Intro/UI_lunatic.png"));
	choice = ImageManager::GetInstance()->AddImage("choice", TEXT("Image/Intro/UI_choice.png"));
	characterUpperBody = ImageManager::GetInstance()->AddImage("characterUpperBody", TEXT("Image/Intro/UI_marisaA.png"));
	characterLowerBody = ImageManager::GetInstance()->AddImage("characterLowerBody", TEXT("Image/Intro/UI_marisaB.png"));


	choicePos = { 500,160 };

	easyPos = { 600, 160 };
	normalPos = { 600, 260 };
	hardPos = { 600, 360 };
	lunaticPos = { 600, 460 };
	
	characterUpperBodyPos = { 900, 160 };
	characterLowerBodyPos = { 900, 416 };


	isSelected = false;
}

void Level::Release()
{

}

void Level::Update(float dt)
{
	bgTimer += dt;
	if (bgTimer >= bgFrameDelay)
	{
		bgTimer = 0.0f;
		bgFrame = (bgFrame + 1) % 100;
	}
	selectLevel(dt);

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_ESCAPE))
	{
		if (currentScene)
			*currentScene = mainMenu;
	}
}

void Level::Render(HDC hdc)
{
	if (difficultyLevelBG)
		difficultyLevelBG->Middle_RenderFrameScale(WINSIZE_X/2,WINSIZE_Y/2,1.6f,4.2f, bgFrame);
	easyImage->RenderFrame(easyPos.x, easyPos.y, 1);
	normalImage->RenderFrame(normalPos.x, normalPos.y, 1);
	hardImage->RenderFrame(hardPos.x, hardPos.y, 1);
	lunaticImage->RenderFrame(lunaticPos.x, lunaticPos.y, 1);
	if(!isSelected)
		choice->RenderFrame(choicePos.x,choicePos.y, 1);
	characterUpperBody->RenderFrame(characterUpperBodyPos.x, characterUpperBodyPos.y, 1);
	characterLowerBody->RenderFrame(characterLowerBodyPos.x, characterLowerBodyPos.y, 1);

}

void Level::selectLevel(float dt)
{
	int index = GetLevelIndex(levelState);

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN)) {
		index = (index + 1) % levelCount;
		levelState = GetLevelStateFromIndex(index);
		choicePos.y = levelPosY[index];
	}
	else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP)) {
		index = (index - 1 + levelCount) % levelCount;
		levelState = GetLevelStateFromIndex(index);
		choicePos.y = levelPosY[index];
	}

	if ((levelState == LevelState::easy) && KeyManager::GetInstance()->IsOnceKeyDown(VK_RETURN))
	{
		isSelected = true;
	}

	if (isSelected) {
		MoveNSEW(easyPos, { 50, 550 }, 500.0f, dt);
		MoveNSEW(normalPos, { -300, 260 }, 700.0f, dt);
		MoveNSEW(hardPos, { -300, 360 }, 700.0f, dt);
		MoveNSEW(lunaticPos, { -300, 460 }, 700.0f, dt);
		MoveNSEW(characterUpperBodyPos, { 600, 160 }, 500.0f, dt);
		MoveNSEW(characterLowerBodyPos, { 600, 416 }, 500.0f,dt);

		bool allDone =
			IsPositionReached(easyPos, { 50, 550 }, dt) &&
			IsPositionReached(normalPos, { -300, 260 }, dt) &&
			IsPositionReached(hardPos, { -300, 360 }, dt) &&
			IsPositionReached(lunaticPos, { -300, 460 }, dt);

		if (allDone){
			if (KeyManager::GetInstance()->IsStayKeyDown(VK_RETURN))
			{
				if (currentScene)
					*currentScene = InStage;
			}
			
		}
	}

}

int Level::GetLevelIndex(LevelState state)
{
	switch (state)
	{
	case LevelState::easy: return 0;
	case LevelState::normal: return 1;
	case LevelState::hard: return 2;
	case LevelState::lunatic: return 3;
	}
	return 0;
}

LevelState Level::GetLevelStateFromIndex(int index)
{
	switch (index)
	{
	case 0: return LevelState::easy;
	case 1: return LevelState::normal;
	case 2: return LevelState::hard;
	case 3: return LevelState::lunatic;
	}
	return LevelState::easy;
}

void Level::MoveNSEW(FPOINT& pos, const FPOINT& target, float speed, float dt)
{
	float dx = target.x - pos.x;
	float dy = target.y - pos.y;
	float distance = sqrtf(dx * dx + dy * dy);

	if (distance < 1.0f) {
		pos = target;
		return;
	}

	float nx = dx / distance;
	float ny = dy / distance;
	pos.x += nx * speed * dt;
	pos.y += ny * speed * dt;
}

bool Level::IsPositionReached(const FPOINT& pos, const FPOINT& target, float threshold)
{
	float dx = pos.x - target.x;
	float dy = pos.y - target.y;
	return (dx * dx + dy * dy) < (threshold * threshold);
}
