#pragma once
#include "config.h"
#include "ICollideable.h"

class ICircleCollideable : public ICollideable
{
protected:
    float hitRadius;
public:
    ICircleCollideable() = default;
    ~ICircleCollideable() override = default;
    
    inline float GetHitRadius() const {return hitRadius;}
};
