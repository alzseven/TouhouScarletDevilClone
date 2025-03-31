#pragma once
#include "BHObject.h"
#include "config.h"
#include "ObjectPool.h"

class D2DImage;
class BHBullet : public BHObject
{
protected:
	// angluar accel
	float AngleRate;
	// accel
	float SpeedRate;
	float movementSpeed;
	ObjectPool<BHBullet>* pool;
public:
	// void Init(D2DImage* image, float hit, FPOINT position, float radianAngle) override;
	void Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle) override;
	// void Init(D2DImage* image, float hit, FPOINT position, float radianAngle, float angleRate, float speedRate, float movementSpeed, bool isPlayerBullet);

	void Launch(float angleRate, float speedRate, float movementSpeed, bool isPlayerBullet);
	
	void Release() override;
	
	// BHObject을(를) 통해 상속됨
	void Update(float dt) override;
	void Render(HDC hdc) override;

	void OnHit(ICollideable* hitObject) override;

	inline void SetPool(ObjectPool<BHBullet>* pool) {this->pool = pool;}
	// inline float GetHit() override { return hit; }

	void Move(float angle, float speed, float dt) override;

	void Reset();
	// inline FPOINT* GetPos() override { return &position; }
	void Shoot(float angle, int shootAmount = 1) override {};
};

