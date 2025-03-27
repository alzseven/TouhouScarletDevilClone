#pragma once
#include "BHObject.h"
class BHPlayer : public BHObject
{
public:
	// 생성자
	BHPlayer() = default;
	
	virtual void Move(FPOINT moveDirection, bool isPressingShift);

	void MoveBackToBorder();

	void OnCollide(BHObject* objectCollided);

	// BHObject을(를) 통해 상속됨
	void Update() override;
};

