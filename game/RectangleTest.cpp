#include "RectangleTest.h"
#include "iostream"

void RectangleTest::Tick(float Deltatime)
{
	SetBBox();
	DrawSquare();
}


void RectangleTest::UpdateTransform(float Deltatime)
{
	// Need to be Rewritten with Direction + Acceleration + Speed to proberly determine momentum
	// 
	// Helper Lambda for Adding two Vectors
	


	auto AddVector2 = [](Vector2& FirstVector, const Vector2 SecondVector)
	{
			FirstVector.x += SecondVector.x;
			FirstVector.y += SecondVector.y;
			return FirstVector;
	};

	auto MultVector2 = [](Vector2& FirstVector, const Vector2 SecondVector)
		{
			FirstVector.x *= SecondVector.x;
			FirstVector.y *= SecondVector.y;
			return FirstVector;
		};

	// Helper Lambda for Clamping Vector 2
	auto ClampVector2 = [](Vector2& VectorToClamp)
		{
			if (VectorToClamp.x > 1)
			{
				VectorToClamp.x = 1;
			}
			else if (VectorToClamp.x < -1)
			{
				VectorToClamp.x = -1;
			}

			if (VectorToClamp.y > 1)
			{
				VectorToClamp.y = 1;
			}
			else if (VectorToClamp.y < -1)
			{
				VectorToClamp.y = -1;
			}


		};


	// Accelarting
	if (IsKeyDown(KEY_UP))
	{
		Momentum.y += -0.01;
		Vector2 TempVector = { 0,-1 };
		Direction = AddVector2(Direction, TempVector);
	}
	if (IsKeyDown(KEY_DOWN))
	{
		Momentum.y += 0.01;
		Vector2 TempVector = { 0, 1 };
		Direction = AddVector2(Direction, TempVector);

	}
	if (IsKeyDown(KEY_RIGHT))
	{
		Momentum.x += 0.01;
		Vector2 TempVector = { 1, 0 };
		Direction = AddVector2(Direction, TempVector);

	}
	if (IsKeyDown(KEY_LEFT))
	{
		Momentum.x += -0.01;
		Vector2 TempVector = { -1, 0 };
		Direction = AddVector2(Direction, TempVector);
	}

	ClampVector2(Momentum);
	//ClampVector2(Direction);

	// Normalize the Vector (Direction)
	float directionMagnitude = std::sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
	if (directionMagnitude > 0)
	{
		Direction.x /= directionMagnitude;
		Direction.y /= directionMagnitude;
	}

	// Calculating End Position for current Tick
	Position.x += Direction.x * std::abs(Momentum.x) * (Deltatime * 1000);
	Position.y += Direction.y * std::abs(Momentum.y) * (Deltatime * 1000);


	if (!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
	{
		isInMomentumState = true;
	}

	if (isInMomentumState == true)
	{
		Position.x += Momentum.x * (Deltatime * 1000);
		Position.y += Momentum.y * (Deltatime * 1000);

		// Apply damping factor for deceleration
		float dampingFactor = 0.95f;
		Momentum.x *= dampingFactor;
		Momentum.y *= dampingFactor;

		// If momentum is very small, stop it
		if (std::abs(Momentum.x) < 0.01f) Momentum.x = 0;
		if (std::abs(Momentum.y) < 0.01f) Momentum.y = 0;
		if (Momentum.x == 0 && Momentum.y == 0) isInMomentumState = false;

		// Reset direction to zero when decelerating
		Direction = { 0, 0 };

		std::cout << "Momentum X:" << Momentum.x << std::endl;
		std::cout << "Momentum Y:" << Momentum.y << std::endl;
		std::cout << "Direction X:" << Direction.x << std::endl;
		std::cout << "Direction Y:" << Direction.y << std::endl;
	}

}

void RectangleTest::DrawSquare()
{
	DrawRectangle(Position.x, Position.y, Dimensions.x, Dimensions.y, FColor);
}

void RectangleTest::SetDimensions(Vector2 NewDimensions)
{
	Dimensions = NewDimensions;
}

void RectangleTest::SetBBox()
{
	BBox = { Position.x, Position.y, Dimensions.x, Dimensions.y };
}

Vector2 RectangleTest::GetDimensions()
{
	return Dimensions;
}

Rectangle RectangleTest::GetBBox()
{
	return BBox;
}


