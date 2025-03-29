#pragma once
// #include "D2DImage.h"
#include "GameObject.h"

class Image;
class BHPlayer;
class BHEnemy;
class D2DImage;
class TouhouScarletDevilCloneGame : public GameObject
{
private:
    BHPlayer* player;
    BHEnemy* enemy;
    Image* bgImage;
    D2DImage* testImage;
public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    TouhouScarletDevilCloneGame() = default;
    ~TouhouScarletDevilCloneGame() = default;
};
