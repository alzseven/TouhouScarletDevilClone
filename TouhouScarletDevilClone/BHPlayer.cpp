#include "BHPlayer.h"
#include "config.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "BHObjectManager.h"
#include "Shape.h"
#include "SoundPlayer.h"
#include "EffectPlayer.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "ShapeManager.h"
#include "BHEnemy.h"

void BHPlayer::Init(string shapeKey, FPOINT pos)
{
    BHObject::Init(shapeKey, pos);

    moveShape = ShapeManager::GetInstance()->FindShape("marisa_left");
    moveStartShape = ShapeManager::GetInstance()->FindShape("marisa_goleft");
    subShape = ShapeManager::GetInstance()->FindShape("marisa_sub");
    spellCardShape = ShapeManager::GetInstance()->FindShape("NormalBullet_blue"); // 임시로 사용
    
    timeElapsed = 0;
    // 딜레이 값을 파라미터로부터 초기화
    mainShootDelay = 0.6f;
    subShootDelay = 1.2f;
    moveDir = { 0,0 };
    isPreviousStateHorizontalMove = false;
    SetCollisionLayer(LAYER_PLAYER, LAYER_ENEMY_BULLET | LAYER_ITEM);
    
    // 플레이어 상태 초기화
    isInvincible = false;
    invincibleTimer = 0.0f;
    invincibleDuration = 2.0f;
    lives = 3;
    
    // 스펠카드(봄) 초기화
    isSpellCardActive = false;
    spellCardTimer = 0.0f;
    spellCardDuration = 5.0f; // 5초 지속
    spellCardCooldown = 30.0f; // 30초 쿨다운
    spellCardCooldownTimer = 0.0f;
    spellCardCount = 3; // 초기 스펠카드 3개
    
    // 게임 상태 초기화
    GameState* gameState = GameStateManager::GetInstance()->GetGameState();
    if (gameState) {
        gameState->PlayerHp = lives;
        gameState->CurrPowerBarFrame = 0;
        gameState->PowerMultiplier = 1.0f;
        gameState->SpellCardCount = spellCardCount;
    }
}

void BHPlayer::Render(HDC hdc)
{
    // 무적 상태일 때 깜빡이는 효과
    if (isInvincible && (int)(invincibleTimer * 10) % 2 == 0 && !isSpellCardActive) {
        return;
    }

    if (abs(moveDir.x) > FLT_EPSILON)
    {
        if (isPreviousStateHorizontalMove)
        {
            if (moveShape)
            {
                moveShape->GetImage()->Middle_RenderFrame(position.x, position.y,frameIndex,0, moveDir.x > 0);
            }
        }
        else
        {
            isPreviousStateHorizontalMove = true;
            // frameIndex = 0;
            if (moveStartShape)
            {
                moveStartShape->GetImage()->Middle_RenderFrame(position.x, position.y,frameIndex,0, moveDir.x > 0);
            }
        }

    }
    else
    {
        isPreviousStateHorizontalMove = false;
        if (shape && shape->GetImage())
        {
            // 프레임 인덱스 분리
            shape->GetImage()->Middle_RenderFrame(position.x, position.y, frameIndex);
        }
    }

    if (subShape)
    {
        subShape->GetImage()->Middle_RenderFrame((isPressingShift ? position.x - 10 : position.x - 30), (isPressingShift ? position.y - 15 : position.y), 1);
        subShape->GetImage()->Middle_RenderFrame((isPressingShift ? position.x + 10 : position.x + 30),(isPressingShift ? position.y - 15 : position.y), 1);
    }
    
    // 스펠카드 활성화 상태일 때 추가 렌더링
    if (isSpellCardActive) {
        RenderSpellCard(hdc);
    }
}

void BHPlayer::Move(FPOINT moveDirection, bool isPressingShift, float dt)
{
    if (abs(moveDirection.x) <= FLT_EPSILON && abs(moveDirection.y) <= FLT_EPSILON)
    {
        return;
    }
    float angle = atan2(moveDirection.x , moveDirection.y);
    
    // 속도 설정 - 쉬프트 키를 누르면 저속 이동
    float speed = isPressingShift ? 25.f : 50.f;
    Move(angle, speed, dt);
}

void BHPlayer::Move(float angle, float speed, float dt)
{
    position.x += sin(angle) * speed * dt;
    position.y += cos(angle) * speed * dt;
}

