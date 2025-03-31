#pragma once
#include <stack>

#include "config.h"

class IObjectActionPattern;
class BHObject;

class EnemyController
{
protected:
    BHObject* target;
    std::queue<IObjectActionPattern*> actions;
    float timeElapsed;
    IObjectActionPattern* patterns[4];

    vector<IObjectActionPattern*> enabledActions;
public:
    EnemyController();
    ~EnemyController();

    void Init();
    void Update(float dt);
    void AddPatternToTarget(IObjectActionPattern* newPatterns);
    inline void SetActionPatterns(IObjectActionPattern* newPatterns) { actions.push(newPatterns); }
    inline void SetTarget(BHObject* newTarget) { target = newTarget; }
};
