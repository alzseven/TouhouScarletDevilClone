#include "ShootSpiralPattern.h"
#include "BHObject.h"
#include "SoundPlayer.h"

void ShootSpiralPattern::Update(float dt)
{
    timeElpased += dt;
    shootTimer += dt;
    
    // 나선형 각도 증가
    spiralAngleOffset += DEG_TO_RAD(2.0f) * dt;
    
    if (timeElpased <= patternEndTime)
    {
        if (shootTimer >= shootDelay)
        {
            currentShootCount++;
            
            // 효과음 재생
            if(currentShootCount == 1) SoundPlayer::GetInstance()->SoundOn("enemy_shoot");
            
            // 나선형 패턴으로 총알 발사
            // 기본 각도에 나선형 각도 오프셋을 더하고, 현재 발사 횟수에 따라 각도를 조정
            float currentAngle = shootAngle + spiralAngleOffset + DEG_TO_RAD(360.0f / shootAmount * currentShootCount);
            
            target->Shoot(
                bulletShapeKey,
                *target->GetPos(),
                currentAngle,
                shootAngleRate,
                shootSpeed,
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
