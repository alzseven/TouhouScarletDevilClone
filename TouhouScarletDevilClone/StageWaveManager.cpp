#include "StageWaveManager.h"

#include "IStageWavePattern.h"

void StageWaveManager::Init()
{
    Stage1Wave1Pattern* stage1_1 = new Stage1Wave1Pattern(); 
    stage1_1->Init(0.f, 99.f, "enemy", 1, 1.f, 0.15f);
    stageWavePatterns.push(stage1_1);
    //...

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
