#pragma once
#include <vector>

#include "Singleton.h"

class ICircleCollideable;

class CollisionManager : public Singleton<CollisionManager>
{
private:
    std::vector<ICircleCollideable*> collisions;

    //TODO: Check Collision with player only
    //TODO: Check player missile - enemies
public:
    void Release();
    void Update();
    void AddCollisionObject(ICircleCollideable* collisionObject);
};