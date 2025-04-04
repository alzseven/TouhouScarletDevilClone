#include "Stage1Wave1Pattern.h"

#include "BHEnemy.h"
#include "BHObjectManager.h"
#include "IObjectComplexPattern.h"

std::vector<FPOINT> Stage1Wave1Pattern::GetSpawnPoints(int spawnAmount)
{
    std::vector<FPOINT> result = std::vector<FPOINT>();
    result.push_back(initalPosLeft);
    for (int i=1; i<spawnAmount; ++i)
    {   
        FPOINT newPos = { result.back().x, result.back().y };
        newPos.x += marginBetweenSpawn.x;
        newPos.y += marginBetweenSpawn.y;

        result.push_back(newPos);
    }
    return result;
}

std::vector<IObjectActionPattern*> Stage1Wave1Pattern::GetObjectActionPatterns(BHObject* target)
{
    queue<IObjectActionPattern*> actionsQueue;
    
    // 직선 탄막 패턴 (플레이어 방향으로 발사)
    IObjectActionPattern* straightPattern = new ShootStraightPattern();
    straightPattern->SetPatternStartTime(0.f);
    straightPattern->SetPatternEndTime(6.f);
    straightPattern->SetTarget(target);
    straightPattern->SetShootParams(
        "NormalBullet_red",
        1.5f, 3, 0.1f,
        DEG_TO_RAD(90.f), DEG_TO_RAD(0.f),
        120.f, 0.f); 
    actionsQueue.push(straightPattern);
    
    // 첫 번째 이동 패턴
    IObjectActionPattern* movePattern1 = new MoveStraightDirectionPattern();
    movePattern1->SetPatternStartTime(0.5f);
    movePattern1->SetPatternEndTime(2.5f);
    movePattern1->SetTarget(target);
    movePattern1->Launch(
        40.f, 0.f,
        DEG_TO_RAD((rand() % 180)), DEG_TO_RAD(0.f));
    actionsQueue.push(movePattern1);

    // 두 번째 이동 패턴
    IObjectActionPattern* movePattern2 = new MoveStraightDirectionPattern();
    movePattern2->SetPatternStartTime(4.f);
    movePattern2->SetPatternEndTime(6.f);
    movePattern2->SetTarget(target);
    movePattern2->Launch(
        50.f, 0.f,
        DEG_TO_RAD((rand() % 180)), DEG_TO_RAD(0.f));
    actionsQueue.push(movePattern2);
    
    // 확산 탄막 패턴
    IObjectActionPattern* spreadPattern = new ShootSpreadPattern();
    spreadPattern->SetPatternStartTime(7.f);
    spreadPattern->SetPatternEndTime(9.f);
    spreadPattern->SetTarget(target);
    spreadPattern->SetShootParams(
        "NormalBullet_blue",
        0.5f, 5, 0.1f,
        DEG_TO_RAD(60.f), DEG_TO_RAD(15.f),
        100.f, 0.f); 
    actionsQueue.push(spreadPattern);
    
    // 세 번째 이동 패턴
    IObjectActionPattern* movePattern3 = new MoveStraightDirectionPattern();
    movePattern3->SetPatternStartTime(9.f);
    movePattern3->SetPatternEndTime(11.f);
    movePattern3->SetTarget(target);
    movePattern3->Launch(
        60.f, 0.f,
        DEG_TO_RAD((rand() % 180)), DEG_TO_RAD(0.f));
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

void Stage1Wave1Pattern::Update(float deltaTime)
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
            spawnedEnemy->SetItemList(*BHObjectManager::GetInstance()->GetItems());
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

void Stage1Wave1Pattern::Init(float startTime, float endTime, string enemyShapeKey,
    int spawnAmount, float spawnDelay, float multiSpawnDelay)
{
    IStageWavePattern::Init(startTime, endTime, enemyShapeKey, spawnAmount, spawnDelay, multiSpawnDelay);
    
    this->currentSpawnCount = 0;
    this->timeElpased = 0.f;

    // 왼쪽에서 적 생성
    initalPosLeft = {GAME_LEFT + 100.f, GAME_TOP + 100.f};
    marginBetweenSpawn = { 0.f, 50.f};
    spawnPoints = GetSpawnPoints(spawnAmount);
}
