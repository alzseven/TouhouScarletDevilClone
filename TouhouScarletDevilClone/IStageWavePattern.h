#pragma once
#include "config.h"

struct GameState;
class BHItem;
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

    // GameState* gameState;
    // vector<BHItem*>* items;
    
    virtual std::vector<FPOINT> GetSpawnPoints(int spawnAmount) = 0;
    virtual std::vector<IObjectActionPattern*> GetObjectActionPatterns(BHObject* target) = 0;
public:
    // virtual void Spawn() = 0;

    virtual void Update(float deltaTime) = 0;

    virtual void Init(float startTime, float endTime, string enemyShapeKey, int spawnAmount, float spawnDelay, float multiSpawnDelay);    

    virtual bool IsWaveDone(float currentTime);

    // void SetItemInfos(GameState* gameState,vector<BHItem*>* items) { this->gameState = gameState; this->items = items; }
};


// 여기에 웨이브 클래스 IStageWavePattern 상속해서 만드시오