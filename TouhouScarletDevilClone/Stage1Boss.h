#pragma once
#include "IStageWavePattern.h"

class BHBoss;
class BHObject;
class IObjectActionPattern;
class Stage1Boss : public IStageWavePattern
{
private:
    FPOINT bossPosition;
    BHBoss* boss;
    bool isBossSpawned;
    float bossSpawnTimer;
    float bossSpawnDelay;
    
    std::vector<IObjectActionPattern*> bossPatterns;
    
public:
    Stage1Boss() : boss(nullptr), isBossSpawned(false), bossSpawnTimer(0.f), bossSpawnDelay(2.0f) {}
    ~Stage1Boss() {}
    
    std::vector<FPOINT> GetSpawnPoints(int spawnAmount) override;
    std::vector<IObjectActionPattern*> GetObjectActionPatterns(BHObject* target) override;
    void Update(float deltaTime) override;
    void Init(float startTime, float endTime, string enemyShapeKey, int spawnAmount, float spawnDelay, float multiSpawnDelay) override;
};
