#pragma once
#include "config.h"
#include "ICollideable.h"

class ICircleCollideable : public ICollideable
{
public:
    ICircleCollideable() = default;
    ~ICircleCollideable() override = default;
    
    virtual float GetHitRadius() = 0;
};
