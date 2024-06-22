#pragma once
#include "core/Core.h"

class GameInstance
{

private:
	GameInstance(int ScreenWidth, int Screenheight, int TargetFps, bool Fullscreen);
	~GameInstance() = default;

	static GameInstance* Instance;

protected:

	/*
	*****************************
	* Window and Start Parameter
	*****************************
	*/

	int m_ScreenWidth;
	int m_ScreenHeight;
	bool m_Fullscreen;
	int m_TargetFps;

	/*
	*****************************
	* Methods
	*****************************
	*/

	static void CreateWindow();
	static void GameLoop();

public:

	GameInstance(const GameInstance&) = delete;
	GameInstance& operator=(const GameInstance&) = delete;

	static void InitGameInstance(int ScreenWidth, int Screenheight, int TargetFps, bool Fullscreen);
	static GameInstance* GetInstance();


};