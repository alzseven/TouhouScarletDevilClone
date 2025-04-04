#pragma once
#include "config.h"
#include "BHObject.h"

class Image;
class D2DImage;

class BHPlayer : public BHObject
{
    int frameIndex;


    float mainWeaponTimer;
    float subWeaponTimer;

    float timeElapsed;
    float mainShootDelay[9];
    float subShootDelay[9];
    int mainShootCount[9];
    int subShootCount[9];
    float moveSpeed;
    float slowSpeed;

    int lv;

    Shape* moveShape;
    Shape* moveStartShape;
    Shape* subShape;

    bool isPreviousStateHorizontalMove;

    FPOINT moveDir;
    bool isPressingShift;

public:
    // »ý¼ºÀÚ
    BHPlayer() = default;
    ~BHPlayer() override = default;


    Shape* spellCardShape; // 스펠카드 이펙트 이미지


    bool isInvincible;
    float invincibleTimer;
    float invincibleDuration;
    int lives;

    // 스펠카드(봄) 관련 변수
    bool isSpellCardActive; // 스펠카드 활성화 상태
    float spellCardTimer; // 스펠카드 지속 시간 타이머
    float spellCardDuration; // 스펠카드 지속 시간
    float spellCardCooldown; // 스펠카드 쿨다운 시간
    float spellCardCooldownTimer; // 스펠카드 쿨다운 타이머
    int spellCardCount; // 남은 스펠카드 수


    void Init(string shapeKey, FPOINT pos) override;

    //TODO:
    virtual void Move(FPOINT moveDirection, bool isPressingShift, float dt);

    void Move(float angle, float speed, float dt) override;
    void Render(HDC hdc) override;

    void MoveBackToBorder();

    void Update(float dt) override;

    void OnHit(ICollideable* hitObject) override;

    void Shoot(string bulletShapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed,
               float shootSpeedRate) override;

    void ShootSubWeapon(bool isAccumulating);

    // 스펠카드(봄) 관련 함수
    void ActivateSpellCard(); // 스펠카드 활성화
    void UpdateSpellCard(float dt); // 스펠카드 상태 업데이트
    void RenderSpellCard(HDC hdc); // 스펠카드 렌더링
    void ClearEnemyBullets(); // 적 탄막 제거
    void DamageNearbyEnemies(float dt); // 주변 적에게 데미지

    // 스펠카드 상태 확인 함수
    inline bool IsSpellCardActive() const { return isSpellCardActive; }
    inline float GetSpellCardCooldownRatio() const { return spellCardCooldownTimer / spellCardCooldown; }
    inline int GetSpellCardCount() const { return spellCardCount; }

    void Release() override;

    inline int GetLV() { return lv; }
    void setLV(int power);
};
