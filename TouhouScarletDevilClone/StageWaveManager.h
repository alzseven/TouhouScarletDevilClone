#pragma once
#include <queue>
#include <vector>

class IStageWavePattern;

class StageWaveManager
{
    std::queue<IStageWavePattern*> stageWavePatterns;
    IStageWavePattern* currentStageWave;
    float stageCurrentTime;
    GameState* gameState;
    std::vector<BHItem*>* items;
public:
    void Init();
    void SetIteminfos(GameState* gameState, std::vector<BHItem*>* items);
    void SetStageWavePatterns(std::queue<IStageWavePattern*> stageWavePatterns) { this->stageWavePatterns = stageWavePatterns; }
    void Release();
    void Update(float dt);
    void Render();
};
