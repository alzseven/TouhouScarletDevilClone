#pragma once
#include "BHObject.h"
#include "BHItem.h"

class EnemyController;
class BulletManager;
class D2DImage;
class BHEnemy : public BHObject
{
private:
    int frameIndex;
    float timeElapsed;
    float shootDelay;

    int tempLevel;
    D2DImage* moveImage;
    FPOINT moveDir;

    BulletManager* bulletManager;
    EnemyController* ec;

    // 아이템 관련 코드
    vector<BHItem*>* items = nullptr;
	GameState* gameState = nullptr;

public:
    // 생성자
    BHEnemy() = default;
    virtual ~BHEnemy () = default;

    inline void SetMoveImage(D2DImage* moveImage) { this->moveImage = moveImage; }

    void Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle) override;

    void Move(float angle, float speed, float dt) override;
    
    void Render(HDC hdc) override;

    void Update(float dt) override;
    
    void Shoot(FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) override;

    void OnHit(ICollideable* hitObject) override;

    void Release() override;

    void GetDamaged();

    // 아이템 관련 코드
	inline void SetItemList(vector<BHItem*>& itemList) { items = &itemList; }
	inline void SetGameState(GameState* state) { gameState = state; }
};

