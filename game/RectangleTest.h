#pragma once
#include "Tickable.h"
#include "TickableFactory.h"
#include "raylib.h"
#include "raymath.h"
#include "Helper.hpp"
#include "CollisionEvent.hpp"
class RectangleTest : public Tickable
{
public:
	RectangleTest()
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

	/*
	* *******************************
	* RectangleTest Classes Specifics
	* *******************************
	*/
	
	void UpdateTransform(float Deltatime);
	void DrawSquare();

	// Setter Functions specific for Rectangles
	void SetDimensions(Vector2 NewDimensions);
	void SetBBox();

	// Getter Functions Specific for Rectangles
	Vector2 GetDimensions();
	Rectangle GetBBox();

	void OnCollision(std::shared_ptr<CollisionEvent> event);
	


private:

	float Test = 100;
	Vector2 Dimensions = { 100,100 };
	Vector2 Velocity = { 0,0 };
	Vector2 Direction = { 0,0 };
	float Accel = 0;
	float Mass = 0;
	float Dampening = 0.97;

	Rectangle BBox;

};

