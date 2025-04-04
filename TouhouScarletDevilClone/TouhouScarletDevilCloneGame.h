#pragma once
#include "GameObject.h"
#include "GameState.h"
#include "ObjectPool.h"
#include "StageWaveManager.h"

class BHEnemy;
class BHPlayer;
class BHItem;
class D2DImage;
class UI;
class TouhouScarletDevilCloneGame : public GameObject
{
private:
    GameState gameState;
    vector<BHItem*> items;
    UI* ui;
    BHPlayer* player;
    D2DImage* bgImage;
    float timer;
    StageWaveManager stageWaveManager;
public:
    void Init() override;
    void Release() override;
    void Update(float dt) override;
    void Render(HDC hdc);
    TouhouScarletDevilCloneGame() = default;
    ~TouhouScarletDevilCloneGame() override = default;
};
