#pragma once
#include "GameObject.h"

// 나중에 중간 보스, 최종 보스 등장 할때 구현할 열거형 미리 해둠
enum class BossPhaseType
{
	None,
	MidBoss,
	FinalBoss
};

class Image;
class Timer;
class UI
{
private:
	FPOINT pos;

	Timer* timer;

	Image* BackGround_Image;
	Image* BackGround;
	bool isBgReder;




	FPOINT StagePos{ WINSIZE_X - 850, WINSIZE_Y - 620 };	// 스테이지 위치
	Image* Stage;

	// 점수 이미지를 담을 맵
	vector<string> numberImageKeys;

	FPOINT MaxScorePos{ WINSIZE_X - 330, WINSIZE_Y - 600 };	// 최대 점수 위치
	int MaxScore;
	Image* MaxScoreImage;

	FPOINT ScorePos{ WINSIZE_X - 281, WINSIZE_Y - 560 };	// 점수 위치
	int Score;
	Image* ScoreImage;

	FPOINT PlayerHpPos{ WINSIZE_X - 330, WINSIZE_Y - 500 };	// 플레이어 체력 위치
	int PlayerHp;
	Image* PlayerHpBarImage;

	Image* PlayerHpImage;

	FPOINT BombPos{ WINSIZE_X - 330, WINSIZE_Y - 455 };	// 폭탄 위치
	int BombCount;
	Image* BombImage;

	static const int MaxHpAndBomb = 8;

	FPOINT PowerPos{ WINSIZE_X - 330, WINSIZE_Y - 380 };	// 파워 위치
	int currPowerbarFrame;
	int elapPowerbarFrame;
	Image* PowerImage;
	Image* PowerBarImage;
	Image* PowerMaxImage;
	Image* PowerBarBuffer = nullptr;
	int prevPowerbarFrame = -1;

	FPOINT GrazePos{ WINSIZE_X - 330, WINSIZE_Y - 330 };	// 그레이즈 위치
	int Graze;
	Image* GrazeImage;

	// 보스 등장하면 나타나는 것들
	bool isEnemyPhase;
	int currBossHpBarFrame;
	FPOINT EnemyPhasePos{ StagePos.x + 10, StagePos.y + 10 };	// 적 등장 위치
	Image* EnemyPhaseImage;
	Image* BossHpBarImage;
	Image* BossHpBarBuffer = nullptr;
	int prevBossHpBarFrame = -1;

	// 타이머 관련(보스 등장 시, isEnemyPhase가 true가 되면 카운트 시작)
	float elapsedTime = 0.0f;
	int remainTime = 60;

	// 꾸미기
	FPOINT circlePos{ WINSIZE_X - 250, WINSIZE_Y - 280 };
	Image* circle;

	// fps 표기
	FPOINT FPSPos{ WINSIZE_X - 200, WINSIZE_Y - 100 };
	Image* FPSImage;
	

public:
	UI();
	virtual ~UI();


	void Update(float dt);
	void Render(HDC hdc);
	void ReLoadScore();
	void ReLoadStar();
	void RenderScoreAsImage(HDC hdc, int number, FPOINT startPos);
	void RenderHpAsImage(HDC hdc, int number, FPOINT Pos);
	void RenderBombAsImage(HDC hdc, int number, FPOINT Pos);
	void UpdatePowerBarMax(HDC hdc, FPOINT pos);

	void RenderPowerBarAsImage(HDC hdc, int number, FPOINT Pos);
	void RenderEnemyPhase(HDC hdc);
	void RenderBossHpBar(HDC hdc, int number, FPOINT Pos);
	void RenderTimerAsImage(HDC hdc, int number, FPOINT Pos);
	void RenderFPSAsImage(HDC hdc, unsigned long fps, FPOINT Pos);


	inline void SetMaxScore(int score) { MaxScore = score; }
	inline int GetMaxScore() { return MaxScore; }
	inline void SetScore(int score) { Score = score; }
	inline int GetScore() { return Score; }
	inline void SetPlayerHp(int hp) { PlayerHp = hp; }
	inline int GetPlayerHp() { return PlayerHp; }
	inline void SetBombCount(int bomb) { BombCount = bomb; }
	inline int GetBombCount() { return BombCount; }
	inline void SetTimer(Timer* t) { timer = t; }


};

