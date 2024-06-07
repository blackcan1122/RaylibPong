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
	* virtual void SetPosition(Vector2 NewPos)
	* virtual void SetColor(Color NewColor)
	* virtual Vector2 GetPosition()
	* virtual Color GetColor()
	* 
	* Vector2 Position
	* Color FColor
	* *****************************************
	*/

	/*
	* ****************************
	* Overriding Virtual Functions
	* ****************************
	*/

	// Tick Function From Tickable Class
	void Tick(float Deltatime) override;

	void SetIsControllable(bool Status) override;

	/*
	* *******************************
	* BaseRectangle Classes Specifics
	* *******************************
	*/
	
	void UpdateTransform(float Deltatime);
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
	bool isBoundByScreen = true;
	float Radius = 15.f;
	Vector2 Velocity = { 0,0 };
	float Accel = 0;
	float Dampening = 0.97;

};

