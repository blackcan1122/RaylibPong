#include "StateMachine.h"
#include "GameMode.h"

void StateMachine::RegisterState(const std::string& StateName, std::function<GameMode* ()> FactoryFunction)
{
	StateFactory[StateName] = FactoryFunction;
}

void StateMachine::ChangeState(const std::string& StateName)
{
	if (CurrentGameMode)
	{
		std::cout << CurrentGameMode << std::endl;
		delete CurrentGameMode;
		CurrentGameMode = nullptr;
		if (CurrentGameMode == nullptr)
		{
			std::cout << "GameMode is now :" << CurrentGameMode << std::endl;
		}
	}

	CurrentGameMode = StateFactory[StateName]();
}

void StateMachine::UpdateGameMode()
{
	if (CurrentGameMode != nullptr)
	{
		CurrentGameMode->Update();
	}
}
