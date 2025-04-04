#pragma once
#include "IObjectActionPattern.h"

// 시간에 따라 총알 속도가 변하는 패턴
class ShootTimeVaryingSpeedPattern : public IObjectActionPattern
{
private:
    int currentShootCount;
    float speedMultiplier;
    float speedMultiplierRate;
    
public:
    ShootTimeVaryingSpeedPattern() : currentShootCount(0), speedMultiplier(1.0f), speedMultiplierRate(0.1f) {}
    
    void Update(float dt) override;
    
    // 속도 변화율 설정
    inline void SetSpeedMultiplierRate(float rate) { this->speedMultiplierRate = rate; }
};
