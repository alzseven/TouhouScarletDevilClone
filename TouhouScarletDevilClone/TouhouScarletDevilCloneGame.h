#pragma once
#include "GameObject.h"
#include "ObjectPool.h"
#include "StageWaveManager.h"

// class EnemyFactory;
class BHEnemy;
class BHPlayer;
class D2DImage;
class TouhouScarletDevilCloneGame : public GameObject
{
private:
    BHPlayer* player;
    BHEnemy* enemy;
    D2DImage* bgImage;
    ObjectPool<BHEnemy>* enemyFactory;
    int timer = 0;
    int frame = 0;
    float angle = 0;

    StageWaveManager* stageWaveManager;
public:
    void Init() override;
    void Release() override;
    void Update(float dt) override;
    void Render(HDC hdc);

    TouhouScarletDevilCloneGame() = default;
    ~TouhouScarletDevilCloneGame() override = default;
};
