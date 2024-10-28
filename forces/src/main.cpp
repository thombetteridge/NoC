#include <raylib.h>

#include "mover.hpp"

int main(void)
{
  // Initialization
  const int screenWidth  = 800;
  const int screenHeight = 600;

  SetTargetFPS(60);

  InitWindow(screenWidth, screenHeight, "raylib example");

  auto m = Mover({screenWidth / 2.0, screenHeight / 2.0}, {0, 0});

  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    m.apply_force(Vector2{0, -1});
    m.update(GetFrameTime());
    // Draw
    {
      BeginDrawing();
      ClearBackground(RAYWHITE);
      m.draw();
      EndDrawing();
    }
  }

  // De-Initialization
  CloseWindow(); // Close window and OpenGL context

  return 0;
}