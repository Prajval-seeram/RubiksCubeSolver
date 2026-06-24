#include "Visualizer.h"
#include "Renderer.h"
#include "../cube/Cube.h"
#include "raylib.h"
#include "Button.h"
#include "../solver/Solver.h"
#include <vector>

void Visualizer::run()
{
    InitWindow(1000, 800, "Rubiks Cube Solver");
    SetTargetFPS(60);

    Cube cube;
    Renderer renderer;
    Solver solver;

    Button scrambleButton = {{50, 680, 120, 40}, "Scramble"};
    Button solveButton    = {{190, 680, 120, 40}, "Solve"};
    Button resetButton    = {{330, 680, 120, 40}, "Reset"};
    Button stopButton     = {{470, 680, 120, 40}, "Stop"};

    Button spd1 = {{620, 680, 55, 40}, "0.25x"};
    Button spd2 = {{680, 680, 55, 40}, "0.5x"};
    Button spd3 = {{740, 680, 55, 40}, "1x"};
    Button spd4 = {{800, 680, 55, 40}, "2x"};
    Button spd5 = {{860, 680, 55, 40}, "4x"};

    std::vector<Button*> uiButtons = {
        &scrambleButton, &solveButton, &resetButton, &stopButton,
        &spd1, &spd2, &spd3, &spd4, &spd5
    };

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        float dt = GetFrameTime();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (scrambleButton.isHovered(mouse))
            {
                scrambleStr = "R U F2 D' L B2"; 
                appStatus = "Scrambled";
            }
            else if (solveButton.isHovered(mouse))
            {
                currentResult = solver.solve(cube);
                solutionStr = "B2 D' L F2 U'"; 
                appStatus = "Solving";
                animController.start(currentResult.solution);
            }
            else if (resetButton.isHovered(mouse))
            {
                cube.reset();
                animController.stop();
                appStatus = "Idle";
                scrambleStr = "";
                solutionStr = "";
                inputBuffer = "";
                currentResult = SolveResult();
            }
            else if (stopButton.isHovered(mouse))
            {
                animController.stop();
                appStatus = "Stopped";
            }
            else if (spd1.isHovered(mouse)) { currentSpeed = 0.25f; animController.setSpeed(0.25f); }
            else if (spd2.isHovered(mouse)) { currentSpeed = 0.5f;  animController.setSpeed(0.5f); }
            else if (spd3.isHovered(mouse)) { currentSpeed = 1.0f;  animController.setSpeed(1.0f); }
            else if (spd4.isHovered(mouse)) { currentSpeed = 2.0f;  animController.setSpeed(2.0f); }
            else if (spd5.isHovered(mouse)) { currentSpeed = 4.0f;  animController.setSpeed(4.0f); }
        }

        int key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (inputBuffer.length() < 40))
            {
                inputBuffer += (char)key;
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !inputBuffer.empty())
        {
            inputBuffer.pop_back();
        }

        animController.update(dt, cube);
        if (!animController.isPlaying() && appStatus == "Solving")
        {
            appStatus = "Solved";
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Rubik's Cube Solver", 340, 25, 32, DARKGRAY);

        renderer.drawCube(cube);

        int panelX = 720;
        DrawText("STATUS PANEL", panelX, 100, 20, BLACK);
        DrawLine(panelX, 125, panelX + 220, 125, LIGHTGRAY);
        
        DrawText(("Status: " + appStatus).c_str(), panelX, 140, 18, DARKGRAY);
        DrawText(("Length: " + std::to_string(currentResult.solution.size())).c_str(), panelX, 170, 18, DARKGRAY);
        DrawText(("Nodes: " + std::to_string(currentResult.nodesExpanded)).c_str(), panelX, 200, 18, DARKGRAY);
        DrawText(("Time: " + std::to_string(currentResult.solveTimeMs) + " ms").c_str(), panelX, 230, 18, DARKGRAY);
        DrawText("Algorithm: IDA*", panelX, 260, 18, DARKGRAY);

        DrawText("Scramble Sequence:", 50, 480, 18, BLACK);
        DrawText(scrambleStr.empty() ? "None" : scrambleStr.c_str(), 50, 510, 18, RED);

        DrawText("Solution Sequence:", 50, 550, 18, BLACK);
        DrawText(solutionStr.empty() ? "None" : solutionStr.c_str(), 50, 580, 18, BLUE);

        DrawText("Input Scramble:", 450, 480, 18, BLACK);
        DrawRectangleLines(450, 510, 220, 35, DARKGRAY);
        DrawText(inputBuffer.c_str(), 460, 518, 18, BLACK);

        DrawText("Speed Control:", 620, 650, 16, DARKGRAY);

        for (const auto* btn : uiButtons)
        {
            Color btnColor = btn->isHovered(mouse) ? LIGHTGRAY : GRAY;
            DrawRectangleRec(btn->bounds, btnColor);
            DrawRectangleLinesEx(btn->bounds, 1.0f, BLACK);
            DrawText(btn->text.c_str(), btn->bounds.x + 12, btn->bounds.y + 10, 16, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
}