void BHPlayer::Update(float dt)
{
    mainWeaponTimer += dt;
    subWeaponTimer += dt;
    timeElapsed += dt;
    
    // 무적 상태 업데이트
    if (isInvincible) {
        invincibleTimer += dt;
        if (invincibleTimer >= invincibleDuration) {
            isInvincible = false;
            invincibleTimer = 0.0f;
        }
    }
    
    // 스펠카드 쿨다운 업데이트
    if (spellCardCooldownTimer > 0) {
        spellCardCooldownTimer -= dt;
        if (spellCardCooldownTimer < 0) {
            spellCardCooldownTimer = 0;
        }
    }
    
    // 스펠카드 활성화 상태 업데이트
    if (isSpellCardActive) {
        UpdateSpellCard(dt);
    }
    
    // 게임 상태 업데이트
    GameState* gameState = GameStateManager::GetInstance()->GetGameState();
    if (gameState) {
        gameState->PlayerHp = lives;
        gameState->SpellCardCount = spellCardCount;
    }
    
#pragma region ARROW_INPUT
    moveDir = { 0,0 };
    // UP
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP))
    {
        moveDir.y=-1;
    }
    // LEFT
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))
    {
        moveDir.x=-1;
    }
    // DOWN
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN))
    {
        moveDir.y=1;
    }
    // RIGHT
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
    {
        moveDir.x=1;
    }
#pragma endregion
    bool isPressingShift = KeyManager::GetInstance()->IsStayKeyDown(VK_SHIFT);
    
    Move(moveDir, isPressingShift, dt);
    
    MoveBackToBorder();

    frameIndex = frameIndex + 1 >= 4 ? 0 : frameIndex + 1;
    
    // Z키로 일반 공격
    if (KeyManager::GetInstance()->IsStayKeyDown(0x5A))
    {
        Shoot("Jewel_blue",{position.x , position.y - 10},DEG_TO_RAD(-90.f),DEG_TO_RAD(0.f),600.f,0.f);
        ShootSubWeapon(isPressingShift);
    }
    
    // X키로 스펠카드(봄) 사용
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58) && !isSpellCardActive && spellCardCooldownTimer <= 0 && spellCardCount > 0)
    {
        ActivateSpellCard();
    }
}

void BHPlayer::OnHit(ICollideable* hitObject)
{
    // 무적 상태일 때는 충돌 무시
    if (isInvincible || isSpellCardActive) {
        return;
    }
    
    // 충돌한 객체의 레이어 확인
    CollisionLayer hitLayer = hitObject->GetLayer();
    
    if (hitLayer & LAYER_ENEMY_BULLET) {
        // 적 총알과 충돌했을 때
        lives--;
        
        // 피격 효과음 재생
        // SoundPlayer::GetInstance()->SoundOn("player_hit");
        
        // 피격 이펙트 재생
        // EffectPlayer::GetInstance()->PlayEffect("hit_effect", position);
        
        // 무적 상태로 전환
        isInvincible = true;
        invincibleTimer = 0.0f;
        
        // 게임 오버 체크
        if (lives <= 0) {
            // 게임 오버 처리
            GameState* gameState = GameStateManager::GetInstance()->GetGameState();
            if (gameState) {
                gameState->isGameOver = true;
                gameState->PlayerHp = 0;
                
                // 게임 오버 효과음 재생
                // SoundPlayer::GetInstance()->SoundOn("game_over");
            }
        }
    }
    else if (hitLayer & LAYER_ITEM) {
        // 아이템과 충돌했을 때는 아이템의 OnHit에서 처리
        // 여기서는 추가 작업 필요 없음
    }
}

void BHPlayer::Shoot(string bulletShapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate)
{
    if (mainWeaponTimer >= mainShootDelay)
    {
        // 파워 배율에 따른 총알 속도 및 데미지 조정
        GameState* gameState = GameStateManager::GetInstance()->GetGameState();
        float powerMultiplier = 1.0f;
        if (gameState) {
            powerMultiplier = gameState->PowerMultiplier;
        }
        
        BHBullet* bullet = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
        bullet->Init(bulletShapeKey, init_pos, true);
        bullet->Launch(angle, angleRate, shootSpeed * powerMultiplier, shootSpeedRate);
        mainWeaponTimer = 0.f;
        
        // 발사 효과음 재생
        // SoundPlayer::GetInstance()->SoundOn("player_shoot");
    }
}

void BHPlayer::ShootSubWeapon(bool isAccumulating)
{
    if (subWeaponTimer >= subShootDelay)
    {
        // 파워 배율에 따른 총알 속도 및 데미지 조정
        GameState* gameState = GameStateManager::GetInstance()->GetGameState();
        float powerMultiplier = 1.0f;
        if (gameState) {
            powerMultiplier = gameState->PowerMultiplier;
        }
        
        BHBullet* bullet1 = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
        bullet1->Init("EllipseBullet_green",{isAccumulating ? position.x - 10 : position.x - 30,isAccumulating ? position.y - 15 : position.y }, true);
        bullet1->Launch(DEG_TO_RAD(-90.f),DEG_TO_RAD(0.f), 300.f * powerMultiplier, 0.f);

        BHBullet* bullet2 = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
        bullet2->Init("EllipseBullet_green",{isAccumulating ? position.x + 10 : position.x + 30,isAccumulating ? position.y - 15 : position.y }, true);
        bullet2->Launch(DEG_TO_RAD(-90.f),DEG_TO_RAD(0.f), 300.f * powerMultiplier, 0.f);
        subWeaponTimer = 0.f;
        
        // 발사 효과음 재생
        // SoundPlayer::GetInstance()->SoundOn("player_sub_shoot");
    }
}

