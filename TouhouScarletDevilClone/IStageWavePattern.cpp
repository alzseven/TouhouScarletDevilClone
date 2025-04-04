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

//--- 

// std::vector<FPOINT> Stage1Wave1Pattern::GetSpawnPoints(int spawnAmount)
// {
//     std::vector<FPOINT> result = std::vector<FPOINT>();
//     result.push_back(initalPosLeft);
//     for (int i=1; i<spawnAmount; ++i)
//     {   
//         FPOINT newPos = { result.back().x, result.back().y };
//         newPos.x += marginBetweenSpawn.x;
//         newPos.y += marginBetweenSpawn.y;
//
//         result.push_back(newPos);
//     }
//     return result;
// }
//
// std::vector<IObjectActionPattern*> Stage1Wave1Pattern::GetObjectActionPatterns(BHObject* target)
// {
//     queue<IObjectActionPattern*> actionsQueue;
//     //TODO: Set as ShootPattern
//     IObjectActionPattern* patternNormal1ThrowKnifePattern1 = new Stage1BossNormalPattern1();
//     patternNormal1ThrowKnifePattern1->SetPatternStartTime(0.f);
//     patternNormal1ThrowKnifePattern1->SetPatternEndTime(99.f);
//     patternNormal1ThrowKnifePattern1->SetTarget(target);
//     patternNormal1ThrowKnifePattern1->SetShootParams(
//         "kunai",
//         1.f, 4, 2.f,
//         DEG_TO_RAD(0.f), DEG_TO_RAD(0.f),
//         50.f, -1.f); 
//     actionsQueue.push(patternNormal1ThrowKnifePattern1);
//     
//     IObjectActionPattern* patternNormal1MovePattern1 = new MoveStraightDirectionPattern();
//     patternNormal1MovePattern1->SetPatternStartTime(2.f);
//     patternNormal1MovePattern1->SetPatternEndTime(4.f);
//     patternNormal1MovePattern1->SetTarget(target);
//     patternNormal1MovePattern1->Launch(
//         50.f, 0.f,
//         DEG_TO_RAD((rand() % 360)), DEG_TO_RAD(0.f));
//     actionsQueue.push(patternNormal1MovePattern1);
//
//     //TODO: Set as MovePattern
//     IObjectActionPattern* patternNormal1MovePattern2 = new MoveStraightDirectionPattern();
//     patternNormal1MovePattern2->SetPatternStartTime(6.f);
//     patternNormal1MovePattern2->SetPatternEndTime(8.f);
//     patternNormal1MovePattern2->SetTarget(target);
//     patternNormal1MovePattern2->Launch(
//         50.f, 0.f,
//         DEG_TO_RAD((rand() % 360)), DEG_TO_RAD(0.f));
//     actionsQueue.push(patternNormal1MovePattern2);
//
//     //TODO: Set as MovePattern
//     IObjectActionPattern* patternNormal1MovePattern3 = new MoveStraightDirectionPattern();
//     patternNormal1MovePattern3->SetPatternStartTime(10.f);
//     patternNormal1MovePattern3->SetPatternEndTime(12.f);
//     patternNormal1MovePattern3->SetTarget(target);
//     patternNormal1MovePattern3->Launch(
//         50.f, 0.f,
//         DEG_TO_RAD((rand() % 360)), DEG_TO_RAD(0.f));
//     actionsQueue.push(patternNormal1MovePattern3);
//     
//     IObjectComplexPattern* patternNormal1 = new IObjectComplexPattern();
//     patternNormal1->SetPatternStartTime(0.0f);
//     patternNormal1->SetPatternEndTime(999.f);
//     patternNormal1->SetTarget(target);
//     patternNormal1->SetActions(actionsQueue);
//     
//     patternNormal1->Init();
//     
//     
//     std::vector<IObjectActionPattern*> result = std::vector<IObjectActionPattern*>();
//
//     result.push_back(patternNormal1);
//     return result;
//     
//     IObjectActionPattern** patterns = new IObjectActionPattern*[4];
//     
//     // patterns[0] = new ShootStraightPattern();
//     // patterns[0]->SetTarget(target);
//     // patterns[0]->SetPatternStartTime(0.f);
//     // patterns[0]->SetPatternEndTime(5.f);
//     // patterns[0]->SetShootParams(1.f, 5, 0.2f, DEG_TO_RAD(90.f), 0.f, 50.f, 0.f);
//     //
//     // patterns[1] = new ShootRoundPattern();
//     // patterns[1]->SetTarget(target);
//     // patterns[1]->SetPatternStartTime(6.f);
//     // patterns[1]->SetPatternEndTime(10.f);
//     // patterns[1]->SetShootParams(2.f, 5, 0.f, DEG_TO_RAD(-90.f), 0.f, 70.f, 0.f);
//
//     patterns[0] = new MoveStraightDirectionPattern();
//     patterns[0]->SetTarget(target);
//     patterns[0]->SetPatternStartTime(0.f);
//     patterns[0]->SetPatternEndTime(5.f);
//     patterns[0]->Launch(50.f,0.f,DEG_TO_RAD(-60.f),DEG_TO_RAD(0.f));
//
//     patterns[1] = new MoveStraightDirectionPattern();
//     patterns[1]->SetTarget(target);
//     patterns[1]->SetPatternStartTime(6.f);
//     patterns[1]->SetPatternEndTime(10.f);
//     patterns[1]->Launch(25.f,0.f,DEG_TO_RAD(60.f),DEG_TO_RAD(0.f));
//     
//     patterns[2] = new ShootSpreadPattern();
//     patterns[2]->SetTarget(target);
//     patterns[2]->SetPatternStartTime(6.f);
//     patterns[2]->SetPatternEndTime(12.f);
//     patterns[2]->SetShootParams(
//         "kunai",1.f, 10, 0.f, DEG_TO_RAD(135.f), DEG_TO_RAD(-5.f), 90.f, 0.f);
//
//     patterns[3] = new MoveStraightDirectionPattern();
//     patterns[3]->SetTarget(target);
//     patterns[3]->SetPatternStartTime(11.f);
//     patterns[3]->SetPatternEndTime(15.f);
//     patterns[3]->Launch(60.f,0.f,DEG_TO_RAD(-180.f),DEG_TO_RAD(0.f));
//
//     result.push_back(patterns[0]);
//     result.push_back(patterns[1]);
//     result.push_back(patterns[2]);
//     result.push_back(patterns[3]);
//     return result;
// }
//
// void Stage1Wave1Pattern::Update(float deltaTime)
// {
//     timeElpased += deltaTime;
//     if (spawnDelay <= timeElpased)
//     {
//         if (currentSpawnCount < spawnAmount)
//         {
//             //TODO : How should I initialize this?
//             BHEnemy* spawnedEnemy = BHObjectManager::GetInstance()->GetEnemyPool()->Allocate();
//
//             const std::vector<IObjectActionPattern*> p = GetObjectActionPatterns(spawnedEnemy);
//             spawnedEnemy->Init(enemyShapeKey,
//                 spawnPoints[currentSpawnCount], p);
//             spawnedEnemy->SetItemList(*items);
//             spawnedEnemy->SetGameState(gameState);
//             spawnedObjects.push_back(spawnedEnemy);
//             
//             timeElpased -= multiSpawnDelay;
//             currentSpawnCount++;
//         }
//         else
//         {
//             timeElpased -= spawnDelay;
//         }
//     }
// }
//
//
// void Stage1Wave1Pattern::Init(float startTime, float endTime, string enemyShapeKey,
//     int spawnAmount, float spawnDelay, float multiSpawnDelay)
// {
//     IStageWavePattern::Init(startTime, endTime,enemyShapeKey,spawnAmount, spawnDelay, multiSpawnDelay);
//     
//     this->currentSpawnCount = 0;
//     this->timeElpased = 0.f;
//
//     // add enemypositions
//     initalPosLeft = {GAME_CENTER_X, GAME_TOP + 100.f};
//     marginBetweenSpawn = { -50.f, 0};
//     spawnPoints = GetSpawnPoints(spawnAmount);
// }

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