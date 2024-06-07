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
    virtual ~Tickable()                     // Virtual destructor for proper cleanup
    {
        DrawCircle(200, 200, 100, RED);
    }
    virtual void Tick(float deltaTime) = 0;  // Pure virtual method

    virtual void SetPosition(Vector2 NewPos);
    virtual void SetColor(Color NewColor);
    virtual void SetIsControllable(bool Status) = 0;
    virtual void SetUseGravity(bool Status);
    virtual void SetIsBoundByScreen(bool Status);

    virtual Vector2 GetPosition();
    virtual Color GetColor();

protected:

    bool IsBoundByScreen = false;
    bool GravitiyAffects = false;
    Vector2 Position = { 0,0 };
    Color FColor = BLACK;
    bool IsControllable = false;
};

#endif // TICKABLE_H