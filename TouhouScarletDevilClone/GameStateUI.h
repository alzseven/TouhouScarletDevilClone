#include "UI.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "InputManager.h"
#include "Timer.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "SoundPlayer.h"

// 게임 상태 화면 관련 추가 코드
class GameScreenUI
{
private:
    D2DImage* gameOverScreen;
    D2DImage* gameClearScreen;
    D2DImage* pauseScreen;
    D2DImage* spellCardIcon;  // 스펠카드 아이콘
    D2DImage* spellCardCooldown;  // 스펠카드 쿨다운 표시
    GameState* gameState;

public:
    GameScreenUI(GameState* state)
    {
        gameState = state;
        
        // 게임 상태 화면 이미지 로드
        gameOverScreen = ImageManager::GetInstance()->AddImage("GameOverScreen", TEXT("Image/Png/GameOver.png"));
        gameClearScreen = ImageManager::GetInstance()->AddImage("GameClearScreen", TEXT("Image/Png/GameClear.png"));
        pauseScreen = ImageManager::GetInstance()->AddImage("PauseScreen", TEXT("Image/Png/Pause.png"));
        
        // 스펠카드 관련 이미지 로드
        spellCardIcon = ImageManager::GetInstance()->AddImage("SpellCardIcon", TEXT("Image/Png/SpellCardIcon.png"));
        spellCardCooldown = ImageManager::GetInstance()->AddImage("SpellCardCooldown", TEXT("Image/Png/SpellCardCooldown.png"));
    }
    
    ~GameScreenUI() {}
    
    void Render(HDC hdc)
    {
        // 게임 상태에 따라 적절한 화면 렌더링
        if (gameState->isGameOver) {
            RenderGameOverScreen(hdc);
        } else if (gameState->isGameClear) {
            RenderGameClearScreen(hdc);
        } else if (gameState->isPaused) {
            RenderPauseScreen(hdc);
        }
        
        // 게임 진행 중일 때 스펠카드 UI 렌더링
        if (!gameState->isGameOver && !gameState->isGameClear && !gameState->isPaused) {
            RenderSpellCardUI(hdc);
        }
    }
    
    void RenderGameOverScreen(HDC hdc)
    {
        if (gameOverScreen) {
            gameOverScreen->Render(WINSIZE_X / 2 - gameOverScreen->GetWidth() / 2, 
                                  WINSIZE_Y / 2 - gameOverScreen->GetHeight() / 2);
            
            // 최종 점수 표시
            // 여기에 점수 렌더링 코드 추가
        }
    }
    
    void RenderGameClearScreen(HDC hdc)
    {
        if (gameClearScreen) {
            gameClearScreen->Render(WINSIZE_X / 2 - gameClearScreen->GetWidth() / 2, 
                                   WINSIZE_Y / 2 - gameClearScreen->GetHeight() / 2);
            
            // 최종 점수 및 클리어 보너스 표시
            // 여기에 점수 렌더링 코드 추가
        }
    }
    
    void RenderPauseScreen(HDC hdc)
    {
        if (pauseScreen) {
            pauseScreen->Render(WINSIZE_X / 2 - pauseScreen->GetWidth() / 2, 
                               WINSIZE_Y / 2 - pauseScreen->GetHeight() / 2);
        }
    }
    
    void RenderSpellCardUI(HDC hdc)
    {
        // 스펠카드 아이콘 및 개수 표시
        if (spellCardIcon) {
            // 화면 오른쪽 하단에 스펠카드 아이콘 표시
            int iconX = WINSIZE_X - 100;
            int iconY = WINSIZE_Y - 50;
            
            // 남은 스펠카드 개수만큼 아이콘 표시
            for (int i = 0; i < gameState->SpellCardCount; i++) {
                spellCardIcon->Render(iconX - i * 30, iconY);
            }
            
            // 스펠카드 쿨다운 표시
            if (spellCardCooldown) {
                // 플레이어 객체에서 쿨다운 비율을 가져와 표시
                // 여기서는 임시로 0.5 (50% 쿨다운)으로 설정
                float cooldownRatio = 0.5f;
                
                // 쿨다운 바 렌더링
                spellCardCooldown->Render(iconX - 50, iconY + 20);
                
                // 쿨다운 진행 상태 표시 (색상 변경 또는 오버레이)
                // 여기에 쿨다운 진행 상태 렌더링 코드 추가
            }
        }
    }
};

// UI 클래스 확장 코드
inline void UpdateUI(UI* ui, GameState* gameState, float dt)
{
    // 기존 UI 업데이트 로직 유지
    ui->Update(dt);
    
    // 게임 상태에 따른 추가 처리
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_ESCAPE)) {
        // ESC 키를 누르면 일시정지 토글
        GameStateManager::GetInstance()->TogglePause();
    }
    
    // 게임 오버 또는 게임 클리어 상태에서 R 키를 누르면 게임 재시작
    if ((gameState->isGameOver || gameState->isGameClear) && 
        KeyManager::GetInstance()->IsOnceKeyDown('R')) {
        GameStateManager::GetInstance()->Reset();
        
        // 게임 재시작 효과음 재생
        SoundPlayer::GetInstance()->SoundOn("game_restart");
    }
}

// 게임 상태 관리 확장 코드
inline void ExtendedGameStateUpdate(GameState* gameState, float dt)
{
    // 게임이 진행 중일 때만 업데이트
    if (!gameState->isGameOver && !gameState->isGameClear && !gameState->isPaused) {
        // 파워 배율 업데이트
        gameState->PowerMultiplier = 1.0f + (float)gameState->CurrPowerBarFrame / gameState->MaxPowerBarFrame;
        
        // 보스 체력이 0이 되면 게임 클리어 처리
        if (gameState->BossHp <= 0 && !gameState->IsEnemyPhase) {
            gameState->isGameClear = true;
            
            // 게임 클리어 효과음 재생
            SoundPlayer::GetInstance()->SoundOn("game_clear");
            
            // 클리어 보너스 점수 추가
            gameState->Score += 50000;
            
            // 최고 점수 갱신
            if (gameState->Score > gameState->MaxScore) {
                gameState->MaxScore = gameState->Score;
            }
        }
        
        // 플레이어 체력이 0이 되면 게임 오버 처리
        if (gameState->PlayerHp <= 0) {
            gameState->isGameOver = true;
            
            // 게임 오버 효과음 재생
            SoundPlayer::GetInstance()->SoundOn("game_over");
        }
    }
}
