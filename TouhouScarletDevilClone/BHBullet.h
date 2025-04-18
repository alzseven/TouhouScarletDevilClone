#pragma once
#include "BHObject.h"
#include "config.h"
#include "ObjectPool.h"

class D2DImage;
class BHBullet : public BHObject
{
protected:
	float imageAngle = 0;
	// angluar accel
	float angleRate;
	// accel
	float speedRate;
	float movementSpeed;
	ObjectPool<BHBullet>* pool;
public:
	BHBullet() = default;
	~BHBullet() override = default;
	
	void Init(string shapeKey, FPOINT pos) override;
	void Init(string shapeKey, FPOINT pos, bool isPlayerBullet);
	
	void Launch(float angle, float angleRate, float movementSpeed, float moveSpeedRate);
	void Launch(float angleRate, float speedRate, float movementSpeed, bool isPlayerBullet);
	
	void Release() override;
	
	void Update(float dt) override;
	void Render(HDC hdc) override;

	void OnHit(ICollideable* hitObject) override;
	
	void Move(float angle, float speed, float dt) override;

	void Reset();

	void Shoot(string bulletShapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) override {};

	bool IsOutofScreen() override;
};

