#include "Tickable.h"

void Tickable::SetPosition(Vector2 NewPos)
{
	Position = NewPos;
}

void Tickable::SetColor(Color NewColor)
{
	FColor = NewColor;
}

void Tickable::SetUseGravity(bool Status)
{
	GravitiyAffects = false;
}

void Tickable::SetIsBoundByScreen(bool Status)
{
	IsBoundByScreen = false;
}


Vector2 Tickable::GetPosition()
{
	return Position;
}

Color Tickable::GetColor()
{
	return FColor;
}
