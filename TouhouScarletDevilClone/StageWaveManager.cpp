#include "StageWaveManager.h"

#include "IStageWavePattern.h"

void StageWaveManager::Init()
{
    
    
    // currentStageWave = new State1Wave1Pattern();
    // currentStageWave->Init(0.f, 99.f, "enemy", 10, 1.f, 0.15f);

    stageWavePatterns = new std::queue<IStageWavePattern*>();
    
    State1Wave1Pattern* stage1_1 = new State1Wave1Pattern(); 
    stage1_1->Init(0.f, 20.f, "cirno_idle", 10, 1.f, 0.15f);
    stageWavePatterns->push(stage1_1);
    //...

    currentStageWave = stageWavePatterns->front();
    stageWavePatterns->pop();

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
        if (stageWavePatterns->empty())
        {
            //TODO: Stage clear
        }
        else
        {
            currentStageWave = stageWavePatterns->front();
            stageWavePatterns->pop();
        }

    }
}

void StageWaveManager::Render()
{
}
