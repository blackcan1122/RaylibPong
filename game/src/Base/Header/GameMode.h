#pragma once
#include "core/Core.h"

class GameMode
{
public:
	GameMode(float Tick);
	~GameMode();

	void Update();

protected:
	float m_DeltaTime;
};