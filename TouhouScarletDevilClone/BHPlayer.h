#pragma once
#include "config.h"
#include "BHObject.h"

class BulletManager;
class IBulletFactory;
class Image;
class BHPlayer : public BHObject
{
	// SHAPE* Shape;
	// Image* image;
	// float scale;
	// float imgAlpha;
	// bool isAlive;

	// FPOINT position;
	// float radianAngleDirection;
	int frameIndex;
	float timeElapsed;
	float shootDelay;
	BulletManager* bulletManager;
	IBulletFactory* level1BulletFactory;
	IBulletFactory* level2BulletFactory;
	// BulletManager* subweaponBulletManager;
	// IBulletFactory* SubWeaponFactory;
	int tempLevel;
	Image* moveImage;
	FPOINT moveDir;
public:
	// »ý¼ºÀÚ
	BHPlayer() = default;
	~BHPlayer() = default;

	inline void SetMoveImage(Image* moveImage) { this->moveImage = moveImage; }
	 
	// virtual  void Init(Image* image, FPOINT position, float angle);
	void Init(Image* image, float hit, FPOINT position, float radianAngle) override;
	
	//TODO:
	virtual void Move(FPOINT moveDirection, bool isPressingShift);

	// virtual void Update();

	// void RenderSub(HDC hdc, Image* image, float size, float fade);
	//void RenderSub(CTexture* texture, float size, float fade);
	void Render(HDC hdc) override;
	
	// bool IsHit(BHObject* BHObject);
	//TODO: Quad-Tree Optimization how?
	//bool IsHit(CTaskList * list);

	//TODO:
	// inline void SetShape(int shape_id) { Shape = new SHAPE(); };
	
	void MoveBackToBorder();

	// void OnCollide(BHObject* objectCollided);
	
	void Update() override;

	void Shoot();

	void ShootSubWeapon(bool isAccumulating);
};

