#pragma once
#include "BHEnemy.h"

// 보스 페이즈 상수 정의
#define SPELL1_THRESHOLD 800
#define SPELL2_THRESHOLD 500
#define SPELL3_THRESHOLD 200

class BHBoss : public BHEnemy
{
    int phase;
    int health;
    float phaseTimer;  // 페이즈 전환 타이머
    bool isPhaseChanging; // 페이즈 전환 중인지 여부

    EnemyController* ec;
public:
    void Init(string shapeKey, FPOINT pos) override;
    void Init(string shapeKey, FPOINT pos, std::vector<IObjectActionPattern*> patterns) override;
    
    void Update(float dt) override;

    void GetDamaged(int damage) override;

    // 일반 패턴
    void ShootNormal1();
    
    // 스펠카드 패턴
    void ShootSpell1();  // 시간 정지 + 나이프 패턴
    void ShootSpell2();  // 환영 나이프 패턴
    void ShootSpell3();  // 일루전 다이얼 패턴
    
    // 페이즈 전환 처리
    void ChangePhase(int newPhase);
    
    // 패턴 설정 함수
    void SetupNormalPattern();
    void SetupSpellCard1();
    void SetupSpellCard2();
    void SetupSpellCard3();
};
