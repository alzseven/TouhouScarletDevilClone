// #pragma once
// #include "BHObject.h"
//
// class BHObject;
//
// class IPatternComponent {
// public:
//     virtual void Apply(BHObject* obj, float dt) = 0;
// };
//
// class MovementComponent : public IPatternComponent {
//     float speed;
//     float angle;
// public:
//     void Apply(BHObject* obj, float dt) override {
//         obj->Move(speed, angle, dt);
//     }
//
//     void Init(float speed, float angle);
// };
//
// class AttackComponent : public IPatternComponent {
//     string bulletShapeKey;
//     FPOINT init_pos;
//     float angle;
//     float angleRate;
//     float moveSpeed;
//     float moveSpeedRate;
// public:
//     void Apply(BHObject* obj, float dt) override {
//         obj->Shoot(bulletShapeKey, init_pos, angle, angleRate, moveSpeed, moveSpeedRate);
//     }
//
//     void Init(string bulletShapeKey,FPOINT init_pos,float angle,float angleRate,float moveSpeed,float moveSpeedRate);
// };