#pragma once
#include "config.h"

class BHObject;
class IObjectActionPattern;
class BHEnemy;

class IStageWavePattern
{
protected:
    float patternStartTime;
    float patternEndTime;

    //Spawn params
    string enemyShapeKey;
    
    int spawnAmount;

    //TODO: implement this with function inside inheritors?
    std::vector<FPOINT> spawnPoints; 
    std::vector<IObjectActionPattern*> objectActionPatterns;
    
    
    float spawnDelay;
    float multiSpawnDelay;


    // float spawnTimer;
    float timeElpased;

    std::vector<BHObject*> spawnedObjects;

    virtual std::vector<FPOINT> GetSpawnPoints(int spawnAmount) = 0;
    virtual std::vector<IObjectActionPattern*> GetObjectActionPatterns(BHObject* target) = 0;
public:
    // virtual void Spawn() = 0;

    virtual void Update(float deltaTime) = 0;

    virtual void Init(float startTime, float endTime, string enemyShapeKey, int spawnAmount, float spawnDelay, float multiSpawnDelay);    

    virtual bool IsWaveDone(float currentTime);
};

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

class Stage1Boss : public IStageWavePattern
{
    std::vector<FPOINT> GetSpawnPoints(int spawnAmount) override;
    std::vector<IObjectActionPattern*> GetObjectActionPatterns(BHObject* target) override;
    void Update(float deltaTime) override;
    
    //Test
    void Init(float startTime, float endTime, string enemyShapeKey, int spawnAmount, float spawnDelay, float multiSpawnDelay) override;
    
};



// 여기에 웨이브 클래스 IStageWavePattern 상속해서 만드시오