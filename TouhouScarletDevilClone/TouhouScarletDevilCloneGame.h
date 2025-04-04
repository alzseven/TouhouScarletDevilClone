#pragma once
#include "GameObject.h"
#include "GameState.h"
#include "ObjectPool.h"
#include "StageWaveManager.h"

class BHEnemy;
class BHPlayer;
class BHItem;
class D2DImage;
class InGame;
class TouhouScarletDevilCloneGame : public GameObject
{
private:
    InGame* inGame;
    BHPlayer* player;
    D2DImage* bgImage;
    StageWaveManager* stageWaveManager;
    
    int frame = 0;
    float angle = 0;
	bool finishFlag = false;   
    
    int timer=0;
public:
    void Init() override;
    void Release() override;
    void Update(float dt) override;
    void Render(HDC hdc);
    TouhouScarletDevilCloneGame() = default;
    ~TouhouScarletDevilCloneGame() override = default;

    inline bool FinishFlag() { return finishFlag; }
};
