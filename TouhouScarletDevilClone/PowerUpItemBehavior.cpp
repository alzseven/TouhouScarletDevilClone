#include "PowerUpItemBehavior.h"
#include "GameStateManager.h"

void PowerUpItemBehavior::OnCollect(GameState* state)
{
	CurrPowerBarFrame(state) += PowerUpValue;
}
