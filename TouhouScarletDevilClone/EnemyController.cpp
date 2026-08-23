#include "EnemyController.h"

#include "BHObject.h"
#include "IObjectActionPattern.h"

EnemyController::~EnemyController()
{
    while (!actions.empty())
    {
        delete actions.front();
        actions.pop();
    }

    for (auto* action : enabledActions)
        delete action;

    enabledActions.clear();
}

void EnemyController::Init()
{
    timeElapsed = 0;
}

// 기존 코드 대체 부분
void EnemyController::Update(float dt)
// {
//     currentTime += dt;
//     
//     // 활성 패턴 관리
//     activePatterns.erase(
//         std::remove_if(activePatterns.begin(), activePatterns.end(),
//             [](auto* p) { return p->IsExpired(); }),
//         activePatterns.end()
//     );
//     
//     // 새 패턴 활성화
//     for (auto& entry : patternTimeline) {
//         if (!entry.isActive && 
//             currentTime >= entry.startTime &&
//             currentTime <= (entry.startTime + entry.duration)) {
//             activePatterns.push_back(entry.pattern.get());
//             entry.isActive = true;
//             }
//     }
//     
//     // 모든 활성 패턴 업데이트
//     for (auto* pattern : activePatterns) {
//         pattern->Update(dt);
//     }
// }

{
    timeElapsed += dt;
    // if (actions.empty() == false)
    // {
    //     if (timeElapsed >= actions.front()->GetPatternStartTime())
    //     {
    //         AddPatternToTarget(actions.front());
    //         actions.pop();
    //     }
    // }

    // Add new patterns
    while (!actions.empty() && timeElapsed >= actions.front()->GetPatternStartTime()) {
        enabledActions.push_back(actions.front());
        actions.pop();
    }
    
    // Update and remove expired
    for (auto it = enabledActions.begin(); it != enabledActions.end();)
    {
        IObjectActionPattern* pattern = *it;

        pattern->Update(dt);

        if (pattern->IsExpired())
        {
            it = enabledActions.erase(it);
            delete pattern;
        }
        else
        {
            ++it;
        }
    }
    
}