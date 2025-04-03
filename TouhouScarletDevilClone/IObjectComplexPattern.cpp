#include "IObjectComplexPattern.h"

void IObjectComplexPattern::Init()
{
    // currentPattern = actions->front();
    // actions->pop();
}

void IObjectComplexPattern::Update(float dt)
{
    timeElpased += dt;
    
    while (!actions.empty() && timeElpased >= actions.front()->GetPatternStartTime()) {
        enabledActions.push_back(std::move(actions.front()));
        actions.pop();
    }
    
    // for (std::vector<IObjectActionPattern*>::iterator iter = enabledActions.begin(); iter != enabledActions.end(); ++iter)
    // {
    //     (*iter)->Update(dt);
    // }
    
    // Update and remove expired
    enabledActions.erase(
        std::remove_if(enabledActions.begin(), enabledActions.end(),
            [dt](const auto& pattern) {
                pattern->Update(dt);
                return pattern->IsExpired();
            }),
        enabledActions.end()
    );
    
    // if (timeElpased >= currentPattern->GetPatternEndTime())
    // {
    //     if (!actions->empty()) {
    //         timeElpased -= currentPattern->GetPatternEndTime();
    //         currentPattern = actions->front();
    //         actions->pop();
    //     }
    // }
    //
    //
    // currentPattern->Update(dt);
}

bool IObjectComplexPattern::IsExpired() const
{
    // return false;
    return actions.empty() && enabledActions.empty();
}
