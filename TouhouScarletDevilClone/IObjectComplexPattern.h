#pragma once
#include "IObjectActionPattern.h"
#include "config.h"

class IObjectComplexPattern : public IObjectActionPattern
{
    std::queue<IObjectActionPattern*> actions;
    vector<IObjectActionPattern*> enabledActions;
    
public:
    IObjectComplexPattern() = default;
    ~IObjectComplexPattern() override;
    void Update(float dt) override;
    bool IsExpired() const override;
    
    // Takes sole ownership of all pointers in newActions.
    void SetActions(std::queue<IObjectActionPattern*> actions) { this->actions = actions; }
    
    IObjectComplexPattern(const IObjectComplexPattern&) = delete;
    IObjectComplexPattern& operator=(const IObjectComplexPattern&) = delete;
};