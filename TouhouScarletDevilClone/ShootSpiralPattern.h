#pragma once
#include "IObjectActionPattern.h"

// 나선형 탄막 패턴 클래스
class ShootSpiralPattern : public IObjectActionPattern
{
private:
    int currentShootCount;
    float spiralAngleOffset;
    
public:
    ShootSpiralPattern() : currentShootCount(0), spiralAngleOffset(0.0f) {}
    
    void Update(float dt) override;
};
