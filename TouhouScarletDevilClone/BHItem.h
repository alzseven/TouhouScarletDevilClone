#pragma once
#include "BHObject.h"

class D2DImage;
class BHItem : public BHObject
{
private:
	D2DImage* ItemImage;
	FPOINT StartPos;

	bool isGoingUpItem = true;
	float speedY;
	float gravity;
	bool isItemGet;
	
public:
	BHItem() = default;
	~BHItem() = default;


	void Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle) override;
	void Update(float dt) override;
	void Render(HDC hdc) override;
	void OnHit(ICollideable* hitObject) override;
	virtual void Move(float dt);
	void Move(float angle, float speed, float dt) override;
	void Shoot(FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) override;
	void Release() override;
	

	bool GetIsItemGet() { return isItemGet; }



};

