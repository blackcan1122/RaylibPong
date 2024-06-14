/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and run premake 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"
#include <stdio.h>
#include <cstdio>
#include "TickAll.h"
#include "BaseRectangle.h"
#include "BaseCircle.h"
#include "Event.hpp"
#include "EventDispatcher.hpp"
#include "DispatcherEvent.hpp"
#include "Physic.hpp"
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

const int screenWidth = 800;
const int screenHeight = 600;

int main()
{

    // Initialize window
    InitWindow(screenWidth, screenHeight, "Waterfall Sonar");


    SetTargetFPS(60);
    std::shared_ptr<BaseRectangle> MyRectangle = std::make_shared<BaseRectangle>();
    std::shared_ptr<BaseRectangle> MyRectangle2 = std::make_shared<BaseRectangle>();
    std::shared_ptr<BaseCircle> MyCircle = std::make_shared<BaseCircle>();

    std::vector<std::shared_ptr<BaseRectangle>> RuntimeRectangles;

    // Creating PhysicEngineObject
    PhysicEngine PhysicEngineObj;


    EventDispatcher Dispatcher;

    Dispatcher.AddListener("CollisionEvent",[MyRectangle](std::shared_ptr<Event> event)
        {
            auto Test = std::dynamic_pointer_cast<CollisionEvent>(event);
            if (Test)
            {
                MyRectangle->OnCollision(Test);
            }
        });

    // Initializing Start Position
    Vector2 Pos1 = { 0,0 };
    Vector2 Pos2 = { 200,200 };
    MyCircle->SetPosition(Vector2{ 0,0 });
    // Init Start Parameter of Objects
    MyRectangle->SetPosition(Pos1);
    MyRectangle->SetUseGravity(true);
    MyRectangle2->SetPosition(Pos2);
    MyRectangle2->SetUseGravity(false);
    MyCircle->SetUseGravity(true);
    MyCircle->SetIsBoundByScreen(true);
    MyCircle->SetIsControllable(false);
    Vector2 PosCircle = { screenWidth / 2,0 };
    MyCircle->SetPosition(PosCircle);
    MyRectangle->SetIsControllable(true);


    PhysicEngineObj.CollectAllObjectsForGravity();
    // Init Start FPS
    float FPSTest = 60;

    

    // Main game loop
    while (!WindowShouldClose()) 
    {
        
        if (IsKeyPressed(KEY_TAB))
        {
            RuntimeRectangles.push_back(std::make_shared<BaseRectangle>());
            RuntimeRectangles[RuntimeRectangles.size() - 1]->SetIsControllable(false);
            RuntimeRectangles[RuntimeRectangles.size() - 1]->SetUseGravity(true);

            PhysicEngineObj.CollectAllObjectsForGravity();
        }
        if (IsKeyPressedRepeat(KEY_D))
        {
            if (RuntimeRectangles.size() > 1)
            {
                RuntimeRectangles.pop_back();
            }
            PhysicEngineObj.CollectAllObjectsForGravity();
        }

        DrawFPS(0, 0);
        float DeltaTime = GetFrameTime();
        TickAll(DeltaTime);
        // Draw Deltatime to Screen
        DrawText(TextFormat("%f", DeltaTime), 200, 200, 16, BLUE);

        // Check for Collision for CollisionEvent Dispatch and filling in data
        if(CheckCollisionRecs(MyRectangle->GetBBox(), MyRectangle2->GetBBox()))
        {
            std::shared_ptr<CollisionEvent> eventCollision = std::make_shared<CollisionEvent>();
            eventCollision->m_HasCollisionHappend = true;
            eventCollision->CurrentDeltaTime = DeltaTime;
            eventCollision->Rect1 = std::dynamic_pointer_cast<Tickable>(MyRectangle);
            eventCollision->Rect2 = std::dynamic_pointer_cast<Tickable>(MyRectangle2);
            Dispatcher.Dispatch(eventCollision);
        }

        DrawText(TextFormat("There are Currently %d", TickableFactory::GetTickables().size()), 500, 500, 18, RED);

        // Debug Velocity Vector
        Vector2 DebugVelVector[2];
        DebugVelVector[0] = MyRectangle->GetCenter();
        DebugVelVector[1] = MyRectangle->CalculateForwardVector();
        DrawSplineLinear(DebugVelVector, 2, 2, RED);

        //Refresh Window 
        BeginDrawing();
        ClearBackground(RAYWHITE);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}