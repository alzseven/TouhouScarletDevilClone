#include "InGame.h"

#include "D2DImage.h"
#include "ImageManager.h"
#include "InputManager.h"
#include "Timer.h"
#include "GameState.h"
#include "GameStateManager.h"

InGame::InGame(GameState* state)
{

	pos = { 0.0f,0.0f };
	gameState = state;


	BackGround_Image = ImageManager::GetInstance()->AddImage("BackGround", TEXT("Image/Png/InGameBackGround.png"));
	//Stage = ImageManager::GetInstance()->AddImage("Stage", TEXT("Image/Png/Stage.bmp"));
	MaxScoreImage = ImageManager::GetInstance()->AddImage("MaxScoreImage", TEXT("Image/Png/MaxScore.png"));
	ScoreImage = ImageManager::GetInstance()->AddImage("Score", TEXT("Image/Png/Score.png"));
	PlayerHpBarImage = ImageManager::GetInstance()->AddImage("PlayerHpBar", TEXT("Image/Png/PlayerHpBar.png"));
	BombImage = ImageManager::GetInstance()->AddImage("BombBar", TEXT("Image/Png/Bomb.png"));
	PowerImage = ImageManager::GetInstance()->AddImage("Power", TEXT("Image/Png/Power.png"));
	PowerBarImage = ImageManager::GetInstance()->AddImage("PowerBar", TEXT("Image/Png/PowerBar.png"));
	PowerMaxImage = ImageManager::GetInstance()->AddImage("PowerMax", TEXT("Image/Png/PowerMax.png"));
	GrazeImage = ImageManager::GetInstance()->AddImage("Graze", TEXT("Image/Png/Graze.png"));
	EnemyPhaseImage = ImageManager::GetInstance()->AddImage("EnemyPhase", TEXT("Image/Png/EnemyPhase.png"));
	BossHpBarImage = ImageManager::GetInstance()->AddImage("BossHpBar", TEXT("Image/Png/BossHpBar.png"));
	circle = ImageManager::GetInstance()->AddImage("circle", TEXT("Image/Png/Logo.png"));
	FPSImage = ImageManager::GetInstance()->AddImage("FPS", TEXT("Image/Png/FPS.png"));

	// Ÿ�̸�
	timer = new Timer();
	timer->Init();



	ReLoadScore();
}

InGame::~InGame()
{
	// BackGround_Image = nullptr;
	// Stage = nullptr;
	// MaxScoreImage = nullptr;
	// ScoreImage = nullptr;
	// PlayerHpBarImage = nullptr;
	// PlayerHpImage = nullptr;
	// BombImage = nullptr;
	// PowerImage = nullptr;
	// PowerBarImage = nullptr;
	// PowerMaxImage = nullptr;
	// GrazeImage = nullptr;
	// EnemyPhaseImage = nullptr;
	// BossHpBarImage = nullptr;
	// circle = nullptr;
	// FPSImage = nullptr;

	// if (BackGround) {
	// 	BackGround->Release();
	// 	delete BackGround;
	// 	BackGround = nullptr;
	// }
	//
	// if (PowerBarBuffer)
	// {
	// 	PowerBarBuffer->Release();
	// 	delete PowerBarBuffer;
	// 	PowerBarBuffer = nullptr;
	// }
	//
	// if (BossHpBarBuffer)
	// {
	// 	BossHpBarBuffer->Release();
	// 	delete BossHpBarBuffer;
	// 	BossHpBarBuffer = nullptr;
	// }

	numberImageKeys.clear();

}

