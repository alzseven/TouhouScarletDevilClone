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
	float mainShootDelay;
	float subShootDelay;
	
	D2DImage* moveImage;
	FPOINT moveDir;
public:
	// »ý¼ºÀÚ
	BHPlayer() = default;
	~BHPlayer() override = default;

	inline void SetMoveImage(D2DImage* moveImage) { this->moveImage = moveImage; }
	 
	void Init(string shapeKey, FPOINT pos) override;
	
	//TODO:
	virtual void Move(FPOINT moveDirection, bool isPressingShift, float dt);

	void Move(float angle, float speed, float dt) override;
	void Render(HDC hdc) override;
	
	void MoveBackToBorder();
	
	void Update(float dt) override;

	void OnHit(ICollideable* hitObject) override;
	
	void Shoot(string bulletShapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) override;

	void ShootSubWeapon(bool isAccumulating);

	void Release() override;
};

