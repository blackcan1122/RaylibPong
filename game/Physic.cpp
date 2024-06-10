#include "Physic.hpp"
#include <cmath>

void PhysicEngine::Tick(float Deltatime)
{
	ApplyGravity(Deltatime);
}

void PhysicEngine::SetIsControllable(bool Status)
{
}

bool PhysicEngine::GetGravityAffected()
{
	return false;
}

void PhysicEngine::SetPosition(Vector2 NewPos)
{
	return;
}

void PhysicEngine::CollectAllObjectsForGravity()
{
	GravityAffected.clear();

	std::vector<Tickable*> TickablesObj = TickableFactory::GetTickables();

	for (const auto& Object : TickablesObj)
	{
		if (Object == this)
		{
			//std::cout << "Own Reference" << std::endl;
			continue;
		}
		// Somehow all objects except self reference land here
		if (Object->GetGravityAffected() == false)
		{
			std::cout << Object->GetGravityAffected() << std::endl;
			//std::cout << "Not Gravity" << std::endl;
			continue;
		}
		GravityAffected.push_back(Object);
	}
}

void PhysicEngine::ApplyGravity(float Deltatime)
{
	std::shared_ptr<GravityEvent> gravityEvent = std::make_shared<GravityEvent>();
	CurrentDispatcher->Dispatch(gravityEvent);
}

void PhysicEngine::SetDispatcher(EventDispatcher* Dispatcher)
{
	CurrentDispatcher = Dispatcher;
}