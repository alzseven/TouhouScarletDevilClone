#pragma once
#include "GameObject.h"
#include "GameScene.h"

enum class MenuState
{
	Entry,
	WaitAfterEntry,
	SlideLeft
};

enum class MenuSelect
{
	Start,
	Quit
};

class D2DImage;
class Menu
{
private:
	GameScene* currentScene = nullptr;
	D2DImage* mainImage;
	D2DImage* dong;
	D2DImage* bang;
	D2DImage* hong;
	D2DImage* ma;
	D2DImage* hang;
	D2DImage* name_A;
	D2DImage* name_B;
	D2DImage* startRed;
	D2DImage* startGray;
	D2DImage* quitRed;
	D2DImage* quitGray;

	bool isStart = true;

	FPOINT mainImagePos{ 0, 0 };
	FPOINT dongPos;
	FPOINT bangPos;
	FPOINT hongPos;
	FPOINT maPos;
	FPOINT hangPos;
	FPOINT nameAPos{ 0, 0 };
	FPOINT nameBPos{ 0, 0 };
	FPOINT startPos{ 0, 0 };
	FPOINT quitPos{ 0, 0 };
	FPOINT startRedPos{ 0, 0 };
	FPOINT quitRedPos{ 0, 0 };
	FPOINT startGrayPos{ 0, 0 };
	FPOINT quitGrayPos{ 0, 0 };

	FPOINT dongTarget{};
	FPOINT bangTarget{};
	FPOINT hongTarget{};
	FPOINT maTarget{};
	FPOINT hangTarget{};
	FPOINT nameATarget{};
	FPOINT nameBTarget{};
	FPOINT startTarget{ 0, 0 };
	FPOINT quitTarget{ 0, 0 };

	// 애니메이션 상태 관리
	bool letterArrived = false;    
	bool isSlidingLeft = false;
	bool allowSlide = false;   

	// 슬라이드 제어
	float elapsedTime = 0.0f;  
	float slideOffset = 0.0f;      
	float slideSpeed = 300.0f;     
	float targetMoveLeft = 100.0f; 

	MenuSelect currentSelect = MenuSelect::Start;
public:
	Menu(GameScene* scene) :currentScene(scene) {}
	~Menu() = default;
	void Init();
	void Release();
	void Update(float dt);
	void Render(HDC hdc);
	void MoveNSEW(FPOINT& pos, const FPOINT& target, float speed, float dt);
	void MoveLeft(FPOINT& pos, const FPOINT& target, float speed, float dt);
	void UpdateEntryAnimation(float dt);
	void UpdateWaitAfterEntry(float dt);
	void UpdateSlideLeftAnimation(float dt);
	bool IsPositionReached(const FPOINT& pos, const FPOINT& target, float threshold = 1.0f);

	MenuState state = MenuState::Entry;
	float waitTimer = 0.0f;
};

