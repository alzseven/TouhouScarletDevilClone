#include "Menu.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "config.h"
#include "KeyManager.h"

void Menu::Init()
{
	mainImage = ImageManager::GetInstance()->AddImage("mainImage", TEXT("Image/Intro/UI_title.jpg"));
	dong = ImageManager::GetInstance()->AddImage("dong", TEXT("Image/Intro/UI_dong.png"));
	bang = ImageManager::GetInstance()->AddImage("bang", TEXT("Image/Intro/UI_bang.png"));
	hong = ImageManager::GetInstance()->AddImage("hong", TEXT("Image/Intro/UI_hong.png"));
	ma = ImageManager::GetInstance()->AddImage("ma", TEXT("Image/Intro/UI_ma.png"));
	hang = ImageManager::GetInstance()->AddImage("hang", TEXT("Image/Intro/UI_hang.png"));
	name_A = ImageManager::GetInstance()->AddImage("name_A", TEXT("Image/Intro/UI_nameA.png"));
	name_B = ImageManager::GetInstance()->AddImage("name_B", TEXT("Image/Intro/UI_nameB.png"));
	startRed = ImageManager::GetInstance()->AddImage("startRed", TEXT("Image/Intro/UI_startR.png"));
	quitRed = ImageManager::GetInstance()->AddImage("quitRed", TEXT("Image/Intro/UI_quitB.png"));	
	startGray = ImageManager::GetInstance()->AddImage("startGray", TEXT("Image/Intro/UI_start.png"));
	quitGray = ImageManager::GetInstance()->AddImage("quitGray", TEXT("Image/Intro/UI_quit.png"));


	dongPos = { 220, 700 };
	bangPos = { -300, 200 };
	hongPos = { WINSIZE_X / 2 - 30, 220 };
	maPos = { 800, 200 };
	hangPos = { 220, -150 };
	nameAPos = { -100, -100 };
	nameBPos = { WINSIZE_X, WINSIZE_Y };

	dongTarget = { WINSIZE_X / 2 - 30, 60 };
	bangTarget = { WINSIZE_X / 2 - 30, 140 };
	hongTarget = { WINSIZE_X / 2 - 30, 220 };
	maTarget = { WINSIZE_X / 2 - 30, 300 };
	hangTarget = { WINSIZE_X / 2 - 30, 380 };
	nameATarget = { WINSIZE_X / 2 - 200, 170 };
	nameBTarget = { WINSIZE_X / 2 - 20, 310 };


	startPos = { 900, 250 };
	quitPos = { 900, 300 };

	startTarget = { WINSIZE_X, 250 };
	quitTarget = { WINSIZE_X, 300 };
}

void Menu::Release()
{
}

void Menu::Update(float dt)
{
	switch (state) {
	case MenuState::Entry:
		UpdateEntryAnimation(dt);
		break;
	case MenuState::WaitAfterEntry:
		UpdateWaitAfterEntry(dt);
		break;
	case MenuState::SlideLeft:
		UpdateSlideLeftAnimation(dt);
		break;
	}

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN) ||
		KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
	{
		if (currentSelect == MenuSelect::Start)
			currentSelect = MenuSelect::Quit;
		else
			currentSelect = MenuSelect::Start;
	}

	if ((currentSelect == MenuSelect::Start) && KeyManager::GetInstance()->IsOnceKeyDown(VK_RETURN)) {
		*currentScene = DifficultyLevel;
	}

}

void Menu::Render(HDC hdc)
{
	if(mainImage)
		mainImage->RenderFrame(mainImagePos.x, mainImagePos.y,1);
	if (dong)
		dong->RenderFrame(dongPos.x, dongPos.y, 1);
	if (bang)
		bang->RenderFrame(bangPos.x, bangPos.y, 1);
	if (hong)
		hong->RenderFrame(hongPos.x, hongPos.y, 1);
	if (ma)
		ma->RenderFrame(maPos.x, maPos.y, 1);
	if (hang)
		hang->RenderFrame(hangPos.x, hangPos.y, 1);
	if (name_A)
		name_A->RenderFrame(nameAPos.x, nameAPos.y, 1, 45.0f);
	if (name_B)
		name_B->RenderFrame(nameBPos.x, nameBPos.y, 1, 45.0f);
	if (currentSelect == MenuSelect::Start)
	{
		if (startRed) startRed->RenderFrame(startPos.x, startPos.y, 1);
		if (quitGray) quitGray->RenderFrame(quitPos.x, quitPos.y, 1);
	}
	else
	{
		if (startGray) startGray->RenderFrame(startPos.x, startPos.y, 1);
		if (quitRed) quitRed->RenderFrame(quitPos.x, quitPos.y, 1);
	}
}

// MoveNSEW the position of an object towards a target position at a specified speed
void Menu::MoveNSEW(FPOINT& pos, const FPOINT& target, float speed, float dt)
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

void Menu::MoveLeft(FPOINT& pos, const FPOINT& target, float speed, float dt)
{
	float dx = target.x - pos.x;
	float dy = target.y - pos.y;
}

void Menu::UpdateEntryAnimation(float dt)
{
	MoveNSEW(dongPos, dongTarget, 400.0f, dt);
	MoveNSEW(bangPos, bangTarget, 400.0f, dt);
	MoveNSEW(hongPos, hongTarget, 0.0f, dt); // hong은 정지 상태
	MoveNSEW(maPos, maTarget, 400.0f, dt);
	MoveNSEW(hangPos, hangTarget, 400.0f, dt);
	MoveNSEW(nameAPos, nameATarget, 400.0f, dt);
	MoveNSEW(nameBPos, nameBTarget, 400.0f, dt);

	if (IsPositionReached(dongPos, dongTarget) &&
		IsPositionReached(bangPos, bangTarget) &&
		IsPositionReached(hongPos, hongTarget) &&
		IsPositionReached(maPos, maTarget) &&
		IsPositionReached(hangPos, hangTarget) &&
		IsPositionReached(nameAPos, nameATarget) &&
		IsPositionReached(nameBPos, nameBTarget)){ 
		waitTimer = 0.0f;
		state = MenuState::WaitAfterEntry;
	}
}

void Menu::UpdateWaitAfterEntry(float dt)
{
	waitTimer += dt;
	if (waitTimer >= 1.5f)
	{
		dongTarget.x -= 300;
		bangTarget.x -= 300;
		hongTarget.x -= 300;
		maTarget.x -= 300;
		hangTarget.x -= 300;
		nameATarget.x -= 260;
		nameBTarget.x -= 260;
		startTarget.x -= 200;
		quitTarget.x -= 200;

		state = MenuState::SlideLeft;
	}
}

void Menu::UpdateSlideLeftAnimation(float dt)
{
	MoveNSEW(dongPos, dongTarget, 400.0f, dt);
	MoveNSEW(bangPos, bangTarget, 400.0f, dt);
	MoveNSEW(hongPos, hongTarget, 400.0f, dt);
	MoveNSEW(maPos, maTarget, 400.0f, dt);
	MoveNSEW(hangPos, hangTarget, 400.0f, dt);
	MoveNSEW(nameAPos, nameATarget, 400.0f, dt);
	MoveNSEW(nameBPos, nameBTarget, 400.0f, dt);
	MoveNSEW(startPos, startTarget, 400.0f, dt);
	MoveNSEW(quitPos, quitTarget, 400.0f, dt);
}

bool Menu::IsPositionReached(const FPOINT& pos, const FPOINT& target, float threshold)
{

	float dx = pos.x - target.x;
	float dy = pos.y - target.y;
	return (dx * dx + dy * dy) < (threshold * threshold);
}
