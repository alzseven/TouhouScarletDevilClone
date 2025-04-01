#pragma once
#include "config.h"

class GameObject
{
public:
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(){};

	GameObject() = default;
	virtual ~GameObject() = default;
};

