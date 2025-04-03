#include "PowerUpItemBehavior.h"
#include "GameStateManager.h"
#include "SoundPlayer.h"

void PowerUpItemBehavior::OnCollect(GameState* state)
{
	// 파워 값 증가
	state->CurrPowerBarFrame += PowerUpValue;
    
	// 최대 파워 값을 초과하지 않도록 제한
	if (state->CurrPowerBarFrame > state->MaxPowerBarFrame) {
		state->CurrPowerBarFrame = state->MaxPowerBarFrame;
	}
    
	// 파워 값에 따라 파워 배율 조정 (0.01 ~ 2.0 범위)
	state->PowerMultiplier = 1.0f + (float)state->CurrPowerBarFrame / state->MaxPowerBarFrame;
    
	// 파워업 아이템 획득 효과음 재생
	SoundPlayer::GetInstance()->SoundOn("power_up");
    
	// 보너스 점수 추가 (파워업 아이템 획득 보너스)
	state->Score += 1000;
}
