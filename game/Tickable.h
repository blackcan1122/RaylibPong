#pragma once
#include "TickableFactory.h"
#include "raylib.h"
#ifndef TICKABLE_H
#define TICKABLE_H
/*
* Class which all Objects who needs a Tick functionality can derive from
*/
class Tickable {
public:
    Tickable() = default;
    virtual ~Tickable();       // Virtual destructor for proper cleanup
    virtual void Tick(float deltaTime) = 0;  // Pure virtual method
    virtual void SetPosition(Vector2 NewPos) = 0;
    virtual void SetIsControllable(bool Status) = 0;

    virtual void SetColor(Color NewColor);
    virtual void SetUseGravity(bool Status);
    virtual void SetIsBoundByScreen(bool Status);
    virtual Vector2 GetPosition();
    virtual Color GetColor();
    virtual bool GetGravityAffected() = 0;

protected:

    bool GravitiyAffects;
    bool IsBoundByScreen = false;
    bool GravityAffects = false;
    Vector2 Position = { 0,0 };
    Color FColor = BLACK;
    bool IsControllable = false;
};

#endif // TICKABLE_H