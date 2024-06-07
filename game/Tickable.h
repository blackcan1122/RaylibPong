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
    virtual void Tick(float deltaTime) = 0;  // Pure virtual method
    virtual ~Tickable()                     // Virtual destructor for proper cleanup
    {
        DrawCircle(200, 200, 100, RED);
    }


    virtual void SetPosition(Vector2 NewPos);
    virtual void SetColor(Color NewColor);
    virtual void SetIsControllable(bool Status) = 0;

    virtual Vector2 GetPosition();
    virtual Color GetColor();

protected:

    bool IsBoundByScreen;
    bool GravitiyAffects;
    Vector2 Position;
    Color FColor;
    bool IsControllable;
};

#endif // TICKABLE_H