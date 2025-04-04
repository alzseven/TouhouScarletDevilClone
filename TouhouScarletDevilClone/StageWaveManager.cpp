#include "StageWaveManager.h"
#include "IStageWavePattern.h"
#include "Stage1Wave1Pattern.h"
#include "Stage1Wave2Pattern.h"
#include "Stage1Wave3Pattern.h"
#include "Stage1Boss.h"
#include "GameState.h"
#include "SoundPlayer.h"

void StageWaveManager::Init()
{
    // 첫 번째 웨이브 패턴 설정
    Stage1Wave1Pattern* stage1_1 = new Stage1Wave1Pattern(); 
    // stage1_1->SetItemInfos(gameState, items);
    stage1_1->Init(0.f, 10.f, "zako_pink", 10, 1.f, 0.15f);
    stageWavePatterns.push(stage1_1);

    // 두 번째 웨이브 패턴 설정
    Stage1Wave2Pattern* stage1_2 = new Stage1Wave2Pattern();
    // stage1_2->SetItemInfos(gameState, items);
    stage1_2->Init(11.f, 15.f, "fairy_white", 8, 1.2f, 0.2f);
    stageWavePatterns.push(stage1_2);
    
    // 세 번째 웨이브 패턴 설정
    Stage1Wave3Pattern* stage1_3 = new Stage1Wave3Pattern();
    // stage1_3->SetItemInfos(gameState, items);
    stage1_3->Init(17.f, 25.f, "zako_red", 6, 1.5f, 0.3f);
    stageWavePatterns.push(stage1_3);
    
    // 보스 웨이브 패턴 설정
    Stage1Boss* stage1_boss = new Stage1Boss();
    // stage1_boss->SetItemInfos(gameState, items);
    stage1_boss->Init(30.f, 999.f, "sakuya_idle", 1, 2.0f, 0.0f);
    stageWavePatterns.push(stage1_boss);
   
    currentStageWave = stageWavePatterns.front();
    stageWavePatterns.pop();

    stageCurrentTime = 0.f;
}

// void StageWaveManager::SetIteminfos(GameState* gameState, vector<BHItem*>* items)
// {
//     this->gameState = gameState;
//     this->items = items;
// }

void StageWaveManager::Release()
{
    delete currentStageWave;
}

void StageWaveManager::Update(float dt)
{
    stageCurrentTime += dt;
    currentStageWave->Update(dt);
    if (currentStageWave->IsWaveDone(stageCurrentTime))
    {
        if (stageWavePatterns.empty())
        {
            // 스테이지 클리어 처리
            if (gameState)
            {
                // 스테이지 클리어 보너스 점수 추가
                gameState->Score += 10000;
                
                // 스테이지 클리어 효과음 재생
                // SoundPlayer::GetInstance()->SoundOn("stage_clear");
                
                // 게임 상태를 스테이지 클리어로 변경
                gameState->isGameClear = true;
                
                // 다음 스테이지로 진행하거나 게임 종료 처리를 위한 추가 로직
                // 현재는 MVP 구현이므로 게임 클리어로 처리
            }
        }
        else
        {
            // 다음 웨이브로 진행
            currentStageWave = stageWavePatterns.front();
            stageWavePatterns.pop();
            
            // 웨이브 전환 효과음 재생
            // SoundPlayer::GetInstance()->SoundOn("wave_change");
        }
    }
}

void StageWaveManager::Render(){}