#include "CircleCollisionManager.h"
#include "BHObject.h"
#include "BHObjectManager.h"
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
    collisions.clear();
    collisions.push_back(BHObjectManager::GetInstance()->GetPlayer());
    auto ep = BHObjectManager::GetInstance()->GetEnemyPool()->GetActive();
    collisions.insert(collisions.end(), ep.begin(),ep.end());
    auto ebp = BHObjectManager::GetInstance()->GetEnemyBulletPool()->GetActive();
    collisions.insert(collisions.end(), ebp.begin(),ebp.end());
    auto pbp = BHObjectManager::GetInstance()->GetPlayerBulletPool()->GetActive();
    collisions.insert(collisions.end(), pbp.begin(),pbp.end());
    auto bosp = BHObjectManager::GetInstance()->GetBossPool()->GetActive();
    collisions.insert(collisions.end(), bosp.begin(),bosp.end());
    auto ip = BHObjectManager::GetInstance()->GetItemPool()->GetActive();
    collisions.insert(collisions.end(), ip.begin(),ip.end());
    
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
    // 충돌 매트릭스를 사용하여 두 레이어 간의 충돌 여부 결정
    // 각 매트릭스 항목은 충돌해야 하는 두 레이어를 정의함
    for (auto& entry : collisionMatrix)
    {
        // 두 레이어가 매트릭스 항목의 레이어와 일치하는지 확인
        // 비트 마스크를 사용하여 레이어 확인
        bool matchA = (layerA & entry.layer1) && (layerB & entry.layer2);
        bool matchB = (layerA & entry.layer2) && (layerB & entry.layer1);
        
        if (matchA || matchB)
        {
            return true;
        }
    }
    
    // 매트릭스에 정의되지 않은 레이어 조합은 충돌하지 않음
    return false;
}

void CircleCollisionManager::Render(HDC hdc)
{
    // collisions.clear();
    // collisions.push_back(BHObjectManager::GetInstance()->GetPlayer());
    // auto ep = BHObjectManager::GetInstance()->GetEnemyPool()->GetActive();
    // collisions.insert(collisions.end(), ep.begin(),ep.end());
    // auto ebp = BHObjectManager::GetInstance()->GetEnemyBulletPool()->GetActive();
    // collisions.insert(collisions.end(), ebp.begin(),ebp.end());
    // auto pbp = BHObjectManager::GetInstance()->GetPlayerBulletPool()->GetActive();
    // collisions.insert(collisions.end(), pbp.begin(),pbp.end());
    // auto bosp = BHObjectManager::GetInstance()->GetBossPool()->GetActive();
    // collisions.insert(collisions.end(), bosp.begin(),bosp.end());
    //
    //
    // for (size_t i = 0; i < collisions.size(); ++i)
    // {
    //     ICircleCollideable* objA = collisions[i];
    //
    //     if (objA == nullptr || objA->IsValid() == false) continue;
    //     
    //     //Debug
    //     D2DImage debugImage;
    //     debugImage.DrawCircle(
    //         {objA->GetPos()->x, objA->GetPos()->y},
    //         objA->GetHitRadius(),
    //         0, 1);
    // }
}
