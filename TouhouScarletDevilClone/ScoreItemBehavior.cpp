#include "ScoreItemBehavior.h"
#include "GameStateManager.h"
#include "SoundPlayer.h"

void ScoreItemBehavior::OnCollect(GameState* state)
{
	// 점수 추가
	state->Score += ScoreValue;
    
	// 최고 점수 갱신
	if (state->Score > state->MaxScore) {
		state->MaxScore = state->Score;
	}
    
	// 점수 아이템 획득 효과음 재생
	SoundPlayer::GetInstance()->SoundOn("score_up");
    
	// 특정 점수 구간에 도달하면 추가 보상 (예: 추가 생명)
	if (state->Score >= 100000 && state->Score % 100000 < ScoreValue) {
		// 추가 생명 부여
		state->PlayerHp++;
        
		// 추가 생명 획득 효과음 재생
		SoundPlayer::GetInstance()->SoundOn("extra_life");
	}
}
