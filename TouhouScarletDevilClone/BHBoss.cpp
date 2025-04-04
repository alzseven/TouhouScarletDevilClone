#include "BHBoss.h"
#include "EnemyController.h"
#include "IObjectComplexPattern.h"
#include "ShapeManager.h"
#include "SoundPlayer.h"
#include "EffectPlayer.h"
#include "GameState.h"
#include "BHObjectManager.h"

void BHBoss::Init(string shapeKey, FPOINT pos)
{
    BHEnemy::Init(shapeKey, pos);
    
    // 보스 초기화
    health = 1000;
    phase = 0;
    phaseTimer = 0.0f;
    isPhaseChanging = false;

    GameState* gameState = GameStateManager::GetInstance()->GetGameState();
    if (gameState) {

        gameState->BossHp = health;
        gameState->BossMaxHp = health;
    }
    // 컨트롤러 초기화
    ec = new EnemyController();
    ec->SetTarget(this);
    
    // 초기 패턴 설정
    SetupNormalPattern();
    
   
}

void BHBoss::Init(string shapeKey, FPOINT pos, std::vector<IObjectActionPattern*> patterns)
{
    BHBoss::Init(shapeKey, pos);

    for (std::vector<IObjectActionPattern*>::iterator it = patterns.begin(); it != patterns.end(); ++it)
    {
        ec->SetActionPatterns((*it));
    }
}

void BHBoss::Update(float dt)
{
    if (isAlive == false) return;
    
    // 페이즈 전환 중이면 타이머 업데이트
    if (isPhaseChanging) {
        phaseTimer += dt;
        if (phaseTimer >= 2.0f) { // 2초 후 페이즈 전환 완료
            isPhaseChanging = false;
            phaseTimer = 0.0f;
            
            // 새 페이즈에 맞는 패턴 설정
            switch (phase) {
                case 1:
                    SetupSpellCard1();
                    break;
                case 2:
                    SetupSpellCard2();
                    break;
                case 3:
                    SetupSpellCard3();
                    break;
                default:
                    SetupNormalPattern();
                    break;
            }
        }
        return;
    }
    
    // 일반 업데이트
    ec->Update(dt);
    
    // 게임 상태 업데이트
    GameState* gameState = GameStateManager::GetInstance()->GetGameState();
    if (gameState) {
        gameState->BossHp = health;
    }
}

void BHBoss::GetDamaged(int damage)
{
    
    // 페이즈 전환 중에는 데미지를 받지 않음
    // if (isPhaseChanging) return;
    
    health -= damage * 3;
    
    // 게임 상태 업데이트
    GameState* gameState = GameStateManager::GetInstance()->GetGameState();
    if (gameState) {
        gameState->BossHp = health;
    }
    
    if (health <= 0) {
        // 보스 처치 처리
        isAlive = false;
        gameState->isGameClear = true;
         //보스 처치 효과음 재생
         SoundPlayer::GetInstance()->SoundOn("boss_dead");
        
         //보스 처치 이펙트 재생
         EffectPlayer::GetInstance()->PlayEffect("Boss_phase", position);
         
        // 아이템 드롭
        for (int i = 0; i < 10; i++) {
            float angle = DEG_TO_RAD(i * 36);
            FPOINT dropPos = { position.x + sin(angle) * 30, position.y + cos(angle) * 30 };
            // BHObjectManager::GetInstance()->CreateItem("smallPower", dropPos);
        }
    }
    else if (phase == 2 && health <= SPELL3_THRESHOLD) {
        ChangePhase(3);
    }
    else if (phase == 1 && health <= SPELL2_THRESHOLD) {
        ChangePhase(2);
    }
    else if (phase == 0 && health <= SPELL1_THRESHOLD) {
        ChangePhase(1);
    }
}

void BHBoss::ChangePhase(int newPhase)
{
    // 페이즈 전환 시작
    phase = newPhase;
    isPhaseChanging = true;
    phaseTimer = 0.0f;
    
    // 화면의 모든 탄막 제거
    BHObjectManager::GetInstance()->ClearEnemyBullets();
    
    // 페이즈 전환 효과음 재생
    // SoundPlayer::GetInstance()->SoundOn("spell_card_declare");
    
    // 페이즈 전환 이펙트 재생
    // EffectPlayer::GetInstance()->PlayEffect("spell_card_effect", position);
}

