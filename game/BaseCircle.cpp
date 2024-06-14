#include "BaseCircle.h"
#include "iostream"

void BaseCircle::Tick(float Deltatime)
{
	DrawCircleShape();
	if (IsControllable == true)
	{
		UseControllTransform(Deltatime);
	}
	else
	{
		CalculateNewPos(Deltatime);
	}
}

void BaseCircle::SetIsControllable(bool Status)
{
	this->IsControllable = Status;
}

void BaseCircle::SetIsBoundByScreen(bool Status)
{
	this->IsBoundByScreen = Status;
}

void BaseCircle::SetUseGravity(bool Status)
{
	this->GravityAffects = Status;
}

void BaseCircle::SetPosition(Vector2 NewPos)
{
	Position = NewPos;
}

Vector2 BaseCircle::CalculatePosition(Vector2& CurrentPos, Vector2& Velocity, float& Dampening, Vector2& Accel, const float Deltatime)
{
	Vector2 ReturnArray;
	ReturnArray = Vector2Add(Velocity, Accel);

	ReturnArray.x *= Dampening;
	ReturnArray.y *= Dampening;

	ReturnArray = Vector2Add(Position, Vector2Scale(Velocity,Deltatime));

	
	return ReturnArray;

}

bool BaseCircle::GetGravityAffected()
{
	return GravityAffects;
}

void BaseCircle::CalculateGravity(float Gravity, float Deltatime)
{
	if ((this->GetPosition().y + Radius) > GetScreenHeight() && IsBoundByScreen)
	{
		Vector2 Pos = this->GetPosition();
		Pos.y -= (Pos.y - GetScreenHeight() + Radius);
		SetPosition(Pos);
		Vector2 Helper = { 0,-1 };
		Vector2 ReflectVector;
		ReflectVector = (Vector2Reflect(Velocity, Helper));
		ReflectVector = Vector2Scale(ReflectVector, 0.8);
		Velocity = ReflectVector;
	}

	std::cout << Vector2Length(Velocity) << std::endl;
	Velocity.y += Gravity;
	Velocity.y *= Dampening;


	CalculateNewPos(Deltatime);
}


void BaseCircle::CalculateNewPos(float Deltatime)
{
	Vector2 NewPos = GetPosition();
	NewPos.x += Velocity.x * Deltatime;
	NewPos.y += Velocity.y * Deltatime;

	SetPosition(NewPos);
}

void BaseCircle::UseControllTransform(float Deltatime)
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

void BaseCircle::DrawCircleShape()
{
	DrawCircle(Position.x, Position.y, Radius, FColor);
}

void BaseCircle::SetRadius(float NewRadius)
{
	Radius = NewRadius;
}


float BaseCircle::GetRadius()
{
	return Radius;
}


void BaseCircle::OnCollision(std::shared_ptr<CollisionEvent> event)
{
	if (event)
	{
		// Need to be implement for circles
	}
}

Vector2 BaseCircle::GetNormalizedVelocity()
{
	Vector2 NormalizedVector = Vector2Normalize(Velocity);
	return NormalizedVector;
}

float BaseCircle::GetMagnitudeVelocity()
{
	float Magnitude = std::sqrt((Velocity.x * Velocity.x) + (Velocity.y * Velocity.y));
	return Magnitude;
}

Vector2 BaseCircle::CalculateForwardVector()
{
	Vector2 NormalizedVelocity = GetNormalizedVelocity();
	Vector2 ForwardVector = Vector2Scale(NormalizedVelocity, this->GetMagnitudeVelocity() * 0.25f);

	float Radius = this->GetRadius();
	Vector2 OffsettedPos = { GetPosition().x + Radius,GetPosition().y + Radius };

	ForwardVector = Vector2Add(ForwardVector, OffsettedPos);

	return ForwardVector;
}

Vector2 BaseCircle::GetCenter()
{
	float Radius = this->GetRadius();
	Vector2 OffsettedPos = { GetPosition().x + Radius,GetPosition().y + Radius };
	return OffsettedPos;
	
}


