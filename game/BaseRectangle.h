#pragma once
#include "Tickable.h"
#include "TickableFactory.h"
#include "raylib.h"
#include "raymath.h"
#include "Helper.hpp"
#include "CollisionEvent.hpp"
class BaseRectangle : public Tickable
{
public:
	BaseRectangle()
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
	void DrawSquare();
	Vector2 CalculateForwardVector();

	// Setter Functions specific for Rectangles
	void SetDimensions(Vector2 NewDimensions);
	void SetBBox();

	// Getter Functions Specific for Rectangles
	Vector2 GetDimensions();
	Vector2 GetNormalizedVelocity();
	Vector2 GetCenter();
	Rectangle GetBBox();
	float GetMagnitudeVelocity();

	// Collision Function Event
	void OnCollision(std::shared_ptr<CollisionEvent> event);
	





private:

	Vector2 Dimensions = { 100,100 };
	Vector2 Velocity = { 0,0 };
	float Accel = 0;
	float Dampening = 0.97;
	Rectangle BBox;

};

