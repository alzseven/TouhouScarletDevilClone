#pragma once
#include "GameObject.h"

class BHEnemy;
class BHPlayer;
class Image;
class D2DImage;
class TouhouScarletDevilCloneGame : public GameObject
{
private:
    BHPlayer* player;
    BHEnemy* enemy;
    D2DImage* bgImage;

public:
    void Init() override;
    void Release() override;
    void Update(float dt) override;
    void Render(HDC hdc);

    TouhouScarletDevilCloneGame() = default;
    ~TouhouScarletDevilCloneGame() override = default;
};
