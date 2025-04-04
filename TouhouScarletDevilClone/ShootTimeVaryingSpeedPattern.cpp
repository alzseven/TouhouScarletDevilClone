#include "ShootTimeVaryingSpeedPattern.h"
#include "BHObject.h"
#include "SoundPlayer.h"

void ShootTimeVaryingSpeedPattern::Update(float dt)
{
    timeElpased += dt;
    shootTimer += dt;
    
    // 시간에 따라 속도 승수 업데이트
    speedMultiplier += speedMultiplierRate * dt;
    
    if (timeElpased <= patternEndTime)
    {
        if (shootTimer >= shootDelay)
        {
            currentShootCount++;
            
            // 효과음 재생
            if(currentShootCount == 1) SoundPlayer::GetInstance()->SoundOn("enemy_shoot");
            
            // 시간에 따라 변화하는 속도로 총알 발사
            float currentSpeed = shootSpeed * speedMultiplier;
            
            target->Shoot(
                bulletShapeKey,
                *target->GetPos(),
                shootAngle + DEG_TO_RAD(currentShootCount * -10.f),
                shootAngleRate,
                currentSpeed,
                shootSpeedRate
            );
            
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
