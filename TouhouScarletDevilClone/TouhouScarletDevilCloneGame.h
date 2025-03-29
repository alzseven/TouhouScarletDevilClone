#pragma once
// #include "D2DImage.h"
#include "GameObject.h"

class Image;
class BHPlayer;
class BHEnemy;
class TouhouScarletDevilCloneGame : public GameObject
{
private:
    BHPlayer* player;
    BHEnemy* enemy;
    Image* bgImage;

public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    TouhouScarletDevilCloneGame() = default;
    ~TouhouScarletDevilCloneGame() = default;
};
