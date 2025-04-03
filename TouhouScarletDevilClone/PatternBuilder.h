// #pragma once
// #include "config.h"
// #include "IPatternComponent.h"
//
//
// class IPatternComponent;
//
// class PatternBuilder {
//     vector<IPatternComponent*> patterns;
// public:
//     PatternBuilder& AddMovement(float speed, float angle) {
//         MovementComponent* movementComponent = new MovementComponent();
//         movementComponent->Init(speed, angle);
//         patterns.push_back(movementComponent);
//         return *this;
//     }
//     
//     PatternBuilder& AddAttack(string bulletShapeKey, FPOINT init_pos, float angle, float angleRate, float moveSpeed, float moveSpeedRate) {
//         AttackComponent* attackComponent = new AttackComponent();
//         attackComponent->Init(bulletShapeKey, init_pos, angle, angleRate, moveSpeed, moveSpeedRate);
//         patterns.push_back(attackComponent);
//         return *this;
//     }
//     
//     vector<IPatternComponent*> Build() { return patterns; }
// };
