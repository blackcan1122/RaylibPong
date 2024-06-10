#pragma once
#include "CollisionEvent.hpp"
#include "GravityEvent.hpp"
#include "Event.hpp"
#include "raylib.h"
#include "Tickable.h"
#include "raylib.h"
#include "raymath.h"
#include "DispatcherEvent.hpp"
#include "EventDispatcher.hpp"

class PhysicEngine : Tickable
{
	/*
* *****************************************
* Parent Methods and Variables:
*
* METHODS:
*
* METHODS TO BE OVERRIDEN:
* virtual void Tick(float deltaTime) = 0;
* virtual void SetIsControllable(bool Status) = 0;
* 
* OTHER METHODS:
* 
* virtual void SetPosition(Vector2 NewPos);
* virtual void SetColor(Color NewColor);
* virtual void SetUseGravity(bool Status);
* virtual void SetIsBoundByScreen(bool Status);
*
* virtual Vector2 GetPosition();
* virtual Color GetColor();
*
* MEMBERS:
*
*
* bool IsBoundByScreen;
* bool GravityAffects;
* Vector2 Position;
* Color FColor;
* bool IsControllable;
* *****************************************
*/


public:

	PhysicEngine()
	{
		TickableFactory::Register(this);
	}

/*
* ****************************
* Overriding Virtual Methods
* ****************************
*/

	void Tick(float Deltatime) override;
	void SetIsControllable(bool Status) override;
	bool GetGravityAffected() override;
	void SetPosition(Vector2 NewPos) override;

/*
* ****************************
* Own Methods
* ****************************
*/
	void CollectAllObjectsForGravity();
	void ApplyGravity(float Deltatime);
	void SetDispatcher(EventDispatcher* Dispatcher);


/*
* ****************************
* Class Member
* ****************************
*/
	Vector2 Gravity = { 0,9.82 };
	std::vector<Tickable*> GravityAffected;

	EventDispatcher* CurrentDispatcher;
};