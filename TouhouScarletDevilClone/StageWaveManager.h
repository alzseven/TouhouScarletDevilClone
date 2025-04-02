#pragma once
#include <queue>
#include <vector>

class IStageWavePattern;

class StageWaveManager
{
    std::queue<IStageWavePattern*>* stageWavePatterns;
    IStageWavePattern* currentStageWave;
    float stageCurrentTime;
public:
    void Init();
    void SetStageWavePatterns(std::queue<IStageWavePattern*>* stageWavePatterns) { this->stageWavePatterns = stageWavePatterns; }
    void Release();
    void Update(float dt);
    void Render();
};
