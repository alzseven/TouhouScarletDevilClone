#pragma once
#include "config.h"
#include "BHObject.h"

class BulletManager;
// class BulletManager;
// class IBulletFactory;
class Image;
class D2DImage;
class BHPlayer : public BHObject
{
	int frameIndex;
	float timeElapsed;
	float shootDelay;
	BulletManager* bulletManager;
	// IBulletFactory* level1BulletFactory;
	// IBulletFactory* level2BulletFactory;

	// int tempLevel;
	D2DImage* moveImage;
	FPOINT moveDir;
public:
	// »ý¼ºÀÚ
	BHPlayer() = default;
	~BHPlayer() override = default;

	inline void SetMoveImage(D2DImage* moveImage) { this->moveImage = moveImage; }
	 
	void Init(string shapeKey, float hitRadius, FPOINT pos, float radianAngle) override;
	// void Init(D2DImage* image, float hit, FPOINT position, float radianAngle) override;
	
	//TODO:
	virtual void Move(FPOINT moveDirection, bool isPressingShift, float dt);

	void Move(float angle, float speed, float dt) override;
	void Render(HDC hdc) override;
	
	//TODO: Quad-Tree Optimization how?
	//bool IsHit(CTaskList * list);

	//TODO:
	// inline void SetShape(int shape_id) { Shape = new SHAPE(); };
	
	void MoveBackToBorder();
	
	void Update(float dt) override;

	void OnHit(ICollideable* hitObject) override;

	// void Shoot(float angle, int shootAmount = 1) override;
	void Shoot(FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) override;

	void ShootSubWeapon(bool isAccumulating);

	void Release() override;
};

