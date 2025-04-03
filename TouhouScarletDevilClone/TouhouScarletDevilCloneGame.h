#pragma once
#include "GameObject.h"
#include "ObjectPool.h"
#include "StageWaveManager.h"

class BHEnemy;
class BHPlayer;
class D2DImage;
class TouhouScarletDevilCloneGame : public GameObject
{
private:
    BHPlayer* player;
    D2DImage* bgImage;

    StageWaveManager stageWaveManager;
public:
    void Init() override;
    void Release() override;
    void Update(float dt) override;
    void Render(HDC hdc);

    TouhouScarletDevilCloneGame() = default;
    ~TouhouScarletDevilCloneGame() override = default;
};
