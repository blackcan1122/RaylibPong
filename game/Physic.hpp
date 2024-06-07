#pragma once
#include "raylib.h"
#include "Tickable.h"

class PhysicEngine : Tickable
{
	/*
* *****************************************
* Parent Methods and Variables:
*
* METHODS:
*
* virtual void Tick(float deltaTime) = 0;
* virtual void SetPosition(Vector2 NewPos);
* virtual void SetColor(Color NewColor);
* virtual void SetIsControllable(bool Status) = 0;
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
* bool GravitiyAffects;
* Vector2 Position;
* Color FColor;
* bool IsControllable;
* *****************************************
*/

/*
* ****************************
* Overriding Virtual Functions
* ****************************
*/
public:

	PhysicEngine()
	{
		TickableFactory::Register(this);
	}

	void Tick(float Deltatime) override;
	void SetIsControllable(bool Status) override;
};