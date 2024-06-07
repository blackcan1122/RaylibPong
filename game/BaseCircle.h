#pragma once
#include "Tickable.h"
#include "TickableFactory.h"
#include "raylib.h"
#include "raymath.h"
#include "Helper.hpp"
#include "CollisionEvent.hpp"
class BaseCircle : public Tickable
{
public:
	BaseCircle()
	{
		TickableFactory::Register(this);	
    }

public:
	/*
	* *****************************************
	* Parent Methods and Variables:
	*
	* METHODS:
	*
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
	void Tick(float Deltatime) override;
	void SetIsControllable(bool Status) override;
	void SetIsBoundByScreen(bool Status) override;
	void SetUseGravity(bool Status) override;

	/*
	* *******************************
	* Circle Classes Specifics
	* *******************************
	*/
	
	void UseControllTransform(float Deltatime);
	void DrawCircleShape();
	Vector2 CalculateForwardVector();

	// Setter Functions specific for Rectangles
	void SetRadius(float NewRadius);

	// Getter Functions Specific for Rectangles
	float GetRadius();
	Vector2 GetNormalizedVelocity();
	Vector2 GetCenter();
	float GetMagnitudeVelocity();

	// Collision Function Event
	void OnCollision(std::shared_ptr<CollisionEvent> event);
	





private:

	float Radius = 15.f;
	Vector2 Velocity = { 0,0 };
	float Accel = 0;
	float Dampening = 0.97;

};

