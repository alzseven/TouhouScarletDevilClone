#pragma once
#include "GameObject.h"

class Image;
class BHPlayer;

class TouhouScarletDevilCloneGame : public GameObject
{
private:
    BHPlayer* player;
    Image* bgImage;
public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    TouhouScarletDevilCloneGame() = default;
    ~TouhouScarletDevilCloneGame() = default;
};
