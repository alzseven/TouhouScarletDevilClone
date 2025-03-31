#pragma once
#include "BHObject.h"
// class BHObjectController;

class EnemyController;
class BulletManager;

// class IPatternInfo;
class BHEnemy : public BHObject
{
private:
    int frameIndex;
    float timeElapsed;
    float shootDelay;

    int tempLevel;
    Image* moveImage;
    FPOINT moveDir;

    BulletManager* bulletManager;
    EnemyController* ec;
    // BHObjectController* controller;
    
    // IPatternInfo* patterns;
    // IPatternInfo* currentPattern;
public:
    // »ý¼ºÀÚ
    BHEnemy() = default;
    virtual ~BHEnemy () = default;

    inline void SetMoveImage(Image* moveImage) { this->moveImage = moveImage; }
    
    void Init(Image* image, float hit, FPOINT position, float radianAngle) override;

    void Move(float angle, float speed, float dt) override;
    
    void Render(HDC hdc) override;

    void Update(float dt) override;

    void Shoot(float angle, int shootAmount = 1) override;

    void OnHit(ICollideable* hitObject) override;

    void Release() override;

    void GetDamaged();
    
    // inline float GetHit() override { return hit; }
    // inline FPOINT GetPos() override { return position; }
};

