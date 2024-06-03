#pragma once
#include <vector>
#include <memory>
#include <TickableFactory.h>
#include "Tickable.h"
#include "raylib.h"

/*
* 
* Template Responsible for Calling Tick on Every Class Derived from Tickable
* 
*/
static void TickAll(float deltaTime) 
{
    for (auto& Ptr : TickableFactory::GetTickables()) 
    {
        if (Ptr != nullptr)
        {
            Ptr->Tick(deltaTime);
        }
    }
}