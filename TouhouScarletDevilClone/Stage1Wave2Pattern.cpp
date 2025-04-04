#include "Stage1Wave2Pattern.h"
#include "BHEnemy.h"
#include "BHObjectManager.h"
#include "GameStateManager.h"
#include "IObjectComplexPattern.h"

std::vector<FPOINT> Stage1Wave2Pattern::GetSpawnPoints(int spawnAmount)
{
    std::vector<FPOINT> result = std::vector<FPOINT>();
    result.push_back(initialPosRight);
    for (int i=1; i<spawnAmount; ++i)
    {   
        FPOINT newPos = { result.back().x, result.back().y };
        newPos.x += marginBetweenSpawn.x;
        newPos.y += marginBetweenSpawn.y;

        result.push_back(newPos);
    }
    return result;
}

std::vector<IObjectActionPattern*> Stage1Wave2Pattern::GetObjectActionPatterns(BHObject* target)
{
    queue<IObjectActionPattern*> actionsQueue;
    
    // 원형 탄막 패턴
    IObjectActionPattern* roundPattern = new ShootRoundPattern();
    roundPattern->SetPatternStartTime(0.f);
    roundPattern->SetPatternEndTime(8.f);
    roundPattern->SetTarget(target);
    roundPattern->SetShootParams(
        "EllipseBullet_green",
        2.0f, 8, 0.2f,
        DEG_TO_RAD(0.f), DEG_TO_RAD(3.f),
        80.f, 0.f); 
    actionsQueue.push(roundPattern);
    
    // 첫 번째 이동 패턴
    IObjectActionPattern* movePattern1 = new MoveStraightDirectionPattern();
    movePattern1->SetPatternStartTime(1.f);
    movePattern1->SetPatternEndTime(3.f);
    movePattern1->SetTarget(target);
    movePattern1->Launch(
        60.f, 0.f,
        DEG_TO_RAD((rand() % 180) + 90), DEG_TO_RAD(0.f));
    actionsQueue.push(movePattern1);

    // 두 번째 이동 패턴
    IObjectActionPattern* movePattern2 = new MoveStraightDirectionPattern();
    movePattern2->SetPatternStartTime(5.f);
    movePattern2->SetPatternEndTime(7.f);
    movePattern2->SetTarget(target);
    movePattern2->Launch(
        70.f, 0.f,
        DEG_TO_RAD((rand() % 180) + 90), DEG_TO_RAD(0.f));
    actionsQueue.push(movePattern2);

    // 세 번째 이동 패턴
    IObjectActionPattern* movePattern3 = new MoveStraightDirectionPattern();
    movePattern3->SetPatternStartTime(9.f);
    movePattern3->SetPatternEndTime(11.f);
    movePattern3->SetTarget(target);
    movePattern3->Launch(
        80.f, 0.f,
        DEG_TO_RAD((rand() % 180) + 90), DEG_TO_RAD(0.f));
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

void Stage1Wave2Pattern::Update(float deltaTime)
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
            spawnedEnemy->SetItemList(BHObjectManager::GetInstance()->GetItemPool()->GetActive());
            spawnedEnemy->SetGameState(GameStateManager::GetInstance()->GetGameState());
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

void Stage1Wave2Pattern::Init(float startTime, float endTime, string enemyShapeKey,
    int spawnAmount, float spawnDelay, float multiSpawnDelay)
{
    IStageWavePattern::Init(startTime, endTime, enemyShapeKey, spawnAmount, spawnDelay, multiSpawnDelay);
    
    this->currentSpawnCount = 0;
    this->timeElpased = 0.f;

    // 오른쪽에서 적 생성
    initialPosRight = {GAME_RIGHT - 100.f, GAME_TOP + 100.f};
    marginBetweenSpawn = { 0.f, 50.f};
    spawnPoints = GetSpawnPoints(spawnAmount);
}