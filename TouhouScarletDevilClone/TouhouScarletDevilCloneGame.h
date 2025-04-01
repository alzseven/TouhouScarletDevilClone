#pragma once
#include "GameObject.h"

class BHEnemy;
class BHPlayer;
class Image;
class TouhouScarletDevilCloneGame : public GameObject
{
private:
    BHPlayer* player;
    BHEnemy* enemy;
    Image* bgImage;
public:
    void Init() override;
    void Release() override;
    void Update(float dt) override;
    void Render(HDC hdc) override;

    TouhouScarletDevilCloneGame() = default;
    ~TouhouScarletDevilCloneGame() override = default;
};
