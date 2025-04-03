#pragma once
#include "ItemBehavior.h"

class ScoreItemBehavior : public ItemBehavior
{
private:
	int ScoreValue;
public:
	ScoreItemBehavior(int scoreValue) : ScoreValue(scoreValue) {}
	void OnCollect(GameState* state) override;
};