void BHBoss::SetupNormalPattern()
{
    queue<IObjectActionPattern*> actions;
    
    // 나이프 발사 패턴
    IObjectActionPattern* patternNormal1ThrowKnifePattern1 = new ShootSpreadPattern();
    patternNormal1ThrowKnifePattern1->SetPatternStartTime(0.f);
    patternNormal1ThrowKnifePattern1->SetPatternEndTime(6.f);
    patternNormal1ThrowKnifePattern1->SetTarget(this);
    patternNormal1ThrowKnifePattern1->SetShootParams(
        "kunai",
        2.f, 18, 0.f,
        DEG_TO_RAD(0.f), DEG_TO_RAD(20.f),
        150.f, -1.f); 
    actions.push(patternNormal1ThrowKnifePattern1);
    
    // 이동 패턴
    IObjectActionPattern* patternNormal1MovePattern1 = new MoveStraightDirectionPattern();
    patternNormal1MovePattern1->SetPatternStartTime(0.f);
    patternNormal1MovePattern1->SetPatternEndTime(2.f);
    patternNormal1MovePattern1->SetTarget(this);
    patternNormal1MovePattern1->Launch(
        50.f, 0.f,
        DEG_TO_RAD((rand() % 360)), DEG_TO_RAD(0.f));
    actions.push(patternNormal1MovePattern1);
    
    // 원형 발사 패턴
    ShootRoundPattern* patternNormal1RoundPattern = new ShootRoundPattern();
    patternNormal1RoundPattern->SetPatternStartTime(6.f);
    patternNormal1RoundPattern->SetPatternEndTime(8.f);
    patternNormal1RoundPattern->SetTarget(this);
    patternNormal1RoundPattern->SetShootParams(
        "NormalBullet_red",
        0.2f, 36, 0.f,
        DEG_TO_RAD(0.f), DEG_TO_RAD(10.f),
        200.f, 0.f);
    actions.push(patternNormal1RoundPattern);
    
    // 이동 패턴 2
    IObjectActionPattern* patternNormal1MovePattern2 = new MoveStraightDirectionPattern();
    patternNormal1MovePattern2->SetPatternStartTime(8.f);
    patternNormal1MovePattern2->SetPatternEndTime(10.f);
    patternNormal1MovePattern2->SetTarget(this);
    patternNormal1MovePattern2->Launch(
        50.f, 0.f,
        DEG_TO_RAD((rand() % 360)), DEG_TO_RAD(0.f));
    actions.push(patternNormal1MovePattern2);
    
    // 복합 패턴 설정
    IObjectComplexPattern* patternNormal1 = new IObjectComplexPattern();
    patternNormal1->SetPatternStartTime(0.0f);
    patternNormal1->SetPatternEndTime(999.f);
    patternNormal1->SetTarget(this);
    patternNormal1->SetActions(actions);
    
    ec->SetActionPatterns(patternNormal1);
}