void InGame::Update(float dt)
{
	timer->Tick();
	ReLoadStar();
	// �Ŀ��� ������ ������Ʈ
	// if (InputManager::isMoveDown()) {
	// 	CurrPowerBarFrame(gameState)++;
		if (CurrPowerBarFrame(gameState) >= 160)
			CurrPowerBarFrame(gameState) = 159;
	// }
	// else if (InputManager::isMoveUp()) {
	// 	CurrPowerBarFrame(gameState)--;
		if (CurrPowerBarFrame(gameState) < 0)
			CurrPowerBarFrame(gameState) = 0;
	// }
	//
	// if (InputManager::isMoveRight()) {
	// 	CurrBossHpBarFrame(gameState)++;
		if (CurrBossHpBarFrame(gameState) >= 350)
			CurrBossHpBarFrame(gameState) = 349;
	// }
	// else if (InputManager::isMoveLeft()) {
	// 	CurrBossHpBarFrame(gameState)--;
		if (CurrBossHpBarFrame(gameState) < 0)
			IsEnemyPhase(gameState) = false;
	// }

	if (IsEnemyPhase(gameState)) {
		elapsedTime += dt;
		if (elapsedTime >= 1.0f)
		{
			RemainTime(gameState)--;
			elapsedTime = 0.0f;

			if (RemainTime(gameState) <= 0) {
				RemainTime(gameState) = 0;
				IsEnemyPhase(gameState) = false;
			}
		}
	}

	// ���� ���� ����
	//if (true)
	//	isEnemyPhase = true;
}

void InGame::Render(HDC hdc)
{

	//Stage->Render(hdc, StagePos.x, StagePos.y);

	//if (BackGround && isBgReder) {
	//	BackGround->Render(hdc);
	//}

	BackGround_Image->Render(-WINSIZE_X / 2, -WINSIZE_Y / 2);


	MaxScoreImage->Render(MaxScorePos.x, MaxScorePos.y);
	ScoreImage->Render(ScorePos.x, ScorePos.y);
	PlayerHpBarImage->Render(PlayerHpPos.x, PlayerHpPos.y);
	BombImage->Render(BombPos.x, BombPos.y);
	PowerImage->Render(PowerPos.x, PowerPos.y);
	GrazeImage->Render(GrazePos.x, GrazePos.y);

	// ����
	RenderScoreAsImage(hdc, MaxScore(gameState), { MaxScorePos.x + 120, MaxScorePos.y + 5 });
	RenderScoreAsImage(hdc, Score(gameState), { ScorePos.x + 105, ScorePos.y + 5 });

	// ü�� �� ��ź
	RenderHpAsImage(hdc, PlayerHp(gameState), { PlayerHpPos.x + 120, PlayerHpPos.y });
	RenderBombAsImage(hdc, BombCount(gameState), { BombPos.x + 120, BombPos.y });

	// �Ŀ���
	//RenderPowerBarAsImage(hdc, CurrPowerBarFrame, PowerPos);
	PowerBarImage->RenderPercent({ PowerPos.x + 120, PowerPos.y + 5 }, 0, CurrPowerBarFrame(gameState), 1.0f);
	UpdatePowerBarMax(hdc, PowerPos);

	// ���� ����� �׸���
	if (IsEnemyPhase(gameState)) {
		RenderEnemyPhase(hdc);
		RenderTimerAsImage(hdc, RemainTime(gameState), EnemyPhasePos);
	}


	// �� �׸���
	circle->Render(circlePos.x, circlePos.y);

	RenderFPSAsImage(hdc, timer->GetFPS(), FPSPos);
}

// ���� �̹��� �ε�
void InGame::ReLoadScore()
{
	// Map�� ���� ���� key��
	const char* numberNames[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };


	// ���� �̹��� �ε�
	for (int i = 0; i < 10; ++i)
	{
		string key = numberNames[i];
		numberImageKeys.push_back(key);

		wchar_t fileName[64];
		wsprintf(fileName, L"Image/Png/Num%S.png", key.c_str());

		if (!ImageManager::GetInstance()->FindImageAdd(key))
			ImageManager::GetInstance()->AddImage(
				key,
				fileName
			);
		int a = 0;
	}
}

void InGame::ReLoadStar()
{
	string key;
	const wchar_t* path = TEXT("Image/Png/HpPoint.png");
	
	// HP �׸���
	for (int i = 0; i < MaxHpAndBomb; i++)
	{
		if (i < PlayerHp(gameState)) {
			key = "Star";
			path = TEXT("Image/Png/HpPoint.png");
		}
		else {
			key = "EmptyStar";
			path = TEXT("Image/Png/EmptyStar.png");
		}

		ImageManager::GetInstance()->AddImage(
			key,
			path
		);
	}

	// ��ź �׸���
	for (int i = 0; i < MaxHpAndBomb; i++)
	{
		if (i < BombCount(gameState)) {
			key = "Bomb";
			path = TEXT("Image/Png/GrazePoint.png");
		}
		else {
			key = "EmptyBomb";
			path = TEXT("Image/Png/EmptyStar.png");
		}

		ImageManager::GetInstance()->AddImage(
			key,
			path
		);
	}
}

