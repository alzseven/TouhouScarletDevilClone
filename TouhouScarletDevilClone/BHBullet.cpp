#include "BHBullet.h"

void BHBullet::Update()
{
	//rad angle
	float rad = radianAngleDirection;
	
	// update position with using angle and movement speed
	position.x += movementSpeed * cosf(rad);
	position.y -= movementSpeed * sinf(rad);

	// add angularaccel to radAngle
	radianAngleDirection += DEG_TO_RAD(AngleRate);
	
	// add accel to movementSpeed;
	movementSpeed += SpeedRate;
	
	//TODO: Check if bullet go out of screen
}

void BHBullet::Render()
{
}
