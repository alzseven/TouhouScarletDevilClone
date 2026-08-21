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
    // isStageWaveFinished = false;
    // 첫 번째 웨이브 패턴 설정
    unique_ptr<Stage1Wave1Pattern> stage1_1 = std::make_unique<Stage1Wave1Pattern>();
    stage1_1->Init(0.f, 10.f, "zako_pink", 10, 1.f, 0.15f);
    stageWavePatterns.push(std::move(stage1_1));

    // 두 번째 웨이브 패턴 설정
    unique_ptr<Stage1Wave2Pattern> stage1_2 = std::make_unique<Stage1Wave2Pattern>();
    stage1_2->Init(11.f, 15.f, "fairy_white", 8, 1.2f, 0.2f);
    stageWavePatterns.push(std::move(stage1_2));
    
    // 세 번째 웨이브 패턴 설정
    unique_ptr<Stage1Wave3Pattern> stage1_3 = std::make_unique<Stage1Wave3Pattern>();
    stage1_3->Init(17.f, 25.f, "zako_red", 6, 1.5f, 0.3f);
    stageWavePatterns.push(std::move(stage1_3));
    
    // 보스 웨이브 패턴 설정
    unique_ptr<Stage1Boss> stage1_boss = std::make_unique<Stage1Boss>();
    stage1_boss->Init(30.f, 999.f, "sakuya_idle", 1, 2.0f, 0.0f);
    stageWavePatterns.push(std::move(stage1_boss));
   
    currentStageWave = std::move(stageWavePatterns.front());
    stageWavePatterns.pop();

    stageCurrentTime = 0.f;
}


void StageWaveManager::Release()
{
    currentStageWave.reset();

    while (!stageWavePatterns.empty())
    {
        stageWavePatterns.pop();
    }
}

void StageWaveManager::Update(float dt)
{
    if (!currentStageWave) return;
    
    stageCurrentTime += dt;
    currentStageWave->Update(dt);
    if (currentStageWave->IsWaveDone(stageCurrentTime))
    {
        if (!stageWavePatterns.empty())
        {
            // 다음 웨이브로 진행
            currentStageWave = std::move(stageWavePatterns.front());
            stageWavePatterns.pop();
            
            // 웨이브 전환 효과음 재생
            // SoundPlayer::GetInstance()->SoundOn("wave_change");
        }
        else
        {
            currentStageWave.reset();
            
            // // 스테이지 클리어 처리
            // if (!isStageWaveFinished)
            // {
            //     if (gameState)
            //     {
            //         // 스테이지 클리어 보너스 점수 추가
            //         gameState->Score += 10000;
            //     
            //         // 스테이지 클리어 효과음 재생
            //         // SoundPlayer::GetInstance()->SoundOn("stage_clear");
            //     
            //         // 게임 상태를 스테이지 클리어로 변경
            //         gameState->isGameClear = true;
            //     
            //         // 다음 스테이지로 진행하거나 게임 종료 처리를 위한 추가 로직
            //         // 현재는 MVP 구현이므로 게임 클리어로 처리
            //         isStageWaveFinished = true;
            //     }
            // }
        }
    }
}

void StageWaveManager::Render() {}

