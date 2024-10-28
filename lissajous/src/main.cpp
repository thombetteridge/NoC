#include <raylib.h>
#include <math.h>
#include <rlgl.h>

#include <vector>
#include <array>

class Curve
{
public:
  Curve()
  {}

  void set_x(float x)
  {
    current.x = x;
  }

  void set_y(float y)
  {
    current.y = y;
  }

  void add_point(float x, float y)
  {
    const Vector2 p{x, y};
    v.push_back(p);
  }

  void add_point()
  {
    v.push_back(current);
    current = Vector2{};
  }

  void draw()
  {
    // const auto lw = rlGetLineWidth();
    DrawLineStrip(v.data(), v.size(), BLACK);
    // rlSetLineWidth(lw);
  }

  void reset()
  {
    v.clear();
    current = Vector2{};
  }

private:
  std::vector<Vector2> v;
  Vector2              current;
};

/******************************************************************************/
int main(void)
{
  // Initialization
  const int screenWidth  = 600;
  const int screenHeight = 600;

  float     angle = 0;
  const int w     = 60;
  const int cols  = screenWidth / w - 1;
  const int rows  = screenHeight / w - 1;

  std::array<std::array<Curve, cols>, rows> grid;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      grid[i][j] = Curve();
    }
  }

  SetTargetFPS(60);

  InitWindow(screenWidth, screenHeight, "raylib example");

  rlSetLineWidth(2);

  // Main game loop
  while (!WindowShouldClose()) {
    // Update

    angle += 0.01;

    if (angle > 2 * PI) {
      angle = 0;
      for (auto& row: grid) {
        for (auto& curve: row) {
          curve.reset();
        }
      }
    }
    // Draw

    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < cols; ++i) {
      const float cx     = w + i * w + w / 2.0;
      const float cy     = w / 2.0;
      const float radius = (w / 2.0) - 5.0;
      DrawCircleLines(cx, cy, radius, BLACK);

      const float x = radius * cos(angle * (i + 1) - PI / 2.0);
      const float y = radius * sin(angle * (i + 1) - PI / 2.0);
      DrawCircle(cx + x, cy + y, 4, BLACK);

      for (int j = 0; j < rows; ++j) {
        grid[j][i].set_x(cx + x);
      }
    }
    for (int j = 0; j < rows; ++j) {
      const float cx     = w / 2.0;
      const float cy     = w + j * w + w / 2.0;
      const float radius = (w / 2.0) - 5.0;
      DrawCircleLines(cx, cy, radius, BLACK);

      const float y = radius * sin(angle * (j + 1) - PI / 2.0);
      const float x = radius * cos(angle * (j + 1) - PI / 2.0);
      DrawCircle(cx + x, cy + y, 4, BLACK);

      for (int i = 0; i < cols; ++i) {
        grid[j][i].set_y(cy + y);
      }
    }

    for (auto& row: grid) {
      for (auto& curve: row) {
        curve.add_point();
        curve.draw();
      }
    }

    EndDrawing();
  }

  // De-Initialization
  // CloseWindow();

  return 0;
}