#pragma once

class BHObject;

class IObjectActionPattern
{
protected:
    //Move params
    float moveSpeed;
    float moveSpeedRate;
    float angle;
    float angleRate;

    //Shoot params
    float shootDelay;
    int shootAmount;
    float shootAngle;
    float shootTimer;

    float patternStartTime;
    float patternEndTime;
    BHObject* target;
    float timeElpased;

public:
    virtual void Update(float dt);
    void Move();
    void Shoot();
    inline void SetTarget(BHObject* target) { this->target = target; }
    inline void SetPatternEndTime(float newEndTime) { this->patternEndTime = newEndTime; }
    inline void SetPatternStartTime(float newEndTime) { this->patternStartTime = newEndTime; }
    
    inline void Launch(float moveSpeed, float moveSpeedRate, float angle, float angleRate)
    {
        this->moveSpeed = moveSpeed;
        this->moveSpeedRate = moveSpeedRate;
        this->angle = angle;
        this->angleRate = angleRate;
    }

    inline void SetShootParams(float shootDelay, int shootAmount, float shootAngle)
    {
        this->shootDelay = shootDelay;
        this->shootAmount = shootAmount;
        this->shootAngle = shootAngle;
    }

    float GetPatternStartTime() const
    {
        return patternStartTime;
    }

    float GetPatternEndTime() const
    {
        return patternEndTime;
    }
};

class MoveStraightDirectionPattern : public IObjectActionPattern
{
    void Update(float dt) override;
};

class ShootStraightPattern : public IObjectActionPattern
{
    void Update(float dt) override;
};
