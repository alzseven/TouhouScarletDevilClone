#pragma once

class IBHObjectControllerState;

class BHObjectController
{
    IBHObjectControllerState* states;
    int currentStateIndex;
public:
    void SetStates(IBHObjectControllerState* states) { this->states = states; }
    void Init();
    void Update();
    void Release();
    void ChangeToNextState();
};
