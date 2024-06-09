#include "Physic.hpp"
#include <cmath>

void PhysicEngine::Tick(float Deltatime)
{
	CollectAllObjectsForGravity();
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
			std::cout << "Own Reference" << std::endl;
			continue;
		}
		// Somehow all objects except self reference land here
		if (Object->GetGravityAffected() == false)
		{
			std::cout << "Not Gravity" << std::endl;
			continue;
		}
		GravityAffected.push_back(Object);
	}
}

void PhysicEngine::ApplyGravity(float Deltatime)
{
	//std::cout << GravityAffected.size() << std::endl;
	for (const auto& Object : GravityAffected)
	{
		Vector2 Temp = Object->GetPosition();
		Temp = (Vector2Add(Temp,(Vector2Scale(Gravity,Deltatime*100))));
		Object->SetPosition(Temp);
	}
}
