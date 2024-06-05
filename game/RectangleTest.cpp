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

	// Accelarting


	Accel = 30.f;
	if (IsKeyDown(KEY_UP))
	{
		Velocity.y -= Accel;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		Velocity.y += Accel;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		Velocity.x += Accel;
	}
	if (IsKeyDown(KEY_LEFT))
	{
		Velocity.x -= Accel;
	}

	// Apply Dampening
	Velocity.x *= Dampening;
	Velocity.y *= Dampening;

	// Update position with velocity

	Position.x += Velocity.x * Deltatime;
	Position.y += Velocity.y * Deltatime;
	Direction = Velocity;
	Vector2Normalize(Direction);

	// Check if velocity is close to zero and set it to zero if so
	if (std::abs(Velocity.x) < 0.02)
	{
		Velocity.x = 0;
	}
	if (std::abs(Velocity.y) < 0.02)
	{
		Velocity.y = 0;
	}

	DrawText(TextFormat("Velocity X: %f, Velocity Y:%f", Velocity.x, Velocity.y), 50, 50, 12, BLACK);
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


