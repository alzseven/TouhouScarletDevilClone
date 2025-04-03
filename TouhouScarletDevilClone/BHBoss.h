#pragma once
#include "BHEnemy.h"

class BHBoss : public BHEnemy
{
    int phase;
    int health;

    EnemyController* ec;
public:
    void Init(string shapeKey, FPOINT pos) override;
    
    void Update(float dt) override;

    void GetDamaged(int damage) override;

    void ShootSpell1();

    void ShootNormal1();
};