#include "UI.h"
#include "Image.h"
#include "ImageManager.h"
#include "InputManager.h"
#include "Timer.h"

UI::UI()
{
	pos = { 0.0f,0.0f };
	BackGround_Image = ImageManager::GetInstance()->AddImage("BackGround", TEXT("Image/InGameBackGround.bmp"), 900, 680, true, RGB(0, 0, 0));
	Stage = ImageManager::GetInstance()->AddImage("Stage", TEXT("Image/Stage.bmp"), 480, 560, true, RGB(255, 0, 255));
	MaxScoreImage = ImageManager::GetInstance()->AddImage("MaxScoreImage", TEXT("Image/MaxScore.bmp"), 100, 30, true, RGB(0, 0, 0));
	ScoreImage = ImageManager::GetInstance()->AddImage("Score", TEXT("Image/Score.bmp"), 50, 28, true, RGB(0, 0, 0));
	PlayerHpBarImage = ImageManager::GetInstance()->AddImage("PlayerHpBar", TEXT("Image/PlayerHpBar.bmp"), 100, 30, true, RGB(0, 0, 0));
	BombImage = ImageManager::GetInstance()->AddImage("BombBar", TEXT("Image/BombBar.bmp"), 80, 30, true, RGB(0, 0, 0));
	PowerImage = ImageManager::GetInstance()->AddImage("Power", TEXT("Image/Power.bmp"), 100, 30, true, RGB(0, 0, 0));
	PowerBarImage = ImageManager::GetInstance()->AddImage("PowerBar", TEXT("Image/PowerBar.bmp"), 160, 30, 160, 1, true, RGB(0, 0, 0));
	PowerMaxImage = ImageManager::GetInstance()->AddImage("PowerMax", TEXT("Image/PowerMax.bmp"), 60, 22, true, RGB(0, 0, 0));
	GrazeImage = ImageManager::GetInstance()->AddImage("Graze", TEXT("Image/Graze.bmp"), 100, 30, true, RGB(0, 0, 0));
	EnemyPhaseImage = ImageManager::GetInstance()->AddImage("EnemyPhase", TEXT("Image/EnemyPhase.bmp"), 50, 20, true, RGB(0, 0, 0));
	BossHpBarImage = ImageManager::GetInstance()->AddImage("BossHpBar", TEXT("Image/BossHpBar.bmp"), 350, 8, 350, 1, true, RGB(0, 0, 0));
	circle = ImageManager::GetInstance()->AddImage("circle", TEXT("Image/circle.bmp"), 129, 129, true, RGB(0, 0, 0));
	FPSImage = ImageManager::GetInstance()->AddImage("FPS", TEXT("Image/FPS.bmp"), 70, 25, true, RGB(32, 32, 32));

	// 타이머
	timer = new Timer();
	timer->Init();



	ReLoadScore();

	// 점수 초기화
	MaxScore = 0;
	Score = 0;

	// 체력 초기화
	PlayerHp = 3;
	// 폭탄 초기화
	BombCount = 3;

	// hp 바 프레임 초기화
	currPowerbarFrame = 0;
	elapPowerbarFrame = 0;
	currBossHpBarFrame = 350;

	// 나중에 지울거
	isEnemyPhase = true;
}

UI::~UI()
{
	BackGround_Image = nullptr;
	Stage = nullptr;
	MaxScoreImage = nullptr;
	ScoreImage = nullptr;
	PlayerHpBarImage = nullptr;
	PlayerHpImage = nullptr;
	BombImage = nullptr;
	PowerImage = nullptr;
	PowerBarImage = nullptr;
	PowerMaxImage = nullptr;
	GrazeImage = nullptr;
	EnemyPhaseImage = nullptr;
	BossHpBarImage = nullptr;
	circle = nullptr;
	FPSImage = nullptr;

	if (BackGround) {
		BackGround->Release();
		delete BackGround;
		BackGround = nullptr;
	}

	if (PowerBarBuffer)
	{
		PowerBarBuffer->Release();
		delete PowerBarBuffer;
		PowerBarBuffer = nullptr;
	}

	if (BossHpBarBuffer)
	{
		BossHpBarBuffer->Release();
		delete BossHpBarBuffer;
		BossHpBarBuffer = nullptr;
	}

	numberImageKeys.clear();

}

