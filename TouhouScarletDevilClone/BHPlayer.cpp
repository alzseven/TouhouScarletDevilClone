#include "BHPlayer.h"
#include "config.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "BHObjectManager.h"
#include "Shape.h"
#include "SoundPlayer.h"
#include "EffectPlayer.h"
#include "GameState.h"
#include "ShapeManager.h"
#include "BHEnemy.h"

void BHPlayer::Init(string shapeKey, FPOINT pos)
{
    BHObject::Init(shapeKey, pos);

    moveShape = ShapeManager::GetInstance()->FindShape("marisa_left");
    moveStartShape = ShapeManager::GetInstance()->FindShape("marisa_goleft");
    subShape = ShapeManager::GetInstance()->FindShape("marisa_sub");
    
    timeElapsed = 0;
    //TODO: Initialize delay in certain value from parameter

    moveSpeed = 130.f;
    slowSpeed = 60.f;
    lv = 5;
    //µô·¹ÀÌ
    mainShootDelay[0] = 0.2f;
    mainShootDelay[1] = 0.2;
    mainShootDelay[2] = 0.2;
    mainShootDelay[3] = 0.15;
    mainShootDelay[4] = 0.15;
    mainShootDelay[5] = 0.15;
    mainShootDelay[6] = 0.15;
    mainShootDelay[7] = 0.15;
    mainShootDelay[8] = 0.15;

    subShootDelay[0] = 0.0f;
    subShootDelay[1] = 0.8f;
    subShootDelay[2] = 0.6f;
    subShootDelay[3] = 0.6;
    subShootDelay[4] = 0.5;
    subShootDelay[5] = 0.5;
    subShootDelay[6] = 0.3;
    subShootDelay[7] = 0.3;
    subShootDelay[8] = 0.3;

    //°¹¼ö
    mainShootCount[0] = 1;
    mainShootCount[1] = 1;
    mainShootCount[2] = 1;
    mainShootCount[3] = 1;
    mainShootCount[4] = 1;
    mainShootCount[5] = 2;
    mainShootCount[6] = 2;
    mainShootCount[7] = 2;
    mainShootCount[8] = 3;

    subShootCount[0] = 0;
    subShootCount[1] = 1;
    subShootCount[2] = 1;
    subShootCount[3] = 1;
    subShootCount[4] = 1;
    subShootCount[5] = 1;
    subShootCount[6] = 1;
    subShootCount[7] = 2;
    subShootCount[8] = 2;

    spellCardShape = ShapeManager::GetInstance()->FindShape("NormalBullet_blue"); // ????ë¡? ?¬ì??
    
    timeElapsed = 0;
    
    moveDir = { 0,0 };
    isPreviousStateHorizontalMove = false;
    SetCollisionLayer(LAYER_PLAYER, LAYER_ENEMY_BULLET | LAYER_ITEM);
    
    // ?????´ì?? ???? ì´?ê¸°í??
    isInvincible = false;
    invincibleTimer = 0.0f;
    invincibleDuration = 2.0f;
    lives = 5;
    
    // ?¤í??ì¹´ë??(ë´?) ì´?ê¸°í??
    isSpellCardActive = false;
    spellCardTimer = 0.0f;
    spellCardDuration = 5.0f; // 5ì´? ì§???
    spellCardCooldown = 6.0f; // 30ì´? ì¿¨ë?¤ì??
    spellCardCooldownTimer = 0.0f;
    spellCardCount = 3; // ì´?ê¸? ?¤í??ì¹´ë?? 3ê°?
    
    // ê²??? ???? ì´?ê¸°í??
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
    // ë¬´ì?? ?????? ?? ê¹?ë¹¡ì?´ë?? ?¨ê³¼
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
            if (frameIndex == 3) isPreviousStateHorizontalMove = true;
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
            // ?????? ?¸ë?±ì?? ë¶?ë¦?
            shape->GetImage()->Middle_RenderFrame(position.x, position.y, frameIndex);
        }
    }

    if (subShape)
    {
        subShape->GetImage()->Middle_RenderFrame((isPressingShift ? position.x - 10 : position.x - 30), (isPressingShift ? position.y - 15 : position.y), 1);
        subShape->GetImage()->Middle_RenderFrame((isPressingShift ? position.x + 10 : position.x + 30),(isPressingShift ? position.y - 15 : position.y), 1);
    }
    
    // ?¤í??ì¹´ë?? ???±í?? ?????? ?? ì¶?ê°? ????ë§?
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
    
    //TODO: SetSpeed;
    float currentSpeed = isPressingShift ? slowSpeed : moveSpeed;
    position.x += sin(angle) * currentSpeed * dt;
    position.y += cos(angle) * currentSpeed * dt;
}

void BHPlayer::Move(float angle, float speed, float dt)
{
    position.x += sin(angle) * speed * dt;
    position.y += cos(angle) * speed * dt;
}

