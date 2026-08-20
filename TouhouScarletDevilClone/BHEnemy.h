#pragma once
#include "BHObject.h"
#include "BHItem.h"
#include "ItemType.h"

class EnemyController;
class BulletManager;
class D2DImage;
enum class ItemType;
class BHEnemy : public BHObject
{
private:
    int frameIndex;
    float timeElapsed;
    float shootDelay;

    int tempLevel;
    D2DImage* moveImage;
    FPOINT moveDir;
	
    // 아이템 관련 코드
    // std::vector<BHItem*> item; // = nullptr;
	// GameState* gameState = nullptr;

	bool isDropPending = false;
	ItemType itemType = ItemType::None;
	
protected:
	EnemyController* ec = nullptr;
	
public:
    // 생성자
    BHEnemy() = default;
    virtual ~BHEnemy (); // = default;

    inline void SetMoveImage(D2DImage* moveImage) { this->moveImage = moveImage; }

    void Init(string shapeKey, FPOINT pos) override;
    virtual void Init(string shapeKey, FPOINT pos, std::vector<IObjectActionPattern*> patterns);
    
    void Move(float angle, float speed, float dt) override;
    
    void Render(HDC hdc) override;

    void Update(float dt) override;
    void MoveBackToBorder();

    void Shoot(string bulletShapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) override;

    void OnHit(ICollideable* hitObject) override;

    void Release() override;


    virtual void GetDamaged(int damage);

    // 아이템 관련 코드
	// inline void SetItemList(vector<BHItem*>& itemList) { items = &itemList; }
	// inline void SetGameState(GameState* state) { gameState = state; }
	
	void CleanUpActiveSession();
	
	ItemType GetItemType() { return itemType; }
	// bool IsBigScore() { return isBigScore; }
	bool IsDropPending() { return isDropPending; }
	
	void ResetDropPending() { isDropPending = false; }
};

