#pragma once
#include "config.h"

class BHObject;

class ICircleCollideable
{
public:
    ICircleCollideable() = default;
    virtual ~ICircleCollideable() = default;
    
    virtual FPOINT* GetPos() = 0;
    virtual float GetHit() = 0;
    virtual void OnHit(ICircleCollideable* hitObject) = 0;
};
