// #pragma once
//
// class IBHObjectControllerState
// {
// public:
//     IBHObjectControllerState();
//     virtual ~IBHObjectControllerState();
//     
//     virtual void OnEnter() = 0;
//     virtual void OnUpdate() = 0;
//     virtual void OnExit() = 0;
// };
//
// class BHObject;
// class BHObjectInitialMove : public IBHObjectControllerState
// {
//     float endTime;
//     float elapsedTime;
//     float angle;
//     // angluar accel
//     float angleRate;
//     float moveSpeed;
//     // movementSpeed accel
//     float moveSpeedRate;
//     BHObject* target;
// public:
//     void OnEnter() override;
//     void OnUpdate() override;
//     void OnExit() override;
// };