// ���ڸ� �̹����� ���
void InGame::RenderScoreAsImage(HDC hdc, int number, FPOINT startPos)
{
	// ���� ��, 8�ڸ� ����
	const int digitWidth = 20;
	const int totalDigits = 10;

	// total ���̸�ŭ 0���� ä��
	string scoreStr = to_string(number);
	while (scoreStr.length() < totalDigits)
		scoreStr = "0" + scoreStr;

	// �� �ڸ����� �̹����� ���
	for (int i = 0; i < totalDigits; ++i)
	{
		char digitChar = scoreStr[i];	// �� �ڸ����� ���ڷ� ��ȯ
		string key(1, digitChar);		// ���ڸ� Ű�� ��ȯ

		// �̹����� ������ ���
		if (D2DImage* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(static_cast<int>(startPos.x + i * digitWidth), static_cast<int>(startPos.y));
		}
	}
}

// ü���� �̹����� ���
void InGame::RenderHpAsImage(HDC hdc, int number, FPOINT Pos)
{
	// ���� ��, 8�ڸ� ����
	const int StarWidth = 20;
	const int MaxStar = GameStateManager::GetInstance()->gameState.PlayerHp;

	for (int i = 0; i < MaxStar; i++) {

		if (D2DImage* img = ImageManager::GetInstance()->FindImage("Star"))
		{
			img->Render(static_cast<int>(Pos.x + i * StarWidth), static_cast<int>(Pos.y));
		}
	}
}


// ��ź�� �̹����� ���
void InGame::RenderBombAsImage(HDC hdc, int number, FPOINT Pos)
{
	// ���� ��, 8�ڸ� ����
	const int StarWidth = 20;
	const int Maxbomb = GameStateManager::GetInstance()->gameState.SpellCardCount;
	for (int i = 0; i < Maxbomb; i++) {

		if (D2DImage* img = ImageManager::GetInstance()->FindImage("Bomb"))
		{
			img->Render(static_cast<int>(Pos.x + i * StarWidth), static_cast<int>(Pos.y));
		}
	}

}


// �Ŀ� ���� �� MAX ǥ��
void InGame::UpdatePowerBarMax(HDC hdc, FPOINT pos)
{
	int number = CurrPowerBarFrame(gameState);

	const int digitWidth = 20;

	string numberStr = to_string(number);
	int len = numberStr.length();

	for (int i = 0; i < len; i++)
	{
		string key(1, numberStr[i]);

		if (D2DImage* img = ImageManager::GetInstance()->FindImage(key)) {
			if (number < 159)
				img->Render(pos.x + 130 + i * digitWidth, pos.y + 5);
		}
	}
	if (CurrPowerBarFrame(gameState) == 159)
		PowerMaxImage->Render(pos.x + 120, pos.y + 5);
}

// �Ŀ��� �̹����� ���
//void InGame::RenderPowerBarAsImage(HDC hdc, int number, FPOINT Pos)
//{
//	D2DImage* img = ImageManager::GetInstance()->FindImage("PowerBar");
//	if (!img) return;
//
//	int frameWidth = img->GetWidth();
//	int frameHeight = img->GetHeight();
//
//	// ������ ���� �ٲ���� ���� �ٽ� �׸�
//	if (CurrPowerBarFrame != prevPowerbarFrame)
//	{
//		if (PowerBarBuffer)
//		{
//			PowerBarBuffer->Release();
//			delete PowerBarBuffer;
//		}
//		if (CurrPowerBarFrame > 0)
//		{
//			// PowerBarBuffer = new Image();
//			// PowerBarBuffer->Init(frameWidth * CurrPowerBarFrame, frameHeight);
//
//			for (int i = 0; i < CurrPowerBarFrame; ++i)
//			{
//				int frameX = i % img->GetMaxFrameX();
//				int frameY = i / img->GetMaxFrameX();
//
//				img->Render(frameX, frameY);
//				// img->FrameRenderRaw(PowerBarBuffer->GetMemDC(),
//				// 	i * frameWidth, 0, frameX, frameY);
//			}
//		}
//		else
//		{
//			PowerBarBuffer = nullptr;
//		}
//		prevPowerbarFrame = CurrPowerBarFrame;
//	}
//	// ���� ���
//	if (PowerBarBuffer && CurrPowerBarFrame > 0)
//	{
//		PowerBarBuffer->Render(Pos.x + 120, Pos.y);
//	}
//}

