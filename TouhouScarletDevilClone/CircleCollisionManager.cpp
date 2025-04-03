#include "CircleCollisionManager.h"

#include "BHObject.h"
#include "CommonFunction.h"
#include "D2DImage.h"

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
        ICircleCollideable* objA = collisions[i];
        if (objA == nullptr || objA->IsValid() == false) continue;

        for (size_t j = i + 1; j < collisions.size(); ++j)
        {
            ICircleCollideable* objB = collisions[j];
            if (objB == nullptr || objB->IsValid() == false) continue;

            if (ShouldCollide(objA->GetLayer(), objB->GetLayer()) &&
                IsCircleCollided(objA->GetPos(), objB->GetPos(),
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

void CircleCollisionManager::RemoveCollisionObject(ICircleCollideable* collisionObject)
{
    // collisions.erase(std::remove(collisions.begin(), collisions.end(), collisionObject));
    collisions.erase(
        std::remove(collisions.begin(), collisions.end(), collisionObject),
        collisions.end()
    );
}

bool CircleCollisionManager::ShouldCollide(CollisionLayer layerA, CollisionLayer layerB)
{
    //TODO:
    for (auto& i : collisionMatrix)
    {
        if ((layerA & i.layer1 && layerB & i.layer2) ||
            (layerA & i.layer2 && layerB & i.layer1))
        {
            return true;
        }
    }
    return false;
}

void CircleCollisionManager::Render(HDC hdc)
{
    for (size_t i = 0; i < collisions.size(); ++i)
    {
        ICircleCollideable* objA = collisions[i];

        if (objA == nullptr || objA->IsValid() == false) continue;
        
        //Debug
        D2DImage debugImage;
        debugImage.DrawCircle(
            {objA->GetPos()->x, objA->GetPos()->y},
            objA->GetHitRadius(),
            0, 1);
    }
}
