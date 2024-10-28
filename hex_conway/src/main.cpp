#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <cmath>

struct Hexagon {
  Vector2 position;
  float   radius;
};

void DrawHexagon(const Vector2& center, float radius, Color color)
{
  Vector2 points[6];
  for (int i = 0; i < 6; i++) {
    float angle = (M_PI / 3) * i; // 60 degrees
    points[i]
      = {center.x + radius * cos(angle), center.y + radius * sin(angle)};
  }
  DrawPoly(center, 6, radius, 0, color);
}


const int   GRID_WIDTH  = 10;
const int   GRID_HEIGHT = 10;
const float HEX_RADIUS  = 20.0f;

std::vector<std::vector<Vector2>>
  hexPositions(GRID_WIDTH, std::vector<Vector2>(GRID_HEIGHT));

void InitializeHexGrid()
{
  for (int q = 0; q < GRID_WIDTH; q++) {
    for (int r = 0; r < GRID_HEIGHT; r++) {
      float x            = HEX_RADIUS * 1.5f * q;
      float y            = HEX_RADIUS * sqrt(3) * (r + (q % 2) * 0.5f);
      hexPositions[q][r] = {x, y};
    }
  }
}

int CountAliveNeighbors(const std::vector<std::vector<int>>& grid, int q, int r)
{
  const int directions[6][2]
    = {{1, 0}, {0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, -1}};

  int count = 0;
  for (const auto& dir: directions) {
    int neighborQ = q + dir[0];
    int neighborR = r + dir[1];
    if (neighborQ >= 0 && neighborQ < GRID_WIDTH && neighborR >= 0
        && neighborR < GRID_HEIGHT) {
      count += grid[neighborQ][neighborR];
    }
  }
  return count;
}

void UpdateGrid(std::vector<std::vector<int>>& grid)
{
  std::vector<std::vector<int>> newGrid(GRID_WIDTH,
                                        std::vector<int>(GRID_HEIGHT, 0));

  for (int q = 0; q < GRID_WIDTH; q++) {
    for (int r = 0; r < GRID_HEIGHT; r++) {
      int aliveNeighbors = CountAliveNeighbors(grid, q, r);
      if (grid[q][r] == 1) {
        newGrid[q][r] = (aliveNeighbors == 2 || aliveNeighbors == 3) ? 1 : 0;
      }
      else {
        newGrid[q][r] = (aliveNeighbors == 3) ? 1 : 0;
      }
    }
  }
  grid = std::move(newGrid);
}


int main()
{
  InitWindow(800, 600, "Hexagonal Conway's Game of Life");

  std::vector<std::vector<int>> grid(GRID_WIDTH,
                                     std::vector<int>(GRID_HEIGHT, 0));
  // Initialize grid with some alive cells for testing...

  InitializeHexGrid();

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE)) {
      UpdateGrid(grid);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int q = 0; q < GRID_WIDTH; q++) {
      for (int r = 0; r < GRID_HEIGHT; r++) {
        Color color = grid[q][r] == 1 ? BLACK : LIGHTGRAY;
        DrawHexagon(hexPositions[q][r], HEX_RADIUS, color);
      }
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
