#include "BHObjectManager.h"

#include "ItemType.h"
#include "PowerUpItem.h"
#include "ScoreItem.h"

void BHObjectManager::Init()
{
    enemyBulletPool.Init(2000);
    playerBulletPool.Init(1000);
    enemyPool.Init(50);
    bossPool.Init(5);
    items.reserve(50);
}

void BHObjectManager::Update(float dt)
{
    player.Update(dt);
    
    for (std::vector<BHEnemy*>::iterator iter = enemyPool.GetUpdateView().begin(); iter != enemyPool.GetUpdateView().end(); ++iter)
    {
        (*iter)->Update(dt);
    }

    for (std::vector<BHBullet*>::iterator iter = enemyBulletPool.GetUpdateView().begin(); iter != enemyBulletPool.GetUpdateView().end(); ++iter)
    {
        (*iter)->Update(dt);
    }

    for (std::vector<BHBullet*>::iterator iter = playerBulletPool.GetUpdateView().begin(); iter != playerBulletPool.GetUpdateView().end(); ++iter)
    {
        (*iter)->Update(dt);
    }
    for (std::vector<BHBoss*>::iterator iter = bossPool.GetUpdateView().begin(); iter != bossPool.GetUpdateView().end(); ++iter)
    {
        (*iter)->Update(dt);
    }
    for (auto iter = items.begin(); iter != items.end(); ++iter)
    {
        if (*iter && (*iter)->IsValid())
        {
            (*iter)->Update(dt);
        }

    }
}

void BHObjectManager::Release()
{
    enemyPool.Clear();
    enemyBulletPool.Clear();
    playerBulletPool.Clear();
    bossPool.Clear();
    
    for (BHItem* item : items)
    {
        delete item;
    }

    items.clear();
    
    ReleaseInstance();
}

void BHObjectManager::Render()
{
    player.Render(NULL);
    
    for (std::vector<BHEnemy*>::iterator iter = enemyPool.GetActive().begin(); iter != enemyPool.GetActive().end(); ++iter)
    {
        (*iter)->Render(NULL);
    }

    for (std::vector<BHBullet*>::iterator iter = enemyBulletPool.GetActive().begin(); iter != enemyBulletPool.GetActive().end(); ++iter)
    {
        (*iter)->Render(NULL);
    }

    for (std::vector<BHBullet*>::iterator iter = playerBulletPool.GetActive().begin(); iter != playerBulletPool.GetActive().end(); ++iter)
    {
        (*iter)->Render(NULL);
    }

    for (std::vector<BHBoss*>::iterator iter = bossPool.GetActive().begin(); iter != bossPool.GetActive().end(); ++iter)
    {
        (*iter)->Render(NULL);
    }
    for (auto iter = items.begin(); iter != items.end(); ++iter)
    {
        if (*iter && (*iter)->IsValid())
        {
            (*iter)->Render(NULL);
        }
    }
}

void BHObjectManager::Cleanup()
{
    std::vector<BHBullet*> deadPlayerBullets;
    for (auto* bullet : playerBulletPool.GetActive())
    {
        if (!bullet->IsValid())
            deadPlayerBullets.push_back(bullet);
    }
    for (auto* bullet : deadPlayerBullets)
    {
        bullet->ResetForReuse();
        playerBulletPool.Release(bullet);
    }
    
    std::vector<BHBullet*> deadEnemyBullets;
    for (auto* bullet : enemyBulletPool.GetActive())
    {
        if (!bullet->IsValid())
            deadEnemyBullets.push_back(bullet);
    }
    for (auto* bullet : deadEnemyBullets)
    {
        bullet->ResetForReuse();
        enemyBulletPool.Release(bullet);
    }
    
    std::vector<BHEnemy*> deadEnemies;

    for (BHEnemy* enemy : enemyPool.GetActive())
    {
        if (enemy && !enemy->IsValid())
            deadEnemies.push_back(enemy);
    }

    for (BHEnemy* enemy : deadEnemies)
    {
        if (enemy->IsDropPending())
        {
            ScoreItem* scItem; //= new ScoreItem();
            PowerUpItem* pwItem; //= new PowerUpItem();
            switch (enemy->GetItemType())
            {
            case ItemType::Point:
                scItem = new ScoreItem();
                scItem->Init("smallScore", *enemy->GetPos());
                scItem->InitGameState(GameStateManager::GetInstance()->GetGameState());
                items.push_back(scItem);
                enemy->ResetDropPending();
                break;
            case ItemType::Power:
                pwItem = new PowerUpItem();
                pwItem->Init("smallPower", *enemy->GetPos());
                pwItem->InitGameState(GameStateManager::GetInstance()->GetGameState());
                items.push_back(pwItem);
                enemy->ResetDropPending();
                break;
            case ItemType::None:
                // break;
            default: 
                break;
            }
        }
        
        enemy->CleanUpActiveSession();
        enemyPool.Release(enemy);
    }
    
    std::vector<BHBoss*> deadBosses;
    
    for (BHBoss* boss : bossPool.GetActive())
    {
        if (boss && !boss->IsValid())
            deadBosses.push_back(boss);
    }

    for (BHBoss* boss : deadBosses)
    {
        boss->CleanUpActiveSession();
        bossPool.Release(boss);
    }
    
    for (auto it = items.begin(); it != items.end();)
    {
        BHItem* item = *it;

        if (item == nullptr || !item->IsValid())
        {
            it = items.erase(it);
            delete item;
        }
        else
        {
            ++it;
        }
    }
    
    enemyPool.RefreshUpdateView();
    enemyBulletPool.RefreshUpdateView();
    playerBulletPool.RefreshUpdateView();
    bossPool.RefreshUpdateView();
}

void BHObjectManager::ClearEnemyBullets()
{
    for (auto* bullet : enemyBulletPool.GetActive())
    {
        if (bullet && bullet->IsValid())
            bullet->DeActivate();
    }
}

void BHObjectManager::ClearItems()
{
    for (BHItem* item : items)
    {
        delete item;
    }

    items.clear();
}

void BHObjectManager::CleanupActiveSession()
{
    vector<BHEnemy*> eSnapshot = enemyPool.GetActive();

    for (auto* enemy : eSnapshot)
    {
        enemy->CleanUpActiveSession();
        enemy->ResetDropPending();
        enemyPool.Release(enemy);
    }

    vector<BHBoss*> bSnapshot = bossPool.GetActive();

    for (auto* boss : bSnapshot)
    {
        boss->CleanUpActiveSession();
        bossPool.Release(boss);
    }

    vector<BHBullet*> pbSnapshot = playerBulletPool.GetActive();

    for (auto* pb : pbSnapshot)
    {
        pb->DeActivate();
        pb->ResetForReuse();
        playerBulletPool.Release(pb);
    }

    vector<BHBullet*> ebSnapshot = enemyBulletPool.GetActive();

    for (auto* eb : ebSnapshot)
    {
        eb->DeActivate();
        eb->ResetForReuse();
        enemyBulletPool.Release(eb);
    }
    
    for (BHItem* item : items)
    {
        delete item;
    }

    items.clear();
    
    enemyPool.RefreshUpdateView();
    bossPool.RefreshUpdateView();
    playerBulletPool.RefreshUpdateView();
    enemyBulletPool.RefreshUpdateView();
}

// void PoolManager::PauseAll()
// {
//     
// }
