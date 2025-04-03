#pragma once
#include <queue>
#include <vector>
#include "config.h"

struct GameState;
class BHItem;
class IStageWavePattern;

class StageWaveManager
{
    std::queue<IStageWavePattern*> stageWavePatterns;
    IStageWavePattern* currentStageWave;
    float stageCurrentTime;
    GameState* gameState;
    vector<BHItem*>* items;
public:
    void Init();
    void SetIteminfos(GameState* gameState,vector<BHItem*>* items);
    void SetStageWavePatterns(std::queue<IStageWavePattern*> stageWavePatterns) { this->stageWavePatterns = stageWavePatterns; }
    void Release();
    void Update(float dt);
    void Render();
};