void BHBoss::SetupSpellCard1()
{
    // 시간 정지 + 나이프 패턴 (사쿠야의 "Private Square" 스펠카드 모방)
    queue<IObjectActionPattern*> actions;
    
    // 중앙으로 이동
    IObjectActionPattern* moveToCenter = new MoveStraightDirectionPattern();
    moveToCenter->SetPatternStartTime(0.f);
    moveToCenter->SetPatternEndTime(1.f);
    moveToCenter->SetTarget(this);
    moveToCenter->Launch(
        100.f, 0.f,
        DEG_TO_RAD(270.f), DEG_TO_RAD(0.f)); // 중앙으로 이동
    actions.push(moveToCenter);
    
    // 시간 정지 효과 (실제로는 탄막 속도 감소로 구현)
    for (int i = 0; i < 4; i++) {
        // 원형 나이프 발사
        ShootRoundPattern* knifeRound = new ShootRoundPattern();
        knifeRound->SetPatternStartTime(1.f + i * 1.5f);
        knifeRound->SetPatternEndTime(1.5f + i * 1.5f);
        knifeRound->SetTarget(this);
        knifeRound->SetShootParams(
            "kunai",
            0.1f, 24, 0.f,
            DEG_TO_RAD(0.f), DEG_TO_RAD(15.f),
            50.f, 0.f); // 느린 속도로 발사
        actions.push(knifeRound);
        
        // 잠시 대기
        IObjectActionPattern* waitPattern = new IObjectActionPattern();
        waitPattern->SetPatternStartTime(1.5f + i * 1.5f);
        waitPattern->SetPatternEndTime(2.0f + i * 1.5f);
        waitPattern->SetTarget(this);
        actions.push(waitPattern);
        
        // 방향성 나이프 발사
        ShootSpreadPattern* knifeSpread = new ShootSpreadPattern();
        knifeSpread->SetPatternStartTime(2.0f + i * 1.5f);
        knifeSpread->SetPatternEndTime(2.5f + i * 1.5f);
        knifeSpread->SetTarget(this);
        knifeSpread->SetShootParams(
            "kunai",
            0.1f, 8, 0.f,
            DEG_TO_RAD(-60.f + i * 30.f), DEG_TO_RAD(15.f),
            100.f, 0.f);
        actions.push(knifeSpread);
    }
    
    // 복합 패턴 설정
    IObjectComplexPattern* spellCard1 = new IObjectComplexPattern();
    spellCard1->SetPatternStartTime(0.0f);
    spellCard1->SetPatternEndTime(999.f);
    spellCard1->SetTarget(this);
    spellCard1->SetActions(actions);
    
    ec->SetActionPatterns(spellCard1);
    
    // 스펠카드 선언 효과음 재생
    // SoundPlayer::GetInstance()->SoundOn("spell_card_declare");
    
    // 스펠카드 이펙트 재생
    // EffectPlayer::GetInstance()->PlayEffect("spell_card_effect", position);
}

void BHBoss::SetupSpellCard2()
{
    // 환영 나이프 패턴 (사쿠야의 "Killing Doll" 스펠카드 모방)
    queue<IObjectActionPattern*> actions;
    
    // 중앙으로 이동
    IObjectActionPattern* moveToCenter = new MoveStraightDirectionPattern();
    moveToCenter->SetPatternStartTime(0.f);
    moveToCenter->SetPatternEndTime(1.f);
    moveToCenter->SetTarget(this);
    moveToCenter->Launch(
        100.f, 0.f,
        DEG_TO_RAD(270.f), DEG_TO_RAD(0.f)); // 중앙으로 이동
    actions.push(moveToCenter);
    
    // 환영 나이프 패턴 (여러 방향에서 나이프 발사)
    for (int i = 0; i < 5; i++) {
        // 다양한 위치에서 나이프 발사
        for (int j = 0; j < 4; j++) {
            ShootSpreadPattern* knifeSpread = new ShootSpreadPattern();
            knifeSpread->SetPatternStartTime(1.f + i * 2.0f);
            knifeSpread->SetPatternEndTime(1.5f + i * 2.0f);
            knifeSpread->SetTarget(this);
            knifeSpread->SetShootParams(
                "kunai",
                0.05f, 5, 0.f,
                DEG_TO_RAD(j * 90.f + i * 15.f), DEG_TO_RAD(10.f),
                200.f, 0.f);
            actions.push(knifeSpread);
        }
        
        // 원형 발사 패턴
        ShootRoundPattern* roundPattern = new ShootRoundPattern();
        roundPattern->SetPatternStartTime(2.0f + i * 2.0f);
        roundPattern->SetPatternEndTime(2.5f + i * 2.0f);
        roundPattern->SetTarget(this);
        roundPattern->SetShootParams(
            "NormalBullet_red",
            0.1f, 24, 0.f,
            DEG_TO_RAD(0.f), DEG_TO_RAD(15.f),
            150.f, 0.f);
        actions.push(roundPattern);
        
        // 랜덤 이동
        IObjectActionPattern* randomMove = new MoveStraightDirectionPattern();
        randomMove->SetPatternStartTime(2.5f + i * 2.0f);
        randomMove->SetPatternEndTime(3.0f + i * 2.0f);
        randomMove->SetTarget(this);
        randomMove->Launch(
            80.f, 0.f,
            DEG_TO_RAD((rand() % 360)), DEG_TO_RAD(0.f));
        actions.push(randomMove);
    }
    
    // 복합 패턴 설정
    IObjectComplexPattern* spellCard2 = new IObjectComplexPattern();
    spellCard2->SetPatternStartTime(0.0f);
    spellCard2->SetPatternEndTime(999.f);
    spellCard2->SetTarget(this);
    spellCard2->SetActions(actions);
    
    ec->SetActionPatterns(spellCard2);
    
    // 스펠카드 선언 효과음 재생
    // SoundPlayer::GetInstance()->SoundOn("spell_card_declare");
    
    // 스펠카드 이펙트 재생
    // EffectPlayer::GetInstance()->PlayEffect("spell_card_effect", position);
}

