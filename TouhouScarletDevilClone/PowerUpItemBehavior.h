#pragma once
#include "ItemBehavior.h"

class PowerUpItemBehavior : public ItemBehavior
{
private:
	int PowerUpValue;
public:
	PowerUpItemBehavior(int powerUpValue) : PowerUpValue(powerUpValue) {}
	void OnCollect(GameState* state) override;
};

