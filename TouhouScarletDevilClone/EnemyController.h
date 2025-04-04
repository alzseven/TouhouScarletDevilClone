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
    // IObjectActionPattern* patterns[4];

    vector<IObjectActionPattern*> enabledActions;
    
public:
    EnemyController();
    ~EnemyController();

    void Init();
    void Update(float dt);
    void AddPatternToTarget(IObjectActionPattern* newPatterns);
    inline void SetActionPatterns(IObjectActionPattern* newPattern) { actions.push(newPattern); }
    inline void SetTarget(BHObject* newTarget) { target = newTarget; }

    //Test
    // void SetAction(string action, float duration);
    // void SetAction(string action);
};
