#include "CollisionManager.h"

#include "BHObject.h"
#include "CommonFunction.h"
#include "ICircleCollideable.h"

void CollisionManager::Release()
{
    for (std::vector<ICircleCollideable*>::iterator iter = collisions.begin(); iter != collisions.end(); ++iter)
    {
        dynamic_cast<BHObject*>(*iter)->Release();
        delete *iter;
    }
    ReleaseInstance();
}

void CollisionManager::Update()
{
    if(collisions.size() < 2) return;
    for(size_t i = 0; i < collisions.size()-1; ++i) {
        for(size_t j = i+1; j < collisions.size(); ++j) {
            ICircleCollideable* a = collisions[i];
            ICircleCollideable* b = collisions[j];
            
            if(IsCircleCollided(a->GetPos(), b->GetPos(), a->GetHit(), b->GetHit())) {
                a->OnHit(b);
                b->OnHit(a); // Optional mutual notification
            }
        }
    }
}

void CollisionManager::AddCollisionObject(ICircleCollideable* collisionObject)
{
    collisions.push_back(collisionObject);
}