void UI::Update(float dt)
{
	timer->Tick();
	ReLoadStar();
	// 파워바 프레임 업데이트
	if (InputManager::isMoveDown()) {
		currPowerbarFrame++;
		if (currPowerbarFrame >= 160)
			currPowerbarFrame = 159;
	}
	else if (InputManager::isMoveUp()) {
		currPowerbarFrame--;
		if (currPowerbarFrame < 0)
			currPowerbarFrame = 0;
	}

	if (InputManager::isMoveRight()) {
		currBossHpBarFrame++;
		if (currBossHpBarFrame >= 350)
			currBossHpBarFrame = 349;
	}
	else if (InputManager::isMoveLeft()) {
		currBossHpBarFrame--;
		if (currBossHpBarFrame < 0)
			isEnemyPhase = false;
	}

	if (isEnemyPhase) {
		elapsedTime += dt;
		if (elapsedTime >= 1.0f)
		{
			remainTime--;
			elapsedTime = 0.0f;

			if (remainTime <= 0) {
				remainTime = 0;
				isEnemyPhase = false;
			}
		}
	}

	// 보스 등장 조건
	//if (true)
	//	isEnemyPhase = true;
}

void UI::Render(HDC hdc)
{
	
	//Stage->Render(hdc, StagePos.x, StagePos.y);
	
	//if (BackGround && isBgReder) {
	//	BackGround->Render(hdc);
	//}

	BackGround_Image->Render(hdc);


	MaxScoreImage->Render(hdc, MaxScorePos.x, MaxScorePos.y);
	ScoreImage->Render(hdc, ScorePos.x, ScorePos.y);
	PlayerHpBarImage->Render(hdc, PlayerHpPos.x, PlayerHpPos.y);
	BombImage->Render(hdc, BombPos.x, BombPos.y);
	PowerImage->Render(hdc, PowerPos.x, PowerPos.y);
	GrazeImage->Render(hdc, GrazePos.x, GrazePos.y);


	// 점수
	RenderScoreAsImage(hdc, MaxScore, { MaxScorePos.x + 120, MaxScorePos.y });
	RenderScoreAsImage(hdc, Score, { ScorePos.x + 70, ScorePos.y });

	// 체력 및 폭탄
	RenderHpAsImage(hdc, PlayerHp, { PlayerHpPos.x + 120, PlayerHpPos.y });
	RenderBombAsImage(hdc, BombCount, { BombPos.x + 120, BombPos.y });

	// 파워바
	RenderPowerBarAsImage(hdc, currPowerbarFrame, PowerPos);
	UpdatePowerBarMax(hdc, PowerPos);

	// 보스 등장시 그리기
	if (isEnemyPhase) {
		RenderEnemyPhase(hdc);
		RenderTimerAsImage(hdc, remainTime, EnemyPhasePos);
	}


	// 원 그리기
	circle->Render(hdc, circlePos.x, circlePos.y);

	RenderFPSAsImage(hdc, timer->GetFPS(), FPSPos);
}

