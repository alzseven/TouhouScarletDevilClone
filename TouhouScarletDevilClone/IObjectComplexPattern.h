#pragma once
#include "IObjectActionPattern.h"
#include "config.h"

class IObjectComplexPattern : public IObjectActionPattern
{
    std::queue<IObjectActionPattern*> actions;
    // IObjectActionPattern* currentPattern;
    vector<IObjectActionPattern*> enabledActions;
public:
    void Init() override;
    void Update(float dt) override;
    bool IsExpired() const override;

    void SetActions(std::queue<IObjectActionPattern*> actions) { this->actions = actions; }
};