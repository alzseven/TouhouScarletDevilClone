#pragma once
#include "GameObject.h"

class TouhouScarletDevilCloneGame : public GameObject
{
private:
    // Add game contents
public:
    void Init();
    void Release();
    void Update(float dt);
    void Render(HDC hdc);

    TouhouScarletDevilCloneGame() = default;
    ~TouhouScarletDevilCloneGame() = default;
};
