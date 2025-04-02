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
    // for test
    // patterns[0] = new MoveStraightDirectionPattern();
    // patterns[0]->SetTarget(target);
    // patterns[0]->SetPatternStartTime(0.f);
    // patterns[0]->SetPatternEndTime(5.f);
    // patterns[0]->Launch(50.f,0.f,DEG_TO_RAD(-60.f),DEG_TO_RAD(0.f));

    // patterns[1] = new MoveStraightDirectionPattern();
    // patterns[1]->SetTarget(target);
    // patterns[1]->SetPatternStartTime(6.f);
    // patterns[1]->SetPatternEndTime(10.f);
    // patterns[1]->Launch(25.f,0.f,DEG_TO_RAD(60.f),DEG_TO_RAD(0.f));

    // patterns[2] = new ShootStraightPattern();
    // patterns[2]->SetTarget(target);
    // patterns[2]->SetPatternStartTime(6.f);
    // patterns[2]->SetPatternEndTime(10.f);
    // patterns[2]->SetShootParams(1.f, 5, DEG_TO_RAD(90.f));

    patterns[0] = new ShootStraightPattern();
    patterns[0]->SetTarget(target);
    patterns[0]->SetPatternStartTime(0.f);
    patterns[0]->SetPatternEndTime(5.f);
    patterns[0]->SetShootParams(1.f, 5, 0.2f, DEG_TO_RAD(90.f), 0.f, 50.f, 0.f);
    
    patterns[1] = new ShootRoundPattern();
    patterns[1]->SetTarget(target);
    patterns[1]->SetPatternStartTime(6.f);
    patterns[1]->SetPatternEndTime(10.f);
    patterns[1]->SetShootParams(2.f, 5, 0.f, DEG_TO_RAD(-90.f), 0.f, 70.f, 0.f);
    
    patterns[2] = new ShootSpreadPattern();
    patterns[2]->SetTarget(target);
    patterns[2]->SetPatternStartTime(6.f);
    patterns[2]->SetPatternEndTime(999.f);
    patterns[2]->SetShootParams(1.f, 10, 0.f, DEG_TO_RAD(135.f), DEG_TO_RAD(-5.f), 90.f, 0.f);


    // patterns[3] = new MoveStraightDirectionPattern();
    // patterns[3]->SetTarget(target);
    // patterns[3]->SetPatternStartTime(11.f);
    // patterns[3]->SetPatternEndTime(15.f);
    // patterns[3]->Launch(60.f,0.f,DEG_TO_RAD(-180.f),DEG_TO_RAD(0.f));

    actions.push(patterns[0]);
    actions.push(patterns[1]);
    actions.push(patterns[2]);
    // actions.push(patterns[3]);
}

void EnemyController::Update(float dt)
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
