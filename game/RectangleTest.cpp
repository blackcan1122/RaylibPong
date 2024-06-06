#include "RectangleTest.h"
#include "iostream"

void RectangleTest::Tick(float Deltatime)
{
	SetBBox();
	DrawSquare();
}


void RectangleTest::UpdateTransform(float Deltatime)
{
	// Accelarting
	Accel = 30.f; // Magic Accel Number
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

void RectangleTest::OnCollision(std::shared_ptr<CollisionEvent> event)
{
	if (event)
	{

		Vector2 NormalizedVel = this->GetNormalizedVelocity();
		float MagnitudeVel = this->GetMagnitudeVelocity();

		//Invert of Vector for Faking Bounce
		NormalizedVel = Vector2Scale(NormalizedVel, -1);
		// Adding the Magnitude again on the new Direction
		NormalizedVel = Vector2Scale(NormalizedVel, MagnitudeVel);

		Velocity = NormalizedVel;

		Vector2 NewPos = Vector2Add(this->GetPosition(), Vector2Scale(Velocity, event->CurrentDeltaTime*2));
		Position = NewPos;
		std::cout << Position.x << " , " << Position.y << std::endl;
	}
}

Vector2 RectangleTest::GetNormalizedVelocity()
{
	Vector2 NormalizedVector = Vector2Normalize(Velocity);
	return NormalizedVector;
}

float RectangleTest::GetMagnitudeVelocity()
{
	float Magnitude = std::sqrt((Velocity.x * Velocity.x) + (Velocity.y * Velocity.y));
	return Magnitude;
}

Vector2 RectangleTest::CalculateForwardVector()
{
	Vector2 NormalizedVelocity = GetNormalizedVelocity();
	Vector2 ForwardVector = Vector2Scale(NormalizedVelocity, this->GetMagnitudeVelocity() * 0.25f);

	Vector2 Dim = this->GetDimensions();
	Vector2 OffsettedPos = { GetPosition().x + (Dim.x / 2),GetPosition().y + (Dim.y / 2) };

	ForwardVector = Vector2Add(ForwardVector, OffsettedPos);

	return ForwardVector;
}

Vector2 RectangleTest::GetCenter()
{
	Vector2 Dim = this->GetDimensions();
	Vector2 CenteredVector = { GetPosition().x + (Dim.x / 2),GetPosition().y + (Dim.y / 2) };
	return CenteredVector;
}


