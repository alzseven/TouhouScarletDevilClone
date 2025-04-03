#include "Stage1Boss.h"
#include "BHEnemy.h"
#include "BHObjectManager.h"
#include "IObjectComplexPattern.h"
#include "SoundPlayer.h"

std::vector<FPOINT> Stage1Boss::GetSpawnPoints(int spawnAmount)
{
    std::vector<FPOINT> spawnPoints;
    // 보스는 화면 중앙 상단에 생성
    bossPosition = {GAME_CENTER_X, GAME_TOP + 150.f};
    spawnPoints.push_back(bossPosition);
    return spawnPoints;
}

std::vector<IObjectActionPattern*> Stage1Boss::GetObjectActionPatterns(BHObject* target)
{
    std::vector<IObjectActionPattern*> patterns;
    
    // 보스 입장 패턴 - 위에서 아래로 이동
    IObjectActionPattern* entrancePattern = new MoveStraightDirectionPattern();
    entrancePattern->SetPatternStartTime(0.f);
    entrancePattern->SetPatternEndTime(3.f);
    entrancePattern->SetTarget(target);
    entrancePattern->Launch(50.f, 0.f, DEG_TO_RAD(90.f), DEG_TO_RAD(0.f));
    
    // 첫 번째 공격 패턴 - 원형 탄막
    IObjectActionPattern* attackPattern1 = new ShootRoundPattern();
    attackPattern1->SetPatternStartTime(4.f);
    attackPattern1->SetPatternEndTime(10.f);
    attackPattern1->SetTarget(target);
    attackPattern1->SetShootParams(
        "kunai",
        2.0f, 16, 0.1f,
        DEG_TO_RAD(0.f), DEG_TO_RAD(5.f),
        100.f, 0.f);
    
    // 두 번째 이동 패턴 - 좌우 이동
    IObjectActionPattern* movePattern = new MoveStraightDirectionPattern();
    movePattern->SetPatternStartTime(11.f);
    movePattern->SetPatternEndTime(13.f);
    movePattern->SetTarget(target);
    movePattern->Launch(70.f, 0.f, DEG_TO_RAD(0.f), DEG_TO_RAD(0.f));
    
    // 두 번째 공격 패턴 - 확산 탄막
    IObjectActionPattern* attackPattern2 = new ShootSpreadPattern();
    attackPattern2->SetPatternStartTime(14.f);
    attackPattern2->SetPatternEndTime(20.f);
    attackPattern2->SetTarget(target);
    attackPattern2->SetShootParams(
        "EllipseBullet_green",
        1.5f, 8, 0.2f,
        DEG_TO_RAD(90.f), DEG_TO_RAD(-10.f),
        120.f, -2.f);
    
    // 세 번째 이동 패턴 - 원형 이동
    IObjectActionPattern* movePattern2 = new MoveStraightDirectionPattern();
    movePattern2->SetPatternStartTime(21.f);
    movePattern2->SetPatternEndTime(23.f);
    movePattern2->SetTarget(target);
    movePattern2->Launch(60.f, 0.f, DEG_TO_RAD(180.f), DEG_TO_RAD(0.f));
    
    // 세 번째 공격 패턴 - 복합 탄막
    IObjectActionPattern* attackPattern3 = new Stage1BossNormalPattern1();
    attackPattern3->SetPatternStartTime(24.f);
    attackPattern3->SetPatternEndTime(30.f);
    attackPattern3->SetTarget(target);
    attackPattern3->SetShootParams(
        "Jewel_blue",
        3.0f, 5, 0.5f,
        DEG_TO_RAD(0.f), DEG_TO_RAD(0.f),
        80.f, 0.f);
    
    // 패턴들을 복합 패턴으로 묶기
    IObjectComplexPattern* complexPattern = new IObjectComplexPattern();
    complexPattern->SetPatternStartTime(0.0f);
    complexPattern->SetPatternEndTime(999.f);
    complexPattern->SetTarget(target);
    
    queue<IObjectActionPattern*> actionsQueue;
    actionsQueue.push(entrancePattern);
    actionsQueue.push(attackPattern1);
    actionsQueue.push(movePattern);
    actionsQueue.push(attackPattern2);
    actionsQueue.push(movePattern2);
    actionsQueue.push(attackPattern3);
    
    complexPattern->SetActions(actionsQueue);
    complexPattern->Init();
    
    patterns.push_back(complexPattern);
    return patterns;
}

void Stage1Boss::Update(float deltaTime)
{
    timeElpased += deltaTime;
    
    if (!isBossSpawned)
    {
        bossSpawnTimer += deltaTime;
        
        if (bossSpawnTimer >= bossSpawnDelay)
        {
            // 보스 생성
            boss = BHObjectManager::GetInstance()->GetBossPool()->Allocate();
            const std::vector<IObjectActionPattern*> patterns = GetObjectActionPatterns(boss);
            
            boss->Init(enemyShapeKey, spawnPoints[0], patterns);
            boss->SetItemList(*items);
            boss->SetGameState(gameState);
            
            // 보스 체력 설정 (일반 적보다 높게)
            // 여기서는 GetDamaged 메서드가 호출될 때마다 체력이 1씩 감소하므로
            // 보스의 체력을 높이기 위해 추가 로직이 필요할 수 있음
            
            spawnedObjects.push_back(boss);
            isBossSpawned = true;
            
            // 보스 등장 효과음 재생
            // SoundPlayer::GetInstance()->SoundOn("boss_appear");
        }
    }
    
    // 보스가 죽었는지 확인
    if (isBossSpawned && !boss->IsValid())
    {
        // 보스 처치 효과음 재생
        // SoundPlayer::GetInstance()->SoundOn("boss_defeat");
    }
}

void Stage1Boss::Init(float startTime, float endTime, string enemyShapeKey, int spawnAmount, float spawnDelay, float multiSpawnDelay)
{
    IStageWavePattern::Init(startTime, endTime, enemyShapeKey, 1, spawnDelay, multiSpawnDelay);
    
    this->timeElpased = 0.f;
    this->bossSpawnTimer = 0.f;
    this->isBossSpawned = false;
    
    // 보스 생성 위치 설정
    spawnPoints = GetSpawnPoints(1);
}
