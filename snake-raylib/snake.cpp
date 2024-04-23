#include "raylib.h"
#include "raymath.h"
#include <cstdlib>
#include <deque>
#include <iostream>

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
double lastUpdateTime = 0;

bool eventTriggered(double interval) {
  double currentTime = GetTime();
  if (currentTime - lastUpdateTime >= interval) {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
}

class Snake {
  deque<Vector2> body = {{6, 9}, {5, 9}, {4, 9}};

  Vector2 direction = {1, 0};

public:
  void draw() {
    for (int i = 0; i < body.size(); i++) {
      float x = body[i].x;
      float y = body[i].y;

      DrawRectangleRounded(
          {x * cellSize, y * cellSize, (float)cellSize, (float)cellSize}, 0.5,
          6, darkGreen);
    }
  }

  void update() {
    body.pop_back();
    body.push_front(Vector2Add(body[0], direction));
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

    if (eventTriggered(0.2)) {
      snake.update();
    }

    ClearBackground(green);
    food.draw();
    snake.draw();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
