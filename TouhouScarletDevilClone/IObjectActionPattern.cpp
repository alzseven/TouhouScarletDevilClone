#include "IObjectActionPattern.h"

#include "BHEnemy.h"
#include "BHObject.h"

void IObjectActionPattern::Update(float dt)
{
    
    
}

void MoveStraightDirectionPattern::Update(float dt)
{
    //delay
    timeElpased += dt;
    if (timeElpased <= patternEndTime)
    {
        target->Move(moveAngle, moveSpeed, dt);
    }
}

void ShootStraightPattern::Update(float dt)
{
    timeElpased += dt;
    shootTimer += dt;
    if (timeElpased <= patternEndTime)
    {
        if (shootTimer >= shootDelay)
        {
            currentShootCount++;
            
            target->Shoot("ball_green", *target->GetPos(),
                shootAngle, shootAngleRate,
                shootSpeed, shootSpeedRate);

            if (currentShootCount >= shootAmount)
            {
                currentShootCount = 0;
                shootTimer -= shootDelay;
            }
            else
            {
                shootTimer -= multiShootDelay;
            }
        }

    }
}

void ShootSpreadPattern::Update(float dt)
{
    timeElpased += dt;
    shootTimer += dt;
    if (timeElpased <= patternEndTime)
    {
        if (shootTimer >= shootDelay)
        {
            currentShootCount++;

            target->Shoot("ball_green",*target->GetPos(),
                shootAngle + DEG_TO_RAD(currentShootCount * -10.f), shootAngleRate,
                shootSpeed, shootSpeedRate);

            //TODO: to handle bullet speed by time,
            //TODO: target->Shoot(some_kind_of_slowed_or_fasted_bullet?) - overloading

            if (currentShootCount >= shootAmount)
            {
                currentShootCount = 0;
                shootTimer -= shootDelay;
            }
            else
            {
                shootTimer -= multiShootDelay;
            }
        }
    }
}

void ShootRoundPattern::Update(float dt)
{
    timeElpased += dt;
    shootTimer += dt;
    if (timeElpased <= patternEndTime)
    {
        if (shootTimer >= shootDelay)
        {
            currentShootCount++;

            target->Shoot("ball_green", *target->GetPos(),
                shootAngle + DEG_TO_RAD(360.f / shootAmount * currentShootCount), shootAngleRate,
                shootSpeed, shootSpeedRate);

            
            // for (currentShootCount = 1; currentShootCount<= shootAmount; ++currentShootCount)
            // {
            //     target->Shoot(*target->GetPos(), angle + DEG_TO_RAD(360.f / shootAmount * currentShootCount), angleRate, shootSpeed, shootSpeedRate);
            // }
            
            if (currentShootCount >= shootAmount)
            {
                currentShootCount = 0;
                shootTimer -= shootDelay;
            }
            else
            {
                shootTimer -= multiShootDelay;
            }
        }

    }
}