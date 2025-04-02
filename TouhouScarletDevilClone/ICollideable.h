#pragma once
#include "config.h"

class ICollideable
{
protected:
    CollisionLayer currentLayer;  // 현재 소속 레이어
    CollisionLayer collideWith;   // 충돌 가능 레이어 비트마스크
public:
    ICollideable() = default;
    virtual ~ICollideable() = default;
    
    inline void SetCollisionLayer(CollisionLayer layer, CollisionLayer mask) {
        currentLayer = layer;
        collideWith = mask;
    }
    
    CollisionLayer GetLayer() const { return currentLayer; }
    CollisionLayer GetCollisionMask() const { return collideWith; }

    virtual FPOINT* GetPos() = 0;
    virtual void OnHit(ICollideable* hitObject) = 0;
    virtual bool IsValid() = 0;
};