void BHPlayer::Update(float dt)
{
    setLV(GameStateManager::GetInstance()->GetGameState()->CurrPowerBarFrame);
    mainWeaponTimer += dt;
    subWeaponTimer += dt;
    timeElapsed += dt;

    // ë¬´ì?? ???? ???°ì?´í??
    if (isInvincible) {
        invincibleTimer += dt;
        if (invincibleTimer >= invincibleDuration) {
            isInvincible = false;
            invincibleTimer = 0.0f;
        }
    }
    
    // ?¤í??ì¹´ë?? ì¿¨ë?¤ì?? ???°ì?´í??
    if (spellCardCooldownTimer > 0) {
        spellCardCooldownTimer -= dt;
        if (spellCardCooldownTimer < 0) {
            spellCardCooldownTimer = 0;
        }
    }
    
    // ?¤í??ì¹´ë?? ???±í?? ???? ???°ì?´í??
    if (isSpellCardActive) {
        UpdateSpellCard(dt);
    }
    
    // ê²??? ???? ???°ì?´í??
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
    isPressingShift = KeyManager::GetInstance()->IsStayKeyDown(VK_SHIFT);
    
    Move(moveDir, isPressingShift, dt);
    
    MoveBackToBorder();

    if (timeElapsed >= 0.5f)
    {
        frameIndex = frameIndex + 1 >= 4 ? 0 : frameIndex + 1;
        timeElapsed = 0;
    }
    
    // Z?¤ë? ?¼ë? ê³µê²©
    if (KeyManager::GetInstance()->IsStayKeyDown(0x5A))
    {
        
        Shoot("marisa_mainbullet", { position.x , position.y - 10 }, DEG_TO_RAD(-90), DEG_TO_RAD(0.f), 600.f, 0.f);
        
        
        ShootSubWeapon(isPressingShift);
    }
    
    // X?¤ë? ?¤í??ì¹´ë??(ë´?) ?¬ì??
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58) && !isSpellCardActive && spellCardCooldownTimer <= 0 && spellCardCount > 0)
    {
        ActivateSpellCard();
    }
}

void BHPlayer::OnHit(ICollideable* hitObject)
{
    // ë¬´ì?? ?????? ???? ì¶©ë?? ë¬´ì??
    if (isInvincible || isSpellCardActive) {
        return;
    }
    
    // ì¶©ë???? ê°?ì²´ì?? ???´ì?? ????
    CollisionLayer hitLayer = hitObject->GetLayer();
    
    if (hitLayer & LAYER_ENEMY_BULLET) {
        // ?? ì´???ê³? ì¶©ë?????? ??
        lives--;
        
        // ?¼ê²© ?¨ê³¼?? ?¬ì??
         SoundPlayer::GetInstance()->SoundOn("player_dead");
        
        // ?¼ê²© ?´í???? ?¬ì??
        // EffectPlayer::GetInstance()->PlayEffect("hit_effect", position);
        
        // ë¬´ì?? ????ë¡? ????
        isInvincible = true;
        invincibleTimer = 0.0f;
        
        // ê²??? ?¤ë? ì²´í??
        if (lives <= 0) {
            // ê²??? ?¤ë? ì²?ë¦?
            GameState* gameState = GameStateManager::GetInstance()->GetGameState();
            if (gameState) {
                gameState->isGameOver = true;
                gameState->PlayerHp = 0;
                
                // ê²??? ?¤ë? ?¨ê³¼?? ?¬ì??
                SoundPlayer::GetInstance()->SoundOn("player_dead");
                EffectPlayer::GetInstance()->PlayEffect("Boss_phase", position);
            }
        }
    }
    else if (hitLayer & LAYER_ITEM) {
        // ???´í??ê³? ì¶©ë?????? ???? ???´í???? OnHit???? ì²?ë¦?
        // ?¬ê¸°???? ì¶?ê°? ???? ???? ????
    }
}

void BHPlayer::Shoot(string bulletShapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate)
{
    if (mainWeaponTimer >= mainShootDelay[lv])
    {
        float shootAngle = 0;
        SoundPlayer::GetInstance()->SoundOn("player_shoot");
        for (int i = 0; i < mainShootCount[lv]; i++)
        {
            BHBullet* bullet = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
            bullet->Init(bulletShapeKey, init_pos, true);
            if (mainShootCount[lv] % 2 == 0) shootAngle = -90 + (i - mainShootCount[lv] / 2 + 0.5f) * 3.0f;
            else shootAngle = -90 + (i - mainShootCount[lv] / 2) * 3.0f;
            bullet->Launch(DEG_TO_RAD(shootAngle), angleRate, shootSpeed, shootSpeedRate);
        }
        mainWeaponTimer = 0.f;
        
        // ë°??? ?¨ê³¼?? ?¬ì??
        // SoundPlayer::GetInstance()->SoundOn("player_shoot");
    }
}

