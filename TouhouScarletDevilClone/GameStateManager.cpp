#include "GameStateManager.h"
#include "SoundPlayer.h"

void GameStateManager::Init()
{
    // 게임 상태 초기화
    gameState.Score = 0;
    gameState.MaxScore = 0;
    gameState.PlayerHp = 3;
    gameState.BombCount = 3;
    gameState.CurrPowerBarFrame = 0;
    gameState.MaxPowerBarFrame = 100;
    gameState.PowerMultiplier = 1.0f;
    gameState.CurrBossHpBarFrame = 350;
    gameState.IsEnemyPhase = true;
    gameState.RemainTime = 60;
    
    // 게임 상태 플래그 초기화
    gameState.isGameOver = false;
    gameState.isGameClear = false;
    gameState.isPaused = false;
    
    isInitialized = true;
}

void GameStateManager::Reset()
{
    // 게임 상태 리셋
    gameState.Score = 0;
    gameState.PlayerHp = 3;
    gameState.BombCount = 3;
    gameState.CurrPowerBarFrame = 0;
    gameState.PowerMultiplier = 1.0f;
    gameState.CurrBossHpBarFrame = 350;
    gameState.IsEnemyPhase = true;
    gameState.RemainTime = 60;
    
    // 게임 상태 플래그 리셋
    gameState.isGameOver = false;
    gameState.isGameClear = false;
    gameState.isPaused = false;
    
    // 게임 리셋 효과음 재생
    // SoundPlayer::GetInstance()->SoundOn("game_reset");
}

void GameStateManager::Update(float dt)
{
    if (!isInitialized) {
        Init();
    }
    
    // 게임이 진행 중일 때만 업데이트
    if (IsGameRunning()) {
        // 시간 감소 (필요한 경우)
        if (gameState.RemainTime > 0) {
            gameState.RemainTime -= dt;
            if (gameState.RemainTime <= 0) {
                gameState.RemainTime = 0;
                // 시간 초과 처리 (필요한 경우)
            }
        }
        
        // 보스 체력이 0이 되면 게임 클리어 처리
        if (gameState.CurrBossHpBarFrame <= 0 && !gameState.IsEnemyPhase) {
            SetGameClear();
        }
        
        // 플레이어 체력이 0이 되면 게임 오버 처리
        if (gameState.PlayerHp <= 0) {
            SetGameOver();
        }
    }
}

void GameStateManager::SetGameOver()
{
    if (!gameState.isGameOver) {
        gameState.isGameOver = true;
        
        // 게임 오버 효과음 재생
        SoundPlayer::GetInstance()->SoundOn("game_over");
    }
}

void GameStateManager::SetGameClear()
{
    if (!gameState.isGameClear) {
        gameState.isGameClear = true;
        
        // 게임 클리어 효과음 재생
        SoundPlayer::GetInstance()->SoundOn("game_clear");
        
        // 클리어 보너스 점수 추가
        gameState.Score += 50000;
        
        // 최고 점수 갱신
        if (gameState.Score > gameState.MaxScore) {
            gameState.MaxScore = gameState.Score;
        }
    }
}

void GameStateManager::TogglePause()
{
    gameState.isPaused = !gameState.isPaused;
    
    // 일시정지 효과음 재생
    if (gameState.isPaused) {
        SoundPlayer::GetInstance()->SoundOn("game_pause");
    } else {
        SoundPlayer::GetInstance()->SoundOn("game_resume");
    }
}
