#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <vector>

class Walker
{
public:
  Walker()

  {
    pos.x = GetRandomValue(0, GetScreenWidth());
    pos.y = GetRandomValue(0, GetScreenHeight());
  }

  void update()
  {
    path.push_back(pos);
    const float x = GetRandomValue(-100, 100) / 100.0f;
    const float y = GetRandomValue(-100, 100) / 100.0f;

    const auto move = Vector2{x, y};

    pos = Vector2Add(pos, move);
  }

  void draw()
  {
    DrawLineStrip(path.data(), path.size(), BLUE);
    DrawCircle(pos.x, pos.y, 3, RED);
  }

private:
  Vector2              pos;
  std::vector<Vector2> path;
};


int main(void)
{
  // Initialization
  const int screenWidth  = 800;
  const int screenHeight = 600;

  SetTargetFPS(60);

  InitWindow(screenWidth, screenHeight, "raylib [core] example");

  std::vector<Walker> walkers;

  for (int i = 0; i < 100; ++i) {
    Walker w;
    walkers.push_back(w);
  }

  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    for (auto& w: walkers) {
      w.update();
    }
    // Draw
    {
      BeginDrawing();
      ClearBackground(RAYWHITE);
      for (auto& w: walkers) {
        w.draw();
      }
      EndDrawing();
    }
  }

  CloseWindow();

  return 0;
}