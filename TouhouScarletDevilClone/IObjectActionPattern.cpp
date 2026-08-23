#include "IObjectActionPattern.h"

#include "BHEnemy.h"
#include "BHObject.h"

IObjectActionPattern::IObjectActionPattern() : patternStartTime(0), patternEndTime(0), target(nullptr), moveSpeed(0),
                                               moveSpeedRate(0),
                                               moveAngle(0),
                                               moveAngleRate(0),
                                               shootDelay(0),
                                               shootAmount(0),
                                               shootAngle(0),
                                               shootAngleRate(0),
                                               shootSpeed(0),
                                               shootSpeedRate(0),
                                               multiShootDelay(0),
                                               shootTimer(0),
                                               timeElpased(0)
{
}

void IObjectActionPattern::Update(float dt)
{
    timeElpased += dt;
    
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
            
            target->Shoot(bulletShapeKey, *target->GetPos(),
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
        if(currentShootCount == 1)SoundPlayer::GetInstance()->SoundOn("enemy_shoot");
        if (shootTimer >= shootDelay)
        {
            currentShootCount++;

            target->Shoot(bulletShapeKey,*target->GetPos(),
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

            target->Shoot(bulletShapeKey, *target->GetPos(),
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

void Stage1BossNormalPattern1::Update(float dt)
{
    timeElpased += dt;
    shootTimer += dt;
    if (timeElpased <= patternEndTime)
    {
        if (shootTimer >= shootDelay)
        {
            currentShootCount++;
            
            for (int i = 0; i < 16; ++i)
            {
                target->Shoot(
                    bulletShapeKey,
                    *target->GetPos(),
                    shootAngle + DEG_TO_RAD(360.f / shootAmount * i),
                    shootAngleRate,
                    shootSpeed,
                    shootSpeedRate);
            }

            for (int i = 0; i < 16; ++i)
            {
                target->Shoot(
                    bulletShapeKey,
                    *target->GetPos(),
                    shootAngle + DEG_TO_RAD(360.f / shootAmount * i) + DEG_TO_RAD(15.f),
                    shootAngleRate,
                    shootSpeed,
                    shootSpeedRate);
            }
            
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

// 여기에 IObjectActionPattern.h에서 선언한 클래스의 구현부를 제작하시오
// Update 내부에서 실질적인 이동과 발사는 위에 선언된 함수들을 참고하시오