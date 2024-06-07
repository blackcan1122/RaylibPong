#include "BaseCircle.h"
#include "iostream"

void BaseCircle::Tick(float Deltatime)
{
	DrawCircleShape();
	if (IsControllable == true)
	{
		UseControllTransform(Deltatime);
	}
}

void BaseCircle::SetIsControllable(bool Status)
{
	IsControllable = Status;
}

void BaseCircle::SetIsBoundByScreen(bool Status)
{
	this->IsBoundByScreen = Status;
}

void BaseCircle::SetUseGravity(bool Status)
{
	this->GravitiyAffects = Status;
}


void BaseCircle::UseControllTransform(float Deltatime)
{
	if (IsControllable == false)
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
	else
	{

	}
	
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
		//if (event->Rect1 == nullptr && event->Rect2 == nullptr)
		//{
		//	std::cout << "Rects are nullptr" << std::endl;
		//	return;
		//}

		//std::shared_ptr<BaseCircle> Rect1 = std::dynamic_pointer_cast<BaseCircle>(event->Rect1);
		//std::shared_ptr<BaseCircle> Rect2 = std::dynamic_pointer_cast<BaseCircle>(event->Rect2);

		//// Find intersection rectangle
		//Rectangle Intersection = GetCollisionRec(Rect1->GetBBox(), Rect2->GetBBox());
		//DrawRectangleLinesEx(Intersection, 5, BLUE);
		//// Calculate the collision normal
		//Vector2 CollisionNormal;

		//if (Intersection.width < Intersection.height) 
		//{
		//	if (Rect1->GetPosition().x < Rect2->GetPosition().x) {
		//		CollisionNormal = { -1, 0 }; // Left side
		//	}
		//	else 
		//	{
		//		CollisionNormal = { 1, 0 }; // Right side
		//	}
		//}
		//else
		//{
		//	if (Rect1->GetPosition().y < Rect2->GetPosition().y) 
		//	{
		//		CollisionNormal = { 0, -1 }; // Top side
		//	}
		//	else 
		//	{
		//		CollisionNormal = { 0, 1 }; // Bottom side
		//	}
		//}



		//// Move the rectangle to the collision point
		//Vector2 IntersectionDim = { (Intersection.width + 10) * 1.5, (Intersection.height + 10) * 1.5 };

		//Vector2 OffsettedPos = (Vector2Add(this->GetPosition(), Vector2Multiply(CollisionNormal, IntersectionDim)));
		//this->SetPosition(OffsettedPos);

		//// Calculate the reflection vector
		//Vector2 NormalizedVel = this->GetNormalizedVelocity();
		//float MagnitudeVel = this->GetMagnitudeVelocity();
		//Vector2 reflection = Vector2Subtract(NormalizedVel, Vector2Scale(CollisionNormal, 2 * Vector2DotProduct(NormalizedVel, CollisionNormal)));
		//reflection = Vector2Scale(reflection, MagnitudeVel);

		////// Update velocity
		//this->Velocity = reflection;
		//


		//std::cout << "Collision at: " << Intersection.x << ", " << Intersection.y << std::endl;
		//std::cout << "New Position: " << Position.x << " , " << Position.y << std::endl;
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


