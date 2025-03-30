#pragma once
#include <vector>

#include "config.h"
#include "Singleton.h"

class ICircleCollideable;
class CircleCollisionManager : public Singleton<CircleCollisionManager>
{
private:
    std::vector<ICircleCollideable*> collisions;
    CollisionMatrixEntry collisionMatrix[3] = {
        {LAYER_PLAYER, LAYER_ENEMY_BULLET},
        {LAYER_ENEMY, LAYER_PLAYER_BULLET},
        {LAYER_PLAYER, LAYER_ITEM},
    };
public:
    void Release();
    void Update();
    void AddCollisionObject(ICircleCollideable* collisionObject);
    bool ShouldCollide(CollisionLayer layerA, CollisionLayer layerB);
    void Render(HDC hdc);

};