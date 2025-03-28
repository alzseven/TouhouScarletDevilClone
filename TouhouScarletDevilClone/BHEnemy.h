#pragma once
#include "BHObject.h"
class BHEnemy : public BHObject
{
private:
    int frameIndex;
    float timeElapsed;
    float shootDelay;

    int tempLevel;
    Image* moveImage;
    FPOINT moveDir;
    
public:
    // »ý¼ºÀÚ
    BHEnemy() = default;
    virtual ~BHEnemy () = default;

    inline void SetMoveImage(Image* moveImage) { this->moveImage = moveImage; }
    
    void Init(Image* image, float hit, FPOINT position, float radianAngle) override;

    virtual void Move(FPOINT moveDirection);
    
    void Render(HDC hdc) override;

    void Update() override;

    void Shoot();
};