// ���� ���� �ϸ� ���� ��ܿ� EnemyPhase �̹��� ���
void InGame::RenderEnemyPhase(HDC hdc)
{
	if (D2DImage* img = ImageManager::GetInstance()->FindImage("EnemyPhase")) {
		img->Render(EnemyPhasePos.x, EnemyPhasePos.y);
	}
	BossHpBarImage->RenderPercent({ EnemyPhasePos.x + 80, EnemyPhasePos.y + 12}, 0, CurrBossHpBarFrame(gameState), 1.0f);
	//RenderBossHpBar(hdc, currBossHpBarFrame, { EnemyPhasePos.x + 60, EnemyPhasePos.y + 5 });
}

// ���� ü�¹� �̹����� ���
//void InGame::RenderBossHpBar(HDC hdc, int number, FPOINT Pos)
//{
//	D2DImage* img = ImageManager::GetInstance()->FindImage("BossHpBar");
//	if (!img) return;
//
//	int frameWidth = img->GetWidth();
//	int frameHeight = img->GetHeight();
//
//	if (currBossHpBarFrame != prevBossHpBarFrame)
//	{
//		if (BossHpBarBuffer)
//		{
//			BossHpBarBuffer->Release();
//			delete BossHpBarBuffer;
//		}
//
//		if (currBossHpBarFrame > 0)
//		{
//			// BossHpBarBuffer = new D2DImage();
//			// BossHpBarBuffer->Init(frameWidth * currBossHpBarFrame, frameHeight);
//
//			for (int i = 0; i < currBossHpBarFrame; ++i)
//			{
//				int frameX = i % img->GetMaxFrameX();
//				int frameY = i / img->GetMaxFrameX();
//
//				img->Render(frameX, frameY);
//				// img->FrameRenderRaw(BossHpBarBuffer->GetMemDC(),
//				// 	i * frameWidth, 0, frameX, frameY);
//			}
//		}
//		else
//		{
//			BossHpBarBuffer = nullptr;
//		}
//
//		prevBossHpBarFrame = currBossHpBarFrame;
//	}
//
//	// ���� ���
//	if (BossHpBarBuffer && currBossHpBarFrame > 0)
//	{
//		BossHpBarBuffer->Render(Pos.x, Pos.y);
//	}
//}

void InGame::RenderTimerAsImage(HDC hdc, int number, FPOINT Pos)
{
	const int digitWidth = 20;
	string timeStr = to_string(number);

	while (timeStr.length() < 2)
		timeStr = "0" + timeStr;

	for (int i = 0; i < timeStr.length(); i++)
	{
		string key(1, timeStr[i]);
		if (D2DImage* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(static_cast<int>(Pos.x + i * digitWidth) + 438, static_cast<int>(Pos.y));
		}
	}
}

void InGame::RenderFPSAsImage(HDC hdc, unsigned long fps, FPOINT Pos)
{
	const int digitWidth = 20;
	string fpsStr = to_string(fps);

	FPSImage->Render(static_cast<int>(Pos.x + 60), static_cast<int>(Pos.y));
	for (int i = 0; i < fpsStr.length(); ++i)
	{
		string key(1, fpsStr[i]);
		if (D2DImage* img = ImageManager::GetInstance()->FindImage(key))
		{
			img->Render(static_cast<int>(Pos.x + i * digitWidth), static_cast<int>(Pos.y));
		}
	}
}