void BHBoss::SetupSpellCard3()
{
    // 일루전 다이얼 패턴 (사쿠야의 "Illusion Dial" 스펠카드 모방)
    queue<IObjectActionPattern*> actions;
    
    // 중앙으로 이동
    IObjectActionPattern* moveToCenter = new MoveStraightDirectionPattern();
    moveToCenter->SetPatternStartTime(0.f);
    moveToCenter->SetPatternEndTime(1.f);
    moveToCenter->SetTarget(this);
    moveToCenter->Launch(
        100.f, 0.f,
        DEG_TO_RAD(270.f), DEG_TO_RAD(0.f)); // 중앙으로 이동
    actions.push(moveToCenter);
    
    // 시계 바늘 패턴 (12개의 방향에서 탄막 발사)
    for (int i = 0; i < 6; i++) {
        // 시계 바늘 형태로 탄막 발사
        for (int j = 0; j < 12; j++) {
            ShootSpreadPattern* clockHand = new ShootSpreadPattern();
            clockHand->SetPatternStartTime(1.f + i * 2.0f);
            clockHand->SetPatternEndTime(1.5f + i * 2.0f);
            clockHand->SetTarget(this);
            clockHand->SetShootParams(
                "NormalBullet_blue",
                0.05f, 8, 0.f,
                DEG_TO_RAD(j * 30.f), DEG_TO_RAD(5.f),
                180.f + i * 20.f, 0.f);
            actions.push(clockHand);
        }
        
        // 원형 나이프 발사
        ShootRoundPattern* knifeRound = new ShootRoundPattern();
        knifeRound->SetPatternStartTime(2.0f + i * 2.0f);
        knifeRound->SetPatternEndTime(2.5f + i * 2.0f);
        knifeRound->SetTarget(this);
        knifeRound->SetShootParams(
            "kunai",
            0.1f, 16, 0.f,
            DEG_TO_RAD(i * 15.f), DEG_TO_RAD(22.5f),
            220.f, 0.f);
        actions.push(knifeRound);
        
        // 랜덤 이동
        IObjectActionPattern* randomMove = new MoveStraightDirectionPattern();
        randomMove->SetPatternStartTime(2.5f + i * 2.0f);
        randomMove->SetPatternEndTime(3.0f + i * 2.0f);
        randomMove->SetTarget(this);
        randomMove->Launch(
            60.f, 0.f,
            DEG_TO_RAD((rand() % 360)), DEG_TO_RAD(0.f));
        actions.push(randomMove);
    }
    
    // 복합 패턴 설정
    IObjectComplexPattern* spellCard3 = new IObjectComplexPattern();
    spellCard3->SetPatternStartTime(0.0f);
    spellCard3->SetPatternEndTime(999.f);
    spellCard3->SetTarget(this);
    spellCard3->SetActions(actions);
    
    ec->SetActionPatterns(spellCard3);
    
    // 스펠카드 선언 효과음 재생
    // SoundPlayer::GetInstance()->SoundOn("spell_card_declare");
    
    // 스펠카드 이펙트 재생
    // EffectPlayer::GetInstance()->PlayEffect("spell_card_effect", position);
}

void BHBoss::ShootNormal1()
{
    // 이 함수는 직접 호출되지 않고 SetupNormalPattern에서 설정된 패턴으로 실행됨
}

void BHBoss::ShootSpell1()
{
    // 이 함수는 직접 호출되지 않고 SetupSpellCard1에서 설정된 패턴으로 실행됨
}

void BHBoss::ShootSpell2()
{
    // 이 함수는 직접 호출되지 않고 SetupSpellCard2에서 설정된 패턴으로 실행됨
}

void BHBoss::ShootSpell3()
{
    // 이 함수는 직접 호출되지 않고 SetupSpellCard3에서 설정된 패턴으로 실행됨
}
