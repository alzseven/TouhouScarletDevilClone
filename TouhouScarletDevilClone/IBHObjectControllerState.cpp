#include "IBHObjectControllerState.h"

#include "BHObject.h"

void BHObjectInitialMove::Init(BHObject* target, float endTime)
{
    IBHObjectControllerState::Init(target, endTime);
}

void BHObjectInitialMove::Launch(float angle, float angleRate, float moveSpeed, float moveSpeedRate)
{
    this->angle = angle;
    this->angleRate = angleRate;
    this->moveSpeed = moveSpeed;
    this->moveSpeedRate = moveSpeedRate;
}

void BHObjectInitialMove::OnEnter()
{
    
}

void BHObjectInitialMove::OnUpdate()
{
    target->Move(angle, moveSpeed);

    angle += angleRate;
    moveSpeed += moveSpeedRate;
}

void BHObjectInitialMove::OnExit()
{
    
}
