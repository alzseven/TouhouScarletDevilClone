#pragma once
#include "config.h"

class BHObject;

class IObjectActionPattern
{
protected:
    float patternStartTime;
    float patternEndTime;
    BHObject* target;
    
    //Move params
    float moveSpeed;
    float moveSpeedRate;
    float moveAngle;
    float moveAngleRate;

    //Shoot params
    string bulletShapeKey;
    float shootDelay;
    int shootAmount;
    float shootAngle;
    float shootAngleRate;
    float shootSpeed;
    float shootSpeedRate;
    float multiShootDelay;
    
    float shootTimer;


    float timeElpased;

public:
    virtual void Init(){};
    virtual void Update(float dt);
    inline void SetTarget(BHObject* target) { this->target = target; }
    inline void SetPatternEndTime(float newEndTime) { this->patternEndTime = newEndTime; }
    inline void SetPatternStartTime(float newEndTime) { this->patternStartTime = newEndTime; }
    
    inline void Launch(float moveSpeed, float moveSpeedRate, float angle, float angleRate)
    {
        this->moveSpeed = moveSpeed;
        this->moveSpeedRate = moveSpeedRate;
        this->moveAngle = angle;
        this->moveAngleRate = angleRate;
    }

    inline void SetShootParams(
        string bulletShapeKey,
        float shootDelay,
        int shootAmount, float multiShootDelay,
        float shootAngle, float shootAngleRate,
        float shootSpeed ,float shootSpeedRate)
    {
        this->bulletShapeKey = bulletShapeKey;
        this->shootDelay = shootDelay;
        this->shootAmount = shootAmount;
        this->multiShootDelay = multiShootDelay;
        this->shootAngle = shootAngle;
        this->shootAngleRate = shootAngleRate;
        this->shootSpeed = shootSpeed;
        this->shootSpeedRate = shootSpeedRate;
    }

    float GetPatternStartTime() const
    {
        return patternStartTime;
    }

    float GetPatternEndTime() const
    {
        return patternEndTime;
    }

    virtual bool IsExpired() const {
        return timeElpased >= (patternEndTime - patternStartTime);
    }
};

class MoveStraightDirectionPattern : public IObjectActionPattern
{
    void Update(float dt) override;
};

class ShootStraightPattern : public IObjectActionPattern
{
    int currentShootCount;
    
    void Update(float dt) override;
};

class ShootSpreadPattern : public IObjectActionPattern
{
    int currentShootCount;
    
    void Update(float dt) override;
};

class ShootRoundPattern : public IObjectActionPattern
{
    int currentShootCount;
    
    void Update(float dt) override;
};

class Stage1BossNormalPattern1 : public IObjectActionPattern
{
    int currentShootCount;
    
    void Update(float dt) override;
};