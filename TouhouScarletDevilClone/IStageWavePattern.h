#pragma once

class BHEnemy;

class IStageWavePattern
{
    float patternStartTime;
    float patternEndTime;
    BHEnemy* enemyToSpawn;

    //Shoot params
    float spawnDelay;
    int spawnAmount;
    float spawnAngle;
    float spawnAngleRate;
    // float spawnSpeed;
    // float spawnSpeedRate;
    float multiSpawnDelay;
    
    float shootTimer;


    float timeElpased;
public:
    virtual void Spawn() = 0;
    virtual void Update(float deltaTime) = 0;
};

class State1Wave1Pattern : public IStageWavePattern
{
    int currentSpawnCount;
    
    void Update(float deltaTime) override;
    void Spawn() override;

    //Test
    void Init();
};