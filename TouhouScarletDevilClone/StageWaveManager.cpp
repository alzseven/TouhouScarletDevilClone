#include "StageWaveManager.h"

#include "IStageWavePattern.h"

void StageWaveManager::Init()
{
    Stage1Wave1Pattern* stage1_1 = new Stage1Wave1Pattern(); 
    stage1_1->Init(0.f, 99.f, "enemy", 1, 1.f, 0.15f);

    stageWavePatterns = new std::queue<IStageWavePattern*>();
    
    State1Wave1Pattern* stage1_1 = new State1Wave1Pattern(); 
    stage1_1->Init(0.f, 20.f, "cirno_idle", 10, 1.f, 0.15f);
    stageWavePatterns->push(stage1_1);

    // 여기에 IStageWavePattern에서 생성한 웨이브 객체 생성해서 넣고 Init 하시오

    stageWavePatterns.push(stage1_1);
   
    currentStageWave = stageWavePatterns.front();
    stageWavePatterns.pop();

    stageCurrentTime = 0.f;
}

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
            //TODO: Stage clear
        }
        else
        {
            currentStageWave = stageWavePatterns.front();
            stageWavePatterns.pop();
        }

    }
}

void StageWaveManager::Render(){}
