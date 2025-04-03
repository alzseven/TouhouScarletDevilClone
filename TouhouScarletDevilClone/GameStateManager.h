#pragma once
#include "GameState.h"
#include "Singleton.h"

// 게임 상태 접근 헬퍼 함수들
inline int& Score(GameState* state) { return state->Score; }
inline int& MaxScore(GameState* state) { return state->MaxScore; }
inline int& PlayerHp(GameState* state) { return state->PlayerHp; }
inline int& BombCount(GameState* state) { return state->BombCount; }

inline int& CurrPowerBarFrame(GameState* state) { return state->CurrPowerBarFrame; }
inline int& CurrBossHpBarFrame(GameState* state) { return state->CurrBossHpBarFrame; }

inline bool& IsEnemyPhase(GameState* state) { return state->IsEnemyPhase; }
inline int& RemainTime(GameState* state) { return state->RemainTime; }

// 게임 상태 플래그 접근 헬퍼 함수들
inline bool& IsGameOver(GameState* state) { return state->isGameOver; }
inline bool& IsGameClear(GameState* state) { return state->isGameClear; }
inline bool& IsPaused(GameState* state) { return state->isPaused; }
inline float& PowerMultiplier(GameState* state) { return state->PowerMultiplier; }

class GameStateManager : public Singleton<GameStateManager>
{
private:
    GameState gameState;
    bool isInitialized;
    
public:
    GameStateManager() : isInitialized(false) {}
    ~GameStateManager() = default;
    
    void Init();
    void Reset();
    void Update(float dt);
    
    // 게임 상태 접근자
    GameState* GetGameState() { return &gameState; }
    
    // 게임 상태 변경 함수들
    void SetGameOver();
    void SetGameClear();
    void TogglePause();
    
    // 게임 진행 상태 확인 함수들
    bool IsGameRunning() const { return !gameState.isGameOver && !gameState.isGameClear && !gameState.isPaused; }
    bool IsGameOver() const { return gameState.isGameOver; }
    bool IsGameClear() const { return gameState.isGameClear; }
    bool IsPaused() const { return gameState.isPaused; }
};
