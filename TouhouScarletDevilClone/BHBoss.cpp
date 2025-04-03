#include "BHBoss.h"

#include "EnemyController.h"
#include "IObjectComplexPattern.h"

void BHBoss::Init(string shapeKey, FPOINT pos)
{
    BHEnemy::Init(shapeKey, pos);

    queue<IObjectActionPattern*> actions;
    //TODO: Set as ShootPattern
    IObjectActionPattern* patternNormal1ThrowKnifePattern1 = new IObjectActionPattern();
    patternNormal1ThrowKnifePattern1->SetPatternStartTime(0.f);
    patternNormal1ThrowKnifePattern1->SetPatternEndTime(6.f);
    patternNormal1ThrowKnifePattern1->SetTarget(this);
    patternNormal1ThrowKnifePattern1->SetShootParams(
        "kunai",
        2.f, 18, 0.f,
        DEG_TO_RAD(0.f), DEG_TO_RAD(10.f),
        50.f, -1.f); 
    actions.push(patternNormal1ThrowKnifePattern1);
    
    //TODO: Set as MovePattern
    IObjectActionPattern* patternNormal1MovePattern1 = new IObjectActionPattern();
    patternNormal1MovePattern1->SetPatternStartTime(0.f);
    patternNormal1MovePattern1->SetPatternEndTime(2.f);
    patternNormal1MovePattern1->SetTarget(this);
    patternNormal1MovePattern1->Launch(
        50.f, 0.f,
        DEG_TO_RAD((rand() % 360)), DEG_TO_RAD(0.f));
    actions.push(patternNormal1MovePattern1);

    
    
    IObjectComplexPattern* patternNormal1 = new IObjectComplexPattern();
    patternNormal1->SetPatternStartTime(0.0f);
    patternNormal1->SetPatternEndTime(999.f);
    patternNormal1->SetTarget(this);
    patternNormal1->SetActions(actions);
    
    ec->SetActionPatterns(patternNormal1);
}

void BHBoss::Update(float dt)
{
    if (isAlive == false) return;

    ec->Update(phase);
    
}

///TODO : StateTransition in pattern?
//
// void BHBoss::GetDamaged(int damage)
// {
//     health -= damage;
//     if (health <= 0)
//     {
//         //DO_SOMETHING
//         // isAlive = false;
//     }
//     else if (phase == 2 && health <= SPELL3_THRESHOLD)
//     {
//
//         phase = 3;
//     }
//     else if (phase == 1 && health <= SPELL2_THRESHOLD)
//     {
//
//         phase = 2;
//     }
//     else if (phase == 0 && health <= SPELL1_THRESHOLD)
//     {
//
//         phase = 1;
//     }
// }
//
// void BHBoss::ShootSpell1()
// {
//     ec->SetAction("Wait", 1.f);
//     ec->SetAction("random_round_spherical");
//     GLOBAL::TIME_STOP;
//     for (int i =0; i<4; ++i)
//     {
//         ec->SetAction("place_spread_knife_guided");
//         ec->SetAction("Wait", 0.2f);
//         ec->SetAction("place_spread_knife_dirctional");
//         ec->SetAction("Wait", 0.2f);
//     }
//     GLOBAL::TIME_RESUME;
// }
//
// void BHBoss::ShootNormal1()
// {  
//     SPAWN::BULLET_CENTER(posLT);
//     SPAWN::BULLET_CENTER(posRT);
//     SPAWN::BULLET_CENTER(posLD);
//     SPAWN::BULLET_CENTER(posRD);
//     //bullets - do something
//     ec->SetAction("round_knife");
//     ec->SetAction("Move_random",20.f); // distance
//     ec->SetAction("round_knife");
//     ec->SetAction("Move_random",20.f); // distance
//     ec->SetAction("round_knife");
//     ec->SetAction("Move_random",20.f); // distance
//     BULLET_CENTERS::REMOVE();
//     ec->SetAction("radial_knife");
//     ec->SetAction("wait");
// }
