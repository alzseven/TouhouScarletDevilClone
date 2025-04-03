#include "Stage1Wave3Pattern.h"
#include "BHEnemy.h"
#include "BHObjectManager.h"
#include "IObjectComplexPattern.h"
#include "ShootSpiralPattern.h"
#include "ShootTimeVaryingSpeedPattern.h"

std::vector<FPOINT> Stage1Wave3Pattern::GetSpawnPoints(int spawnAmount)
{
    std::vector<FPOINT> result = std::vector<FPOINT>();
    result.push_back(initialPosTop);
    for (int i=1; i<spawnAmount; ++i)
    {   
        FPOINT newPos = { result.back().x, result.back().y };
        newPos.x += marginBetweenSpawn.x;
        newPos.y += marginBetweenSpawn.y;

        result.push_back(newPos);
    }
    return result;
}

std::vector<IObjectActionPattern*> Stage1Wave3Pattern::GetObjectActionPatterns(BHObject* target)
{
    queue<IObjectActionPattern*> actionsQueue;
    
    // 나선형 탄막 패턴 (동방홍마향 스타일)
    ShootSpiralPattern* spiralPattern = new ShootSpiralPattern();
    spiralPattern->SetPatternStartTime(0.f);
    spiralPattern->SetPatternEndTime(5.f);
    spiralPattern->SetTarget(target);
    spiralPattern->SetShootParams(
        "NormalBullet_purple",
        0.2f, 30, 0.f,
        DEG_TO_RAD(0.f), DEG_TO_RAD(10.f),
        100.f, 0.f); 
    actionsQueue.push(spiralPattern);
    
    // 첫 번째 이동 패턴
    IObjectActionPattern* movePattern1 = new MoveStraightDirectionPattern();
    movePattern1->SetPatternStartTime(0.5f);
    movePattern1->SetPatternEndTime(2.5f);
    movePattern1->SetTarget(target);
    movePattern1->Launch(
        30.f, 0.f,
        DEG_TO_RAD(270.f), DEG_TO_RAD(0.f));
    actionsQueue.push(movePattern1);

    // 시간에 따라 속도가 변하는 탄막 패턴
    IObjectActionPattern* timeVaryingPattern = new ShootTimeVaryingSpeedPattern();
    timeVaryingPattern->SetPatternStartTime(5.5f);
    timeVaryingPattern->SetPatternEndTime(8.f);
    timeVaryingPattern->SetTarget(target);
    timeVaryingPattern->SetShootParams(
        "NormalBullet_yellow",
        0.3f, 12, 0.f,
        DEG_TO_RAD(0.f), DEG_TO_RAD(30.f),
        50.f, 5.f); 
    actionsQueue.push(timeVaryingPattern);
    
    // 두 번째 이동 패턴
    IObjectActionPattern* movePattern2 = new MoveStraightDirectionPattern();
    movePattern2->SetPatternStartTime(8.5f);
    movePattern2->SetPatternEndTime(10.f);
    movePattern2->SetTarget(target);
    movePattern2->Launch(
        40.f, 0.f,
        DEG_TO_RAD((rand() % 360)), DEG_TO_RAD(0.f));
    actionsQueue.push(movePattern2);
    
    // 원형 탄막 패턴 (동방홍마향 스타일)
    ShootRoundPattern* roundPattern = new ShootRoundPattern();
    roundPattern->SetPatternStartTime(10.5f);
    roundPattern->SetPatternEndTime(12.f);
    roundPattern->SetTarget(target);
    roundPattern->SetShootParams(
        "NormalBullet_red",
        0.2f, 24, 0.f,
        DEG_TO_RAD(0.f), DEG_TO_RAD(15.f),
        120.f, 0.f);
    actionsQueue.push(roundPattern);
    
    // 세 번째 이동 패턴
    IObjectActionPattern* movePattern3 = new MoveStraightDirectionPattern();
    movePattern3->SetPatternStartTime(12.5f);
    movePattern3->SetPatternEndTime(14.f);
    movePattern3->SetTarget(target);
    movePattern3->Launch(
        50.f, 0.f,
        DEG_TO_RAD((rand() % 360)), DEG_TO_RAD(0.f));
    actionsQueue.push(movePattern3);
    
    // 복합 패턴 생성
    IObjectComplexPattern* complexPattern = new IObjectComplexPattern();
    complexPattern->SetPatternStartTime(0.0f);
    complexPattern->SetPatternEndTime(999.f);
    complexPattern->SetTarget(target);
    complexPattern->SetActions(actionsQueue);
    
    complexPattern->Init();
    
    std::vector<IObjectActionPattern*> result = std::vector<IObjectActionPattern*>();
    result.push_back(complexPattern);
    return result;
}

void Stage1Wave3Pattern::Update(float deltaTime)
{
    timeElpased += deltaTime;
    if (spawnDelay <= timeElpased)
    {
        if (currentSpawnCount < spawnAmount)
        {
            BHEnemy* spawnedEnemy = BHObjectManager::GetInstance()->GetEnemyPool()->Allocate();

            const std::vector<IObjectActionPattern*> p = GetObjectActionPatterns(spawnedEnemy);
            spawnedEnemy->Init(enemyShapeKey,
                spawnPoints[currentSpawnCount], p);
            spawnedEnemy->SetItemList(*items);
            spawnedEnemy->SetGameState(gameState);
            spawnedObjects.push_back(spawnedEnemy);
            
            timeElpased -= multiSpawnDelay;
            currentSpawnCount++;
        }
        else
        {
            timeElpased -= spawnDelay;
        }
    }
}

void Stage1Wave3Pattern::Init(float startTime, float endTime, string enemyShapeKey,
    int spawnAmount, float spawnDelay, float multiSpawnDelay)
{
    IStageWavePattern::Init(startTime, endTime, enemyShapeKey, spawnAmount, spawnDelay, multiSpawnDelay);
    
    this->currentSpawnCount = 0;
    this->timeElpased = 0.f;

    // 위쪽에서 적 생성
    initialPosTop = {GAME_LEFT + 200.f, GAME_TOP + 50.f};
    marginBetweenSpawn = { 80.f, 0.f};
    spawnPoints = GetSpawnPoints(spawnAmount);
}
