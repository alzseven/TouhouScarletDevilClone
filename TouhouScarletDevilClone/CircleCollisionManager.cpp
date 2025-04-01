#include "CircleCollisionManager.h"

#include "BHObject.h"
#include "CommonFunction.h"
// #include "Grid.h"
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
    // for (size_t i = 0; i < collisions.size(); ++i)
    // {
    //     ICircleCollideable* objA = collisions[i];
    //     
    //     HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    //     // 기존 펜 받아서
    //     HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    //     HBRUSH oldbrush = (HBRUSH)SelectObject( hdc, GetStockObject( NULL_BRUSH ) );
    //
    //
    //     RenderEllipseAtCenter(hdc, objA->GetPos()->x, objA->GetPos()->y, objA->GetHitRadius() * 2, objA->GetHitRadius() * 2);
    //     // 다시 원래 펜으로
    //     SelectObject(hdc, hOldPen);
    //     SelectObject(hdc, oldbrush);
    //     // 삭제
    //     DeleteObject(hPen);
    // }
}