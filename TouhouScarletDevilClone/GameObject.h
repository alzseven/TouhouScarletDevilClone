#pragma once
#include "config.h"

class GameObject
{
public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc) = 0;

	GameObject() = default;
	virtual ~GameObject() = default;
};

