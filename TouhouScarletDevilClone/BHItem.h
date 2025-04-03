#pragma once
#include "BHObject.h"

class D2DImage;
struct GameState;
class ItemBehavior;
class BHItem : public BHObject
{
protected:
	D2DImage* ItemImage;
	FPOINT StartPos;
	GameState* gameState = nullptr;
	ItemBehavior* itemBehavior = nullptr;
	bool isGoingUpItem = true;
	float speedY;
	float gravity;
	bool isItemGet;
	int point;
	
public:
	BHItem() = default;
	~BHItem() = default;


	void InitGameState(GameState* state) { gameState = state; }
	void SetBehavior(ItemBehavior* itembehavior) { itemBehavior = itembehavior; }

	void Init(string shapeKey, FPOINT pos) override = 0;
	void Update(float dt) override = 0;
	void Render(HDC hdc) override = 0;
	void OnHit(ICollideable* hitObject) override = 0;
	virtual void Move(float dt) = 0;
	void Move(float angle, float speed, float dt) override = 0;
	void Shoot(string shapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) override = 0;
	void Release() override = 0;
	
	bool IsOutofScreen() override { return false; }

	bool GetIsItemGet() { return isItemGet; }



};

