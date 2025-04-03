#pragma once
#include "config.h"
#include "IStageWavePattern.h"

class BHObject;
class IObjectActionPattern;
class Stage1Wave1Pattern : public IStageWavePattern
{
private:
    int currentSpawnCount;
    FPOINT initalPosLeft;
    FPOINT marginBetweenSpawn;
    
    vector<IObjectActionPattern*> actions;
public:
    std::vector<FPOINT> GetSpawnPoints(int spawnAmount) override;
    std::vector<IObjectActionPattern*> GetObjectActionPatterns(BHObject* target) override;
    void Update(float deltaTime) override;
    // void Spawn() override;

    // void SetActions(vector<IObjectActionPattern*> actions) { this->actions = actions; }
    //Test
    void Init(float startTime, float endTime, string enemyShapeKey, int spawnAmount, float spawnDelay, float multiSpawnDelay) override;
    // void Init(FPOINT initalPosLeft, FPOINT initalPosRight, FPOINT marginBetweenSpawn);
};
