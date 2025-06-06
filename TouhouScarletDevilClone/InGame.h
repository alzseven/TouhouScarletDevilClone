#pragma once
#include "GameObject.h"

// 나중에 중간 보스, 최종 보스 등장 할때 구현할 열거형 미리 해둠
enum class BossPhaseType
{
	None,
	MidBoss,
	FinalBoss
};

class D2DImage;
class Timer;
struct GameState;
// class UI;
class InGame
{
private:
	FPOINT pos;

	Timer* timer;

	vector<POINT> BackGroubdTile;
	D2DImage* BackGround_Image;
	D2DImage* BackGround;
	bool isBgReder;

	GameState* gameState = nullptr;



	FPOINT StagePos{ WINSIZE_X - 850, WINSIZE_Y - 620 };	// 스테이지 위치
	D2DImage* Stage;

	// 점수 이미지를 담을 맵
	vector<string> numberImageKeys;

	FPOINT MaxScorePos{ WINSIZE_X - 370, WINSIZE_Y - 600 };	// 최대 점수 위치
	D2DImage* MaxScoreImage;

	FPOINT ScorePos{ WINSIZE_X - 355, WINSIZE_Y - 560 };	// 점수 위치
	D2DImage* ScoreImage;

	FPOINT PlayerHpPos{ WINSIZE_X - 370, WINSIZE_Y - 500 };	// 플레이어 체력 위치
	D2DImage* PlayerHpBarImage;

	D2DImage* PlayerHpImage;

	FPOINT BombPos{ WINSIZE_X - 370, WINSIZE_Y - 455 };	// 폭탄 위치
	D2DImage* BombImage;

	static const int MaxHpAndBomb = 8;

	FPOINT PowerPos{ WINSIZE_X - 370, WINSIZE_Y - 380 };	// 파워 위치
	int elapPowerbarFrame;
	D2DImage* PowerImage;
	D2DImage* PowerBarImage;
	D2DImage* PowerMaxImage;
	D2DImage* PowerBarBuffer = nullptr;
	int prevPowerbarFrame = -1;

	FPOINT GrazePos{ WINSIZE_X - 370, WINSIZE_Y - 330 };	// 그레이즈 위치
	D2DImage* GrazeImage;

	// 보스 등장하면 나타나는 것들
	FPOINT EnemyPhasePos{ StagePos.x - 5, StagePos.y + 5 };	// 적 등장 위치
	D2DImage* EnemyPhaseImage;
	D2DImage* BossHpBarImage;
	D2DImage* BossHpBarBuffer = nullptr;
	int prevBossHpBarFrame = -1;

	// 타이머 관련(보스 등장 시, isEnemyPhase가 true가 되면 카운트 시작)
	float elapsedTime = 0.0f;

	// 꾸미기
	FPOINT circlePos{ WINSIZE_X - 330, WINSIZE_Y - 350 };
	D2DImage* circle;

	// fps 표기
	FPOINT FPSPos{ WINSIZE_X - 200, WINSIZE_Y - 100 };
	D2DImage* FPSImage;
	

public:
	InGame(GameState* state);
	virtual ~InGame();


	void Update(float dt);
	void Render(HDC hdc);
	void ReLoadScore();
	void ReLoadStar();
	void RenderScoreAsImage(HDC hdc, int number, FPOINT startPos);
	void RenderHpAsImage(HDC hdc, int number, FPOINT Pos);
	void RenderBombAsImage(HDC hdc, int number, FPOINT Pos);
	void UpdatePowerBarMax(HDC hdc, FPOINT pos);

	//void RenderPowerBarAsImage(HDC hdc, int number, FPOINT Pos);
	void RenderEnemyPhase(HDC hdc);
	//void RenderBossHpBar(HDC hdc, int number, FPOINT Pos);
	void RenderTimerAsImage(HDC hdc, int number, FPOINT Pos);
	void RenderFPSAsImage(HDC hdc, unsigned long fps, FPOINT Pos);


	inline void SetTimer(Timer* t) { timer = t; }


};

