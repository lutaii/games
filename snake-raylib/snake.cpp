#include "raylib.h"
#include <cstdlib>
#include <deque>
#include <iostream>

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Snake {
  deque<Vector2> body = {{6, 9}, {5, 9}, {4, 9}};

public:
  void draw() {
    for (int i = 0; i < body.size(); i++) {
      int x = body[i].x;
      int y = body[i].y;

      DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, darkGreen);
    }
  }
};

class Food {

public:
  Vector2 position;
  Texture2D texture;

  // load texture
  Food() { position = generateRandomPosition(); }

  // unload texture
  ~Food() {}

  void draw() {
    DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize,
                  cellSize, darkGreen);
  }

  Vector2 generateRandomPosition() {
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);
    return {x, y};
  }
};

int main() {
  InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake");
  SetTargetFPS(60);

  Food food = Food();
  Snake snake = Snake();

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(green);
    food.draw();
    snake.draw();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
