#pragma once
#include "core/Core.h"

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