void BHPlayer::MoveBackToBorder() {
    if (shape == nullptr) return;

    const float width = shape->GetImage()->GetWidth() / shape->GetImage()->GetMaxFrameX();
    const float height = shape->GetImage()->GetHeight() / shape->GetImage()->GetMaxFrameY();

    const float right = position.x + width / 2;
    const float left = position.x - width / 2;
    const float top = position.y - height / 2;
    const float bottom = position.y + height / 2;

    if (left < GAME_LEFT) position.x = GAME_LEFT + width / 2;
    if (right > GAME_RIGHT) position.x = GAME_RIGHT - width / 2;
    if (top < GAME_TOP) position.y = GAME_TOP + height / 2;
    if (bottom > GAME_BOTTOM) position.y = GAME_BOTTOM - height / 2;
}

// 스펠카드(봄) 활성화
void BHPlayer::ActivateSpellCard()
{
    if (spellCardCount <= 0) return;
    
    isSpellCardActive = true;
    spellCardTimer = 0.0f;
    spellCardCount--;
    
    // 스펠카드 사용 효과음 재생
    // SoundPlayer::GetInstance()->SoundOn("spell_card_declare");
    
    // 스펠카드 이펙트 재생
    // EffectPlayer::GetInstance()->PlayEffect("spell_card_effect", position);
    
    // 화면의 모든 적 탄막 제거
    ClearEnemyBullets();
    
    // 무적 상태로 전환
    isInvincible = true;
    invincibleTimer = 0.0f;
    
    // 게임 상태 업데이트
    GameState* gameState = GameStateManager::GetInstance()->GetGameState();
    if (gameState) {
        gameState->SpellCardCount = spellCardCount;
    }
}

// 스펠카드 상태 업데이트
void BHPlayer::UpdateSpellCard(float dt)
{
    spellCardTimer += dt;
    
    // 주변 적에게 데미지
    DamageNearbyEnemies(dt);
    
    // 지속 시간이 끝나면 비활성화
    if (spellCardTimer >= spellCardDuration) {
        isSpellCardActive = false;
        isInvincible = false;
        invincibleTimer = 0.0f;
        
        // 쿨다운 시작
        spellCardCooldownTimer = spellCardCooldown;
    }
}

// 스펠카드 렌더링
void BHPlayer::RenderSpellCard(HDC hdc)
{
    // 스펠카드 이펙트 렌더링 (원형 파동 효과)
    if (spellCardShape && spellCardShape->GetImage()) {
        float scale = 1.0f + spellCardTimer * 5.0f; // 시간에 따라 확장
        float alpha = 1.0f - (spellCardTimer / spellCardDuration); // 시간에 따라 투명해짐
        
        // 원형 이펙트 렌더링
        spellCardShape->GetImage()->Middle_Render(position.x, position.y, scale, scale, alpha);
    }
}

// 적 탄막 제거
void BHPlayer::ClearEnemyBullets()
{
    // 화면의 모든 적 탄막 제거
    BHObjectManager::GetInstance()->ClearEnemyBullets();
    
    // 탄막 제거 효과음 재생
    // SoundPlayer::GetInstance()->SoundOn("bullet_clear");
    
    // 탄막 제거 이펙트 재생
    // EffectPlayer::GetInstance()->PlayEffect("bullet_clear_effect", position);
}

// 주변 적에게 데미지
void BHPlayer::DamageNearbyEnemies(float dt)
{
    // 화면의 모든 적에게 데미지
    vector<BHEnemy*>& enemies = BHObjectManager::GetInstance()->GetEnemyPool()->GetActive();
    for (auto enemy : enemies) {
        if (enemy && enemy->IsValid()) {
            // 보스는 초당 10 데미지, 일반 적은 초당 20 데미지
            int damage = dynamic_cast<BHBoss*>(enemy) ? 10 * dt : 20 * dt;
            enemy->GetDamaged(damage);
            
            // 데미지 이펙트 재생 (간헐적으로)
            if ((int)(spellCardTimer * 5) % 2 == 0) {
                // EffectPlayer::GetInstance()->PlayEffect("damage_effect", *enemy->GetPos());
            }
        }
    }
}

void BHPlayer::Release()
{
    // if (bulletManager)
    // {
    //     bulletManager->Release();
    //     delete bulletManager;
    // }
}
