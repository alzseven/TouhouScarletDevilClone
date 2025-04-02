#pragma once
#include "BHItem.h"

class PowerUpItem : public BHItem
{
public:
	PowerUpItem() = default;
	~PowerUpItem() = default;
	void Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle) override;
	void Update(float dt) override;
	void Render(HDC hdc) override;
	void OnHit(ICollideable* hitObject) override;
	virtual void Move(float dt) override;
	void Move(float angle, float speed, float dt) override;
	void Release() override;
	void Shoot(FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) override;
};

