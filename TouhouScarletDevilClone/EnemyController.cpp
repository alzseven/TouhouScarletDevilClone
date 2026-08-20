#include "EnemyController.h"

#include "BHObject.h"
#include "IObjectActionPattern.h"

EnemyController::EnemyController()
{
}

EnemyController::~EnemyController()
{
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
        enabledActions.push_back(std::move(actions.front()));
        actions.pop();
    }
    
    // for (std::vector<IObjectActionPattern*>::iterator iter = enabledActions.begin(); iter != enabledActions.end(); ++iter)
    // {
    //     (*iter)->Update(dt);
    // }
    
    // Update and remove expired
    enabledActions.erase(
        std::remove_if(enabledActions.begin(), enabledActions.end(),
            [dt](const auto& pattern) {
                pattern->Update(dt);
                return pattern->IsExpired();
            }),
        enabledActions.end()
    );
    
}

void EnemyController::AddPatternToTarget(IObjectActionPattern* newPattern)
{
    enabledActions.push_back(newPattern);
    // target->AddAction(newPattern);
    // target->AddPa
}

// void EnemyController::