#include <raylib.h>

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "raylib example");

    // Main game loop
    while (!WindowShouldClose()) {
        // Update

        // Draw
        {
            BeginDrawing();
            // ClearBackground(RAYWHITE);
            EndDrawing();
        }
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}