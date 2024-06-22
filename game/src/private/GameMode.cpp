#include "GameMode.h"

GameMode::GameMode(float Tick)
{
	m_DeltaTime = Tick;
	std::cout << "GameMode Was Created" << std::endl;

}

GameMode::~GameMode()
{
	std::cout << "GameMode Was Deleted" << std::endl;
}

void GameMode::Update()
{
	if (m_DeltaTime == 10)
	{
		ClearBackground(RED);
	}
	else if (m_DeltaTime == 20)
	{
		ClearBackground(GREEN);
	}
}
