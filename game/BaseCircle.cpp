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
	if (Debugmode == true)
	{
		DrawDebugVelocity();
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
	if ((this->GetPosition().x + Radius) > GetScreenWidth() && IsBoundByScreen)
	{
		Vector2 Pos = this->GetPosition();
		Pos.x -= (Pos.x - GetScreenWidth() + Radius);
		SetPosition(Pos);
		Vector2 Helper = { -1,0 };
		Vector2 ReflectVector;
		ReflectVector = (Vector2Reflect(Velocity, Helper));
		ReflectVector = Vector2Scale(ReflectVector, 0.8);
		Velocity = ReflectVector;
	}
	if ((this->GetPosition().x - Radius) < 0 && IsBoundByScreen)
	{
		Vector2 Pos = this->GetPosition();
		Pos.x -= (Pos.x - 0 - Radius);
		SetPosition(Pos);
		Vector2 Helper = { 1,0 };
		Vector2 ReflectVector;
		ReflectVector = (Vector2Reflect(Velocity, Helper));
		ReflectVector = Vector2Scale(ReflectVector, 0.8);
		Velocity = ReflectVector;
	}

	Velocity.y += Gravity;
	Velocity.y *= Dampening;


	CalculateNewPos(Deltatime);
}


void BaseCircle::CalculateNewPos(float Deltatime)
{
	Vector2 NewPos = GetPosition();
	if (std::abs(Velocity.x) < 0.5) { Velocity.x = 0; };
	if (std::abs(Velocity.y) < 0.5) { Velocity.x = 0; };

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

void BaseCircle::DrawDebugVelocity()
{
	Vector2 DebugVelVector[2];
	DebugVelVector[0] = this->GetCenter();
	DebugVelVector[1] = this->CalculateForwardVector();
	DrawSplineLinear(DebugVelVector, 2, 2, RED);
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


	ForwardVector = Vector2Add(ForwardVector, this->GetCenter());

	return ForwardVector;
}

void BaseCircle::CalculateCollision(std::shared_ptr<Tickable> CollisionObject)
{
	if (!CollisionObject)
	{
		std::cout << "Collision Object is Nullptr" << std::endl;
		return;
	}

	// Case when our Collision Object is derived from BaseRectangle
	if (std::dynamic_pointer_cast<BaseRectangle>(CollisionObject))
	{
		std::shared_ptr<BaseRectangle> CollObject = std::dynamic_pointer_cast<BaseRectangle>(CollisionObject);
		//Getting Vector To Collision Object
		Vector2 DirectionToOtherObject = Vector2Subtract(this->GetCenter(), CollObject->GetCenter());
		float Distance = Vector2Length(DirectionToOtherObject);

		Vector2 DirNormalized = Vector2Normalize(DirectionToOtherObject);
		Vector2 RelativeVelocity = Vector2Subtract(this->Velocity, CollObject->GetVelocity());

		// Calculate the velocity component along the direction of collision
		float VelAlongCollision = Vector2DotProduct(RelativeVelocity, DirNormalized);

		// Calculate new Position Outside of Rectangle

		Vector2 PushAway = Vector2Scale(DirNormalized, Distance/10);
		this->Position = Vector2Add(this->Position, PushAway);
		Vector2 Helper = Vector2Add(DirNormalized, CollObject->GetCenter());
		DrawLine(this->GetCenter().x, this->GetCenter().y, Helper.x, Helper.y, GREEN);


		// Apply collision response if circles are moving towards each other
		if (VelAlongCollision < 0)
		{
			Vector2 Impulse = Vector2Scale(DirNormalized, VelAlongCollision);

			this->Velocity = Vector2Subtract(this->Velocity, Impulse);

		}
	}
	// Case when our Collision Object is derived from BaseCircle
	if (std::dynamic_pointer_cast<BaseCircle>(CollisionObject))
	{
		std::shared_ptr<BaseCircle> CollObject = std::dynamic_pointer_cast<BaseCircle>(CollisionObject);

		Vector2 DirectionToOtherObject = Vector2Subtract(this->GetCenter(), CollObject->GetCenter());
		float Distance = Vector2Length(DirectionToOtherObject);

		Vector2 DirNormalized = Vector2Normalize(DirectionToOtherObject);
		Vector2 RelativeVelocity = Vector2Subtract(this->Velocity, CollObject->Velocity);

		// Calculate the velocity component along the direction of collision
		float VelAlongCollision = Vector2DotProduct(RelativeVelocity, DirNormalized);

		// Apply positional correction to separate the circles
		float RadiusSum = this->GetRadius() + CollObject->GetRadius();
		float Overlap = RadiusSum - Distance;
		Vector2 Correction = Vector2Scale(DirNormalized, Overlap / 2.0f);
		this->SetPosition(Vector2Add(this->GetPosition(), Correction));
		CollObject->SetPosition(Vector2Subtract(CollObject->GetPosition(), Correction));

		// Apply collision response if circles are moving towards each other
		if (VelAlongCollision < 0)
		{
			Vector2 Impulse = Vector2Scale(DirNormalized, VelAlongCollision);

			this->Velocity = Vector2Subtract(this->Velocity, Impulse);
			CollObject->Velocity = Vector2Add(CollObject->Velocity, Impulse);

		}
	}

}

Vector2 BaseCircle::GetCenter()
{
	float Radius = this->GetRadius();
	Vector2 OffsettedPos = { GetPosition().x , GetPosition().y  };
	return OffsettedPos;
	
}


