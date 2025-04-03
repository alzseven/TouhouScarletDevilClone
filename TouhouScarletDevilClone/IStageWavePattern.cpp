#include "IStageWavePattern.h"
#include "PoolManager.h"

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
    bool isSpawnedAllDead = true;
    for (std::vector<BHObject*>::iterator iter = spawnedObjects.begin(); iter != spawnedObjects.end(); ++iter)
    {
        if ((*iter)->IsValid())
        {
            isSpawnedAllDead = false;
        }
    }
    return currentTime >= patternEndTime || isSpawnedAllDead;
}

std::vector<FPOINT> State1Wave1Pattern::GetSpawnPoints(int spawnAmount)
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

std::vector<IObjectActionPattern*> State1Wave1Pattern::GetObjectActionPatterns(BHObject* target)
{
    std::vector<IObjectActionPattern*> result = std::vector<IObjectActionPattern*>();

    IObjectActionPattern** patterns = new IObjectActionPattern*[4];
    
    // patterns[0] = new ShootStraightPattern();
    // patterns[0]->SetTarget(target);
    // patterns[0]->SetPatternStartTime(0.f);
    // patterns[0]->SetPatternEndTime(5.f);
    // patterns[0]->SetShootParams(1.f, 5, 0.2f, DEG_TO_RAD(90.f), 0.f, 50.f, 0.f);
    //
    // patterns[1] = new ShootRoundPattern();
    // patterns[1]->SetTarget(target);
    // patterns[1]->SetPatternStartTime(6.f);
    // patterns[1]->SetPatternEndTime(10.f);
    // patterns[1]->SetShootParams(2.f, 5, 0.f, DEG_TO_RAD(-90.f), 0.f, 70.f, 0.f);

    patterns[0] = new MoveStraightDirectionPattern();
    patterns[0]->SetTarget(target);
    patterns[0]->SetPatternStartTime(0.f);
    patterns[0]->SetPatternEndTime(5.f);
    patterns[0]->Launch(50.f,0.f,DEG_TO_RAD(-60.f),DEG_TO_RAD(0.f));

    patterns[1] = new MoveStraightDirectionPattern();
    patterns[1]->SetTarget(target);
    patterns[1]->SetPatternStartTime(6.f);
    patterns[1]->SetPatternEndTime(10.f);
    patterns[1]->Launch(25.f,0.f,DEG_TO_RAD(60.f),DEG_TO_RAD(0.f));
    
    patterns[2] = new ShootSpreadPattern();
    patterns[2]->SetTarget(target);
    patterns[2]->SetPatternStartTime(6.f);
    patterns[2]->SetPatternEndTime(12.f);
    patterns[2]->SetShootParams(1.f, 10, 0.f, DEG_TO_RAD(135.f), DEG_TO_RAD(-5.f), 90.f, 0.f);

    patterns[3] = new MoveStraightDirectionPattern();
    patterns[3]->SetTarget(target);
    patterns[3]->SetPatternStartTime(11.f);
    patterns[3]->SetPatternEndTime(15.f);
    patterns[3]->Launch(60.f,0.f,DEG_TO_RAD(-180.f),DEG_TO_RAD(0.f));

    result.push_back(patterns[0]);
    result.push_back(patterns[1]);
    result.push_back(patterns[2]);
    result.push_back(patterns[3]);
    return result;
}

void State1Wave1Pattern::Update(float deltaTime)
{
    timeElpased += deltaTime;
    if (spawnDelay <= timeElpased)
    {
        if (currentSpawnCount < spawnAmount)
        {
            //TODO : How should I initialize this?
            BHEnemy* spawnedEnemy = PoolManager::GetInstance()->GetEnemyPool()->Allocate();

            const std::vector<IObjectActionPattern*> p = GetObjectActionPatterns(spawnedEnemy);
            spawnedEnemy->Init(enemyShapeKey,
                spawnPoints[currentSpawnCount], p);

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


void State1Wave1Pattern::Init(float startTime, float endTime, string enemyShapeKey,
    int spawnAmount, float spawnDelay, float multiSpawnDelay)
{
    IStageWavePattern::Init(startTime, endTime,enemyShapeKey,spawnAmount, spawnDelay, multiSpawnDelay);
    
    this->currentSpawnCount = 0;
    this->timeElpased = 0.f;

    // add enemypositions
    initalPosLeft = {GAME_RIGHT - 15.f, GAME_TOP - 100.f};
    marginBetweenSpawn = { -50.f, 0};
    spawnPoints = GetSpawnPoints(spawnAmount);
}
