#pragma once
#include "GameObject.h"
#include "ObjectPool.h"

// class EnemyFactory;
class BHEnemy;
class BHPlayer;
class BHItem;
class D2DImage;
class UI;
class GameState;
class TouhouScarletDevilCloneGame : public GameObject
{
private:
    GameState* gameState;
    UI* ui;
    BHPlayer* player;
    BHEnemy* enemy;
    BHItem* item;
    D2DImage* bgImage;
    ObjectPool<BHEnemy>* enemyFactory;
    int timer = 0;
    int frame = 0;
    float angle = 0;
public:
    void Init() override;
    void Release() override;
    void Update(float dt) override;
    void Render(HDC hdc);
    TouhouScarletDevilCloneGame() = default;
    ~TouhouScarletDevilCloneGame() override = default;
};
