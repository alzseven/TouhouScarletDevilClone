#pragma once
#include "GameState.h"

inline int& Score(GameState* state) { return state->Score; }
inline int& MaxScore(GameState* state) { return state->MaxScore; }
inline int& PlayerHp(GameState* state) { return state->PlayerHp; }
inline int& BombCount(GameState* state) { return state->BombCount; }

inline int& CurrPowerBarFrame(GameState* state) { return state->CurrPowerBarFrame; }
inline int& CurrBossHpBarFrame(GameState* state) { return state->CurrBossHpBarFrame; }

inline bool& IsEnemyPhase(GameState* state) { return state->IsEnemyPhase; }
inline int& RemainTime(GameState* state) { return state->RemainTime; }
