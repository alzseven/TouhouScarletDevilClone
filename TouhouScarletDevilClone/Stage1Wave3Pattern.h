#pragma once
#include "IStageWavePattern.h"

class BHObject;
class IObjectActionPattern;
class Stage1Wave3Pattern : public IStageWavePattern
{
private:
    int currentSpawnCount;
    FPOINT initialPosTop;
    FPOINT marginBetweenSpawn;
    
    vector<IObjectActionPattern*> actions;
public:
    std::vector<FPOINT> GetSpawnPoints(int spawnAmount) override;
    std::vector<IObjectActionPattern*> GetObjectActionPatterns(BHObject* target) override;
    void Update(float deltaTime) override;
    void Init(float startTime, float endTime, string enemyShapeKey, int spawnAmount, float spawnDelay, float multiSpawnDelay) override;
};
