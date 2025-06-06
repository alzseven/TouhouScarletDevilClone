#pragma once
#include "BHItem.h"

class ScoreItem : public BHItem
{
public:
	ScoreItem() = default;
	~ScoreItem() = default;

	void Init(string shapeKey, FPOINT pos) override;
	void Update(float dt) override;
	void Render(HDC hdc) override;
	void OnHit(ICollideable* hitObject) override;
	virtual void Move(float dt) override;
	void Move(float angle, float speed, float dt) override;
	void Release() override;
	void Shoot(string shapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) override;

};

