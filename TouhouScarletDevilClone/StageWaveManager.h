#pragma once
#include <queue>
#include <vector>
#include <memory>
#include "config.h"
#include "IStageWavePattern.h"

struct GameState;
class BHItem;

class StageWaveManager
{
    std::queue<std::unique_ptr<IStageWavePattern>> stageWavePatterns;
    std::unique_ptr<IStageWavePattern> currentStageWave;
    float stageCurrentTime = 0.0f;
    // GameState* gameState = nullptr;
    // bool isStageWaveFinished = false;
public:
    StageWaveManager() = default;
    virtual ~StageWaveManager() = default;
    
    void Init();
    void Release();
    void Update(float dt);
    void Render();
    
    StageWaveManager(const StageWaveManager&) = delete;
    StageWaveManager& operator=(const StageWaveManager&) = delete;
};