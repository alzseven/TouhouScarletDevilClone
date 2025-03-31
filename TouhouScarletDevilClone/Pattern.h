#pragma once
#include"config.h"
class Pattern
{
public:
	string shapeId;
	int			fireCount = 0;
	float		s_delay = 0;

	float		m_angle = 0;
	float		m_angleRate = 0;
	float		m_speed = 0;
	float		m_speedRate = 0;
};
