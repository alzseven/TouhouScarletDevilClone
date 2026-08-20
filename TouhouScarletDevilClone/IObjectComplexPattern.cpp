#include "IObjectComplexPattern.h"

IObjectComplexPattern::~IObjectComplexPattern()
{
    while (!actions.empty())
    {
        delete actions.front();
        actions.pop();
    }

    for (auto* action : enabledActions)
        delete action;

    enabledActions.clear();
}

void IObjectComplexPattern::Update(float dt)
{
    timeElpased += dt;
    
    while (!actions.empty() && timeElpased >= actions.front()->GetPatternStartTime()) {
        enabledActions.push_back(actions.front());
        actions.pop();
    }
    
   
    for (auto it = enabledActions.begin(); it != enabledActions.end();)
    {
        IObjectActionPattern* pattern = *it;

        pattern->Update(dt);

        if (pattern->IsExpired())
        {
            it = enabledActions.erase(it);
            delete pattern;
        }
        else
        {
            ++it;
        }
    }
}

bool IObjectComplexPattern::IsExpired() const
{
    return actions.empty() && enabledActions.empty();
}
