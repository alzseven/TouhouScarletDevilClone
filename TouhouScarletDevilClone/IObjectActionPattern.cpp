#include "IObjectActionPattern.h"

#include "BHEnemy.h"
#include "BHObject.h"

void IObjectActionPattern::Update(float dt)
{
    
    
}

void IObjectActionPattern::Move()
{
}

void IObjectActionPattern::Shoot()
{
}

void MoveStraightDirectionPattern::Update(float dt)
{
    //delay
    timeElpased += dt;
    if (timeElpased <= patternEndTime)
    {
        target->Move(angle, moveSpeed, dt);
    }
    // TODO: when endTime, then do what?
    // TODO: Remove this pattern from enemy?
    
    
    // if (timeElpased >= 1.f)
    // {
    //     
    //     angle += angleRate * dt;
    //     moveSpeed += moveSpeedRate * dt;
    //     timeElpased = 0.f;
    // }
}

void ShootStraightPattern::Update(float dt)
{
    timeElpased += dt;
    shootTimer += dt;
    if (timeElpased <= patternEndTime)
    {
        if (shootTimer >= shootDelay)
        {
            // static_cast<BHEnemy*>(target)
            target->Shoot(shootAngle, shootAmount);
            shootTimer -= shootDelay;
        }

    }
}
