#pragma once

class BHObject;

class IBHObjectControllerState
{
public:
    IBHObjectControllerState();
    virtual ~IBHObjectControllerState();

    virtual void Init(BHObject* target, float endTime) {}
    virtual void OnEnter() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnExit() = 0;
};

class BHObject;
class BHObjectInitialMove : public IBHObjectControllerState
{
    float endTime;
    float elapsedTime;
    float angle;
    // angluar accel
    float angleRate;
    float moveSpeed;
    // movementSpeed accel
    float moveSpeedRate;
    BHObject* target;
public:
    void Init(BHObject* target, float endTime) override;
    void Launch(float angle, float angleRate, float moveSpeed, float moveSpeedRate);
    void OnEnter() override;
    void OnUpdate() override;
    void OnExit() override;
};