void BHPlayer::ShootSubWeapon(bool isAccumulating)
{
    if (subWeaponTimer >= subShootDelay[lv])
    {

        float shootAngle = 0;
        for (int i = 0; i < subShootCount[lv]; i++)
        {
            if (subShootCount[lv] % 2 == 0) shootAngle = -90 + (i - subShootCount[lv] / 2 + 0.5f) * 3.0f;
            else shootAngle = -90 + (i - subShootCount[lv] / 2) * 3.0f;
            BHBullet* bullet1 = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
            bullet1->Init("marisa_subbullet", { isAccumulating ? position.x - 10 : position.x - 30,isAccumulating ? position.y - 15 : position.y }, true);
            bullet1->Launch(DEG_TO_RAD(shootAngle), DEG_TO_RAD(0.f), 500.f, 0.f);
            BHBullet* bullet2 = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
            bullet2->Init("marisa_subbullet", { isAccumulating ? position.x + 10 : position.x + 30,isAccumulating ? position.y - 15 : position.y }, true);
            bullet2->Launch(DEG_TO_RAD(shootAngle), DEG_TO_RAD(0.f), 500.f, 0.f);
            subWeaponTimer = 0.f;
        }
        
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

// ?¤í??ì¹´ë??(ë´?) ???±í??
void BHPlayer::ActivateSpellCard()
{
    if (spellCardCount <= 0) return;
    
    isSpellCardActive = true;
    spellCardTimer = 0.0f;
    spellCardCount--;
    EffectPlayer::GetInstance()->PlayEffect("marisa_bomb", position);
    // ?¤í??ì¹´ë?? ?¬ì?? ?¨ê³¼?? ?¬ì??
    // SoundPlayer::GetInstance()->SoundOn("spell_card_declare");
    
    // ?¤í??ì¹´ë?? ?´í???? ?¬ì??
    // EffectPlayer::GetInstance()->PlayEffect("spell_card_effect", position);
    
    // ??ë©´ì?? ëª¨ë?? ?? ??ë§? ??ê±?
    ClearEnemyBullets();
    
    // ë¬´ì?? ????ë¡? ????
    isInvincible = true;
    invincibleTimer = 0.0f;
    
    // ê²??? ???? ???°ì?´í??
    GameState* gameState = GameStateManager::GetInstance()->GetGameState();
    if (gameState) {
        gameState->SpellCardCount = spellCardCount;
    }
}

// ?¤í??ì¹´ë?? ???? ???°ì?´í??
void BHPlayer::UpdateSpellCard(float dt)
{
    spellCardTimer += dt;
    
    // ì£¼ë? ????ê²? ?°ë?¸ì?
    DamageNearbyEnemies(dt);
    
    // ì§??? ??ê°??? ????ë©? ë¹????±í??
    if (spellCardTimer >= spellCardDuration) {
        isSpellCardActive = false;
        isInvincible = false;
        invincibleTimer = 0.0f;
        
        // ì¿¨ë?¤ì?? ????
        spellCardCooldownTimer = spellCardCooldown;
    }
}

// ?¤í??ì¹´ë?? ????ë§?
void BHPlayer::RenderSpellCard(HDC hdc)
{
    // ?¤í??ì¹´ë?? ?´í???? ????ë§? (???? ???? ?¨ê³¼)
    if (spellCardShape && spellCardShape->GetImage()) {
        float scale = 1.0f + spellCardTimer * 5.0f; // ??ê°??? ?°ë?? ????
        float alpha = 1.0f - (spellCardTimer / spellCardDuration); // ??ê°??? ?°ë?? ?¬ë??´ì?
        
        // ???? ?´í???? ????ë§?
        spellCardShape->GetImage()->Middle_Render(position.x, position.y, scale, scale, alpha);
    }
}

// ?? ??ë§? ??ê±?
void BHPlayer::ClearEnemyBullets()
{
    // ??ë©´ì?? ëª¨ë?? ?? ??ë§? ??ê±?
    BHObjectManager::GetInstance()->ClearEnemyBullets();
    
    // ??ë§? ??ê±? ?¨ê³¼?? ?¬ì??
    // SoundPlayer::GetInstance()->SoundOn("bullet_clear");
    
    // ??ë§? ??ê±? ?´í???? ?¬ì??
    // EffectPlayer::GetInstance()->PlayEffect("bullet_clear_effect", position);
}

// ì£¼ë? ????ê²? ?°ë?¸ì?
void BHPlayer::DamageNearbyEnemies(float dt)
{
    // ??ë©´ì?? ëª¨ë?? ????ê²? ?°ë?¸ì?
    vector<BHEnemy*>& enemies = BHObjectManager::GetInstance()->GetEnemyPool()->GetActive();
    for (auto enemy : enemies) {
        if (enemy && enemy->IsValid()) {
            // ë³´ì?¤ë?? ì´??? 10 ?°ë?¸ì?, ?¼ë? ???? ì´??? 20 ?°ë?¸ì?
            int damage = dynamic_cast<BHBoss*>(enemy) ? 10 * dt : 20 * dt;
            enemy->GetDamaged(damage);
            
            // ?°ë?¸ì? ?´í???? ?¬ì?? (ê°??????¼ë?)
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


void BHPlayer::setLV(int power)
{
    if (power >= 128) lv = 8;
    else if (power >= 96) lv = 7;
    else if (power >= 80) lv = 6;
    else if (power >= 64) lv = 5;
    else if (power >= 48) lv = 4;
    else if (power >= 32) lv = 3;
    else if (power >= 16) lv = 2;
    else if (power >= 8) lv = 1;
    else lv = 0;
}
