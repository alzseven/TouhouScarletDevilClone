#pragma once

struct GameState
{
	int Score = 0;
	int MaxScore = 0;
	int PlayerHp = 3;
	int BombCount = 3;
	int SpellCardCount = 3; // 스펠카드(봄) 개수

	int CurrPowerBarFrame = 0;
	int MaxPowerBarFrame = 100;  // 최대 파워 값
	float PowerMultiplier = 1.0f; // 파워 배율 (파워에 따라 공격력 증가)

	int BossHp = 1000;       // 보스 현재 체력
	int BossMaxHp = 1000;    // 보스 최대 체력
	int CurrBossHpBarFrame = 350;
	bool IsEnemyPhase = true;
	int RemainTime = 60;
    
	// 게임 상태 플래그
	bool isGameOver = false;
	bool isGameClear = false;
	bool isPaused = false;
};
