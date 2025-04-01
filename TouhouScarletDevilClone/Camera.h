#pragma once
class Camera
{
private:
	float x, y;
	float width, height;
	float stageWidth, stageHeight;
public:
	Camera();
	Camera(float viewWidth, float viewHeight, float stageWidth, float stageHeight);
	
	void SetPos(float x, float y);
	//void F
};

