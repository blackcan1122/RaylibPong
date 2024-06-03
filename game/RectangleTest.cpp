#include "RectangleTest.h"
#include "iostream"

void RectangleTest::Tick(float Deltatime)
{
	SetBBox();
	DrawSquare();
}


void RectangleTest::UpdateTransform(float Deltatime)
{
	// Still a Problem with the way i implemented Momentum -> Should change to Vector2 and calculate on top of pos in general

	// Helper Lambda Function for Clamping:
	auto ClampMomentum = [this]() 
	{
		if (this->Momentum >= 10) this->Momentum = 10;
		if (this->Momentum <= 0) this->Momentum = 0;
	};

	// Helper Lambda for Setting Position
	auto m_SetPosition = [this, Deltatime](float& Position, float Delta, float& Momentum)
		{
			Position += Delta * Momentum * (Deltatime * 1000);
		};
	// Accelarting
	
	if (IsKeyDown(KEY_UP))
	{
		this->Momentum += 0.1;
		ClampMomentum();
		m_SetPosition(this->Position.y, -0.1, this->Momentum);
		LastPressed = UpKey;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		this->Momentum += 0.1;
		ClampMomentum();
		m_SetPosition(this->Position.y, 0.1, this->Momentum);
		LastPressed = DownKey;

	}
	if (IsKeyDown(KEY_RIGHT))
	{
		this->Momentum += 0.1;
		ClampMomentum();
		m_SetPosition(this->Position.x, 0.1, this->Momentum);
		LastPressed = RightKey;

	}
	if (IsKeyDown(KEY_LEFT))
	{
		this->Momentum += 0.1;
		ClampMomentum();
		m_SetPosition(this->Position.x, -0.1, this->Momentum);
		LastPressed = LeftKey;
	}

	ClampMomentum();

 //Slowing Down

	if (LastPressed == UpKey && !IsKeyDown(KEY_UP))
	{
		this->Momentum -= 0.1;
		ClampMomentum();
		m_SetPosition(this->Position.y, -0.1, this->Momentum);

	}
	if (LastPressed == DownKey && !IsKeyDown(KEY_DOWN))
	{
		this->Momentum -= 0.1;
		ClampMomentum();
		m_SetPosition(this->Position.y, 0.1, this->Momentum);


	}
	if (LastPressed == RightKey && !IsKeyDown(KEY_RIGHT))
	{
		this->Momentum -= 0.1;
		ClampMomentum();
		m_SetPosition(this->Position.x, 0.1, this->Momentum);

	}
	if (LastPressed == LeftKey && !IsKeyDown(KEY_LEFT))
	{
		this->Momentum -= 0.1;
		ClampMomentum();
		m_SetPosition(this->Position.x, -0.1, this->Momentum);

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


