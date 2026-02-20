#include "include/llogo.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
int main()
{
    InitWindow(800, 450, "Raylib - Move Along Angle");
    Vector2 position = { SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0 };
    float speed = 300.0f;
    float angle = -90.0f; // 0 is right, 90 is down
    SetTargetFPS(60);

    Vector2 position_source = { SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0 };

    float length = 50.0;
    Vector2 position_destination = {position_source.x + cosf(angle * DEG2RAD) * length, position_source.y + sinf(angle * DEG2RAD) * length};

    char command[100] = "fd 40";
    evaluate_command(command);
    memset(command, '\0', strlen(command));
    strcpy(command, "rt 90");
    evaluate_command(command);
    memset(command, '\0', strlen(command));
    strcpy(command, "fd 40");
    evaluate_command(command);
    show_all_paths();
    //evaluate_command("rt 90");
    //evaluate_command("fd 40");

    while (!WindowShouldClose()) {
        // Update angle (rotating with arrow keys)
        if (IsKeyDown(KEY_LEFT)) angle -= 3.0f;
        if (IsKeyDown(KEY_RIGHT)) angle += 3.0f;

        position_destination.x = position_source.x + cosf(angle * DEG2RAD) * length;
        position_destination.y = position_source.y + sinf(angle * DEG2RAD) * length;

        // Move forward in the current angle direction
        if (IsKeyDown(KEY_UP)) {
            position.x += cosf(angle * DEG2RAD) * speed * GetFrameTime();
            position.y += sinf(angle * DEG2RAD) * speed * GetFrameTime();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw object (a triangle pointing right, rotated)
        DrawPoly(position, 3, 20, angle, MAROON);
        DrawText("Use Arrows to Rotate/Move", 10, 10, 20, DARKGRAY);
        DrawLineV(position_source, position_destination, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}