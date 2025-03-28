#pragma once
#include "BHObject.h"
#include "config.h"

class BHBullet : public BHObject
{
protected:

	// angluar accel
	float AngleRate;
	// accel
	float SpeedRate;
	float movementSpeed;
public:
	void Init(Image* image, float hit, FPOINT position, float radianAngle) override;

	void Init(Image* image, float hit, FPOINT position, float radianAngle, float angleRate, float speedRate, float movementSpeed);
	
	// void Init(int shape_id, FPOINT position,
	// 	float angle, float angle_rate,
	// 	float movementSpeed, float speedRate);
	// BHObject을(를) 통해 상속됨
	void Update() override;
	void Render(HDC hdc) override;
	// void Render();
};

