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
#include "RectangleTest.h"
#include "Event.hpp"
#include "EventDispatcher.hpp"

// Define a simple C++ class that uses raylib functions
class SimpleWindow {
public:
    SimpleWindow(int width, int height, const char* title) {
        RLAPI::InitWindow(width, height, title); // Initialize the window using raylib
        RLAPI::SetTargetFPS(18); // Set the frame rate
    }

    ~SimpleWindow() {
        CloseWindow(); // Close the window using raylib
    }

    bool ShouldClose() const {
        return WindowShouldClose(); // Check if the window should close using raylib
    }

    void BeginDrawing() const {
        RLAPI::BeginDrawing(); // Start drawing using raylib
    }

    void EndDrawing() const {
        RLAPI::EndDrawing(); // End drawing using raylib
    }

    void ClearBackground(Color color) const {
        RLAPI::ClearBackground(color); // Clear the background using raylib
    }

    
};

const int screenWidth = 800;
const int screenHeight = 600;

int main()
{

    // Initialize window
    InitWindow(screenWidth, screenHeight, "Waterfall Sonar");


    SetTargetFPS(60);
    std::shared_ptr<RectangleTest> MyRectangle = std::make_shared<RectangleTest>();
    std::shared_ptr<RectangleTest> MyRectangle2 = std::make_shared<RectangleTest>();

    EventDispatcher Dispatcher;

    Dispatcher.AddListener("CollisionEvent",[&MyRectangle](std::shared_ptr<Event> event)
        {
            auto Test = std::dynamic_pointer_cast<CollisionEvent>(event);
            if (Test)
            {
                MyRectangle->OnCollision(Test);
            }
        });

    Vector2 Pos1 = { 0,0 };
    Vector2 Pos2 = { 200,200 };
    MyRectangle->SetPosition(Pos1);
    MyRectangle2->SetPosition(Pos2);
    float FPSTest = 60;
    // Main game loop
    while (!WindowShouldClose()) {

        //FPSTest += GetMouseWheelMove();
        //SetTargetFPS(FPSTest);
        DrawFPS(0, 0);
        float DeltaTime = GetFrameTime();
        char Buffer[16];
        // Convert the Float of DeltaTime to the Char Buffer
        std::snprintf(Buffer, sizeof(Buffer), "%f", DeltaTime);

        Vector2 Temp = MyRectangle->GetPosition();
        float test = 0;
        MyRectangle->UpdateTransform(DeltaTime);
        DrawText(TextFormat("Position Y is %f", MyRectangle->GetPosition().y), 250, 240, 12, BLACK);
        DrawText(TextFormat("Position X is %f", MyRectangle->GetPosition().x), 250, 250, 12, BLACK);

        DrawText(TextFormat("Position of BBox 1 is X:%f Y:%f", MyRectangle->GetBBox().x, MyRectangle->GetBBox().y),100,100,18,BLACK);
        if(CheckCollisionRecs(MyRectangle->GetBBox(), MyRectangle2->GetBBox()))
        {
            std::shared_ptr<CollisionEvent> eventCollision = std::make_shared<CollisionEvent>();
            eventCollision->m_HasCollisionHappend = true;
            eventCollision->CurrentDeltaTime = DeltaTime;
            eventCollision->Rect1 = std::dynamic_pointer_cast<Tickable>(MyRectangle);
            eventCollision->Rect2 = std::dynamic_pointer_cast<Tickable>(MyRectangle2);
            Dispatcher.Dispatch(eventCollision);
        }
        Vector2 TEST[2];

        TEST[0] = MyRectangle->GetCenter();
        TEST[1] = MyRectangle->CalculateForwardVector();

        DrawSplineLinear(TEST, 2, 2, RED);

        BeginDrawing();
        ClearBackground(RAYWHITE);


        TickAll(DeltaTime);

        // Draw the text
        DrawText(Buffer, 200, 200, 16, BLUE);

        EndDrawing();
        
    }

    CloseWindow();
    return 0;
}