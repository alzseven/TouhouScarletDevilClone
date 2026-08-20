#pragma once
#include <stack>

#include "config.h"

class IObjectActionPattern;
class BHObject;

class EnemyController
{
protected:
    BHObject* target = nullptr;

    float timeElapsed = 0.f;
    
    std::queue<IObjectActionPattern*> actions;
    vector<IObjectActionPattern*> enabledActions;
    
public:
    EnemyController() = default;
    ~EnemyController();

    void Init();
    void Update(float dt);
    // Takes sole ownership of newPattern.
    // newPattern must not already be owned elsewhere.
    inline void SetActionPatterns(IObjectActionPattern* newPattern) { actions.push(newPattern); }
    inline void SetTarget(BHObject* newTarget) { target = newTarget; }
    
    EnemyController(const EnemyController&) = delete;
    EnemyController& operator=(const EnemyController&) = delete;
};
