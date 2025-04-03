#pragma once

struct GameState
{
	int Score = 0;
	int MaxScore = 0;
	int PlayerHp = 3;
	int BombCount = 3;

	int CurrPowerBarFrame = 0;

	int CurrBossHpBarFrame = 350;
	bool IsEnemyPhase = true;
	int RemainTime = 60;
};
