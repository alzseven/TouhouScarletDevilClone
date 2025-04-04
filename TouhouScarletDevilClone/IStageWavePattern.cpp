#include "IStageWavePattern.h"

#include "IObjectComplexPattern.h"
#include "BHObjectManager.h"

void IStageWavePattern::Init(float startTime, float endTime, string enemyShapeKey, int spawnAmount, float spawnDelay,
                             float multiSpawnDelay)
{
    this->patternStartTime = startTime;
    this->patternEndTime = endTime;
    this->enemyShapeKey = enemyShapeKey;
    this->spawnAmount = spawnAmount;
    this->spawnDelay = spawnDelay;
    this->multiSpawnDelay = multiSpawnDelay;
}

bool IStageWavePattern::IsWaveDone(float currentTime)
{
    // bool isSpawnedAllDead = true;
    // for (std::vector<BHObject*>::iterator iter = spawnedObjects.begin(); iter != spawnedObjects.end(); ++iter)
    // {
    //     if ((*iter)->IsValid())
    //     {
    //         isSpawnedAllDead = false;
    //     }
    // }
    return currentTime >= patternEndTime;// || isSpawnedAllDead;
}

void IStageWavePattern::SetItemInfos(GameState* gameState, vector<BHItem*>* items)
{
    this->gameState = gameState;
    this->items = items;
}

//--- 

// 1_boss

// std::vector<FPOINT> Stage1Boss::GetSpawnPoints(int spawnAmount)
// {
//     return std::vector<FPOINT>();
// }
//
// std::vector<IObjectActionPattern*> Stage1Boss::GetObjectActionPatterns(BHObject* target)
// {
//     return std::vector<IObjectActionPattern*>();
// }
//
// void Stage1Boss::Update(float deltaTime)
// {
// }
//
// void Stage1Boss::Init(float startTime, float endTime, string enemyShapeKey, int spawnAmount, float spawnDelay,
//     float multiSpawnDelay)
// {
//     // BHBoss* spawnedBoss = PoolManager::GetInstance()->GetBossPool()->Allocate();
//     //
//     // //
//     // spawnedBoss->Init("BOSS",pos);
//
// }
//

// 여기에 웨이브 클래스 IStageWavePattern 상속해서 만드시오

// 이 함수를 통해 enemy가 생성될 위치 정보를 담는 vector를 생성하시오.
// std::vector<FPOINT> ::GetSpawnPoints(int spawnAmount)
// {
//     
// }

// 이 함수에 IObjectActionPattern을 상속 받는 객체를 담는 vector를 생성해서 반환하시오
// std::vector<IObjectActionPattern*> ::GetObjectActionPatterns(BHObject* target)
// {
//     
// }

// 이 함수에서 세부적인 생성 방식을 정하시오. 귀찮으면 복붙
// void ::Update(float deltaTime)
// {
// }

// 여기에서 초기설정 하시오
// void ::Init(float startTime, float endTime, string enemyShapeKey,
//     int spawnAmount, float spawnDelay, float multiSpawnDelay)
// {
// }



