#include "ScoreItemBehavior.h"
#include "GameStateManager.h"

void ScoreItemBehavior::OnCollect(GameState* state)
{
	Score(state) += ScoreValue;
}
