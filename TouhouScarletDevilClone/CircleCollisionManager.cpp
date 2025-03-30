#include "CircleCollisionManager.h"

#include "BHObject.h"
#include "CommonFunction.h"
#include "Grid.h"
#include "ICircleCollideable.h"

void CircleCollisionManager::Release()
{
    for (std::vector<ICircleCollideable*>::iterator iter = collisions.begin(); iter != collisions.end(); ++iter)
    {
        dynamic_cast<BHObject*>(*iter)->Release();
        delete *iter;
    }
    collisions.clear();
    ReleaseInstance();
}

void CircleCollisionManager::Update()
{
    if (collisions.size() < 2) return;
    for (size_t i = 0; i < collisions.size(); ++i)
    {
        for (size_t j = i + 1; j < collisions.size(); ++j)
        {
            ICircleCollideable* objA = collisions[i];
            ICircleCollideable* objB = collisions[j];
            
            if (ShouldCollide(objA->GetLayer(), objB->GetLayer()) && IsCircleCollided(objA->GetPos(), objB->GetPos(),
                objA->GetHitRadius(), objB->GetHitRadius()))
            {
                objA->OnHit(objB);
                objB->OnHit(objA);
            }
        }
    }
}

void CircleCollisionManager::AddCollisionObject(ICircleCollideable* collisionObject)
{
    collisions.push_back(collisionObject);
}

bool CircleCollisionManager::ShouldCollide(CollisionLayer layerA, CollisionLayer layerB)
{
    //TODO:
    for (int i=0; i<3; i++)
    {
        if ((layerA & collisionMatrix[i].layer1 && layerB & collisionMatrix[i].layer2) ||
            (layerA & collisionMatrix[i].layer2 && layerB & collisionMatrix[i].layer1))
        {
            return true;
        }
    }
    return false;
}