// 점수 이미지 로드
void UI::ReLoadScore()
{
	// Map에 넣을 점수 key값
	const char* numberNames[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	MaxScore = 1234;
	Score = 12;

	// 숫자 이미지 로드
	for (int i = 0; i < 10; ++i)
	{
		string key = numberNames[i];
		numberImageKeys.push_back(key);

		wchar_t fileName[64];
		wsprintf(fileName, L"Image/Num%S.bmp", key.c_str());

		if (!ImageManager::GetInstance()->FindImage(key))
			ImageManager::GetInstance()->AddImage(
				key,
				fileName,
				20, 28,
				true, RGB(37, 37, 37)
			);
	}
}

void UI::ReLoadStar()
{
	string key;
	const wchar_t* path = TEXT("Image/PlayerHpImage.bmp");

	PlayerHp = 3;
	BombCount = 3;

	// HP 그리기
	for (int i = 0; i < MaxHpAndBomb; i++)
	{
		if (i < PlayerHp) {
			key = "Star";
			path = TEXT("Image/PlayerHpImage.bmp");
		}
		else {
			key = "EmptyStar";
			path = TEXT("");
		}

		ImageManager::GetInstance()->AddImage(
			key,
			path,
			20, 28, true, RGB(0, 0, 0)
		);
	}

	// 폭탄 그리기
	for (int i = 0; i < MaxHpAndBomb; i++)
	{
		if (i < BombCount) {
			key = "Bomb";
			path = TEXT("Image/BombCount.bmp");
		}
		else {
			key = "EmptyBomb";
			path = TEXT("");
		}

		ImageManager::GetInstance()->AddImage(
			key,
			path,
			20, 28, true, RGB(0, 0, 0)
		);
	}
}

// 숫자를 이미지로 출력
void UI::RenderScoreAsImage(HDC hdc, int number, FPOINT startPos)
{
	// 가로 폭, 8자리 설정
	const int digitWidth = 20;
	const int totalDigits = 8;

	// total 길이만큼 0으로 채움
	string scoreStr = to_string(number);
	while (scoreStr.length() < totalDigits)
		scoreStr = "0" + scoreStr;

	// 각 자리수를 이미지로 출력
	for (int i = 0; i < totalDigits; ++i)
	{
		char digitChar = scoreStr[i];	// 각 자리수를 문자로 변환
		string key(1, digitChar);		// 문자를 키로 변환

		// 이미지가 있으면 출력
		if (Image* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(hdc, static_cast<int>(startPos.x + i * digitWidth), static_cast<int>(startPos.y));
		}
	}
}

// 체력을 이미지로 출력
void UI::RenderHpAsImage(HDC hdc, int number, FPOINT Pos)
{
	// 가로 폭, 8자리 설정
	const int StarWidth = 20;
	const int MaxStar = 8;

	for (int i = 0; i < MaxStar; i++) {

		string key = (i < number) ? "Star" : "EmptyStar";

		if (Image* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(hdc, static_cast<int>(Pos.x + i * StarWidth), static_cast<int>(Pos.y));
		}
	}
}


// 폭탄을 이미지로 출력
void UI::RenderBombAsImage(HDC hdc, int number, FPOINT Pos)
{
	// 가로 폭, 8자리 설정
	const int StarWidth = 20;

	for (int i = 0; i < MaxHpAndBomb; i++) {

		string key = (i < number) ? "Bomb" : "EmptyBomb";

		if (Image* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(hdc, static_cast<int>(Pos.x + i * StarWidth), static_cast<int>(Pos.y));
		}
	}

}


// 파워 숫자 및 MAX 표기
void UI::UpdatePowerBarMax(HDC hdc, FPOINT pos)
{
	int number = currPowerbarFrame;

	const int digitWidth = 20;

	string numberStr = to_string(number);
	int len = numberStr.length();

	for (int i = 0; i < len; i++)
	{
		string key(1, numberStr[i]);

		if (Image* img = ImageManager::GetInstance()->FindImage(key)) {
			if (number < 159)
				img->Render(hdc, pos.x + 130 + i * digitWidth, pos.y);
		}
	}
	if (currPowerbarFrame == 159)
		PowerMaxImage->Render(hdc, pos.x + 130, pos.y);
}

// 파워바 이미지로 출력
void UI::RenderPowerBarAsImage(HDC hdc, int number, FPOINT Pos)
{
	Image* img = ImageManager::GetInstance()->FindImage("PowerBar");
	if (!img) return;

	int frameWidth = img->GetFrameWidth();
	int frameHeight = img->GetFrameHeight();

	// 프레임 수가 바뀌었을 때만 다시 그림
	if (currPowerbarFrame != prevPowerbarFrame)
	{
		if (PowerBarBuffer)
		{
			PowerBarBuffer->Release();
			delete PowerBarBuffer;
		}
		if (currPowerbarFrame > 0)
		{
			PowerBarBuffer = new Image();
			PowerBarBuffer->Init(frameWidth * currPowerbarFrame, frameHeight);

			for (int i = 0; i < currPowerbarFrame; ++i)
			{
				int frameX = i % img->GetMaxFrameX();
				int frameY = i / img->GetMaxFrameX();

				img->FrameRenderRaw(PowerBarBuffer->GetMemDC(),
					i * frameWidth, 0, frameX, frameY);
			}
		}
		else
		{
			PowerBarBuffer = nullptr;
		}
		prevPowerbarFrame = currPowerbarFrame;
	}
	// 최종 출력
	if (PowerBarBuffer && currPowerbarFrame > 0)
	{
		PowerBarBuffer->Render(hdc, Pos.x + 120, Pos.y);
	}
}

// 보스 출현 하면 왼쪽 상단에 EnemyPhase 이미지 출력
void UI::RenderEnemyPhase(HDC hdc)
{
	if (Image* img = ImageManager::GetInstance()->FindImage("EnemyPhase")) {
		img->Render(hdc, EnemyPhasePos.x, EnemyPhasePos.y);
	}
	RenderBossHpBar(hdc, currBossHpBarFrame, { EnemyPhasePos.x + 60, EnemyPhasePos.y + 5 });
}

// 보스 체력바 이미지로 출력
void UI::RenderBossHpBar(HDC hdc, int number, FPOINT Pos)
{
	Image* img = ImageManager::GetInstance()->FindImage("BossHpBar");
	if (!img) return;

	int frameWidth = img->GetFrameWidth();
	int frameHeight = img->GetFrameHeight();

	if (currBossHpBarFrame != prevBossHpBarFrame)
	{
		if (BossHpBarBuffer)
		{
			BossHpBarBuffer->Release();
			delete BossHpBarBuffer;
		}

		if (currBossHpBarFrame > 0)
		{
			BossHpBarBuffer = new Image();
			BossHpBarBuffer->Init(frameWidth * currBossHpBarFrame, frameHeight);

			for (int i = 0; i < currBossHpBarFrame; ++i)
			{
				int frameX = i % img->GetMaxFrameX();
				int frameY = i / img->GetMaxFrameX();

				img->FrameRenderRaw(BossHpBarBuffer->GetMemDC(),
					i * frameWidth, 0, frameX, frameY);
			}
		}
		else
		{
			BossHpBarBuffer = nullptr;
		}

		prevBossHpBarFrame = currBossHpBarFrame;
	}

	// 최종 출력
	if (BossHpBarBuffer && currBossHpBarFrame > 0)
	{
		BossHpBarBuffer->Render(hdc, Pos.x, Pos.y);
	}
}

void UI::RenderTimerAsImage(HDC hdc, int number, FPOINT Pos)
{
	const int digitWidth = 20;
	string timeStr = to_string(number);

	while (timeStr.length() < 2)
		timeStr = "0" + timeStr;

	for (int i = 0; i < timeStr.length(); i++)
	{
		string key(1, timeStr[i]);
		if (Image* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(hdc, static_cast<int>(Pos.x + i * digitWidth) + 425, static_cast<int>(Pos.y) - 5);
		}
	}
}

void UI::RenderFPSAsImage(HDC hdc, unsigned long fps, FPOINT Pos)
{
	const int digitWidth = 20;
	string fpsStr = to_string(fps);

	FPSImage->Render(hdc, static_cast<int>(Pos.x + 80), static_cast<int>(Pos.y));
	for (int i = 0; i < fpsStr.length(); ++i)
	{
		string key(1, fpsStr[i]);
		if (Image* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(hdc, static_cast<int>(Pos.x + i * digitWidth), static_cast<int>(Pos.y));
		}
	}
}



