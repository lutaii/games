#include "raylib.h"
#include <cctype>
#include <cstdlib>

const double screen_width = 1280;
const double screen_height = 800;
Color background = Color{170, 69, 58, 255};

int p1_score = 0, p2_score = 0, cpu_score = 0;

struct Ball {
  float x, y, radius;
  int speed_x, speed_y;

  void draw() { DrawCircle(x, y, radius, WHITE); };

  void move() {
    x += speed_x;
    y += speed_y;

    if (x + radius >= screen_width || x - radius <= 0) {
      speed_x *= -1;
    }
    if (x - radius <= 0) {
      speed_x *= -1;
      p2_score++;
      reset();
    } else if (x + radius >= screen_width) {

      speed_x *= -1;
      p1_score++;
      cpu_score++;
      reset();
    }
    if (y + radius >= screen_height || y - radius <= 0) {
      speed_y *= -1;
    }
  }

  void reset() {
    x = screen_width / 2;
    y = screen_height / 2;
    int dir[2] = {-1, 1};
    speed_x *= dir[rand() % 2];
    speed_y *= dir[rand() % 2];
  }
};

Ball ball;

class Paddle {
public:
  double x, y, width, height, speed;

  virtual void move() = 0;

  void draw() {
    Rectangle rec;
    rec.x = x;
    rec.y = y;
    rec.width = width;
    rec.height = height;
    DrawRectangleRounded(rec, 0.8, 0, WHITE);
  };

  virtual ~Paddle() = default;
};

class Player1 : public Paddle {
public:
  void move() override {
    if (IsKeyDown(KEY_W)) {
      y = y - speed;
      if (y <= 0) {
        y = 0;
      }
    }
    if (IsKeyDown(KEY_S)) {
      y = y + speed;
      if (y >= screen_height - height) {
        y = screen_height - height;
      }
    }
  }
};

class Player2 : public Paddle {
public:
  void move() override {
    if (IsKeyDown(KEY_UP)) {
      y = y - speed;
      if (y <= 0) {
        y = 0;
      }
    }
    if (IsKeyDown(KEY_DOWN)) {
      y = y + speed;
      if (y >= screen_height - height) {
        y = screen_height - height;
      }
    }
  }
};

class Computer : public Paddle {
public:
  void move() override {
    if (y + height / 2 > ball.y) {
      y -= speed;
      if (y <= 0) {
        y = 0;
      }
    } else {
      y += speed;
      if (y >= screen_height - height) {
        y = screen_height - height;
      }
    }
  }
};

int main() {

  InitWindow(screen_width, screen_height, "Ping Pong Game");
  SetTargetFPS(120);

  ClearBackground(background);

  ball.x = screen_width / 2;
  ball.y = screen_height / 2;
  ball.radius = 20;
  ball.speed_x = 11;
  ball.speed_y = 14;

  Player1 p1;
  Player2 p2;
  Computer cpu;

  p1.height = 140;
  p1.width = 20;
  p2.height = 140;
  p2.width = 20;

  p1.x = 10;
  p1.y = screen_height / 2 - p1.height / 2;
  p1.speed = 10;

  p2.x = screen_width - p2.width - 10;
  p2.y = screen_height / 2 - p2.height / 2;
  p2.speed = 10;

  // CPU
  cpu.x = 10;
  cpu.y = screen_height / 2 - p1.height / 2;
  cpu.height = 140;
  cpu.width = 20;
  cpu.speed = 10;

  bool menu = true;
  bool isPVP;

  while (!WindowShouldClose()) {

    BeginDrawing();

    if (menu) {

      ClearBackground(background);
      DrawText(TextFormat("1. P v CPU"), screen_width / 2 - 120,
               screen_height / 2 - 100, 80, WHITE);
      DrawText(TextFormat("2. P v P"), screen_width / 2 - 120,
               screen_height / 2 + 60, 80, WHITE);
      if (IsKeyDown(KEY_ONE)) {
        isPVP = false;
        menu = false;
        ball.reset();
      }
      if (IsKeyDown(KEY_TWO)) {
        isPVP = true;
        menu = false;
        ball.reset();
      }
    } else {
      ball.move();
      if (isPVP) {

        p1.move();
      } else {
        cpu.move();
      }
      p2.move();

      if (IsKeyDown(KEY_BACKSPACE)) {
        menu = true;
        p1_score = 0;
        cpu_score = 0;
        p2_score = 0;
        ball.reset();
      }

      Rectangle rec1, rec2, rec3;
      rec1.x = p1.x;
      rec1.y = p1.y;
      rec1.width = p1.width;
      rec1.height = p1.height;

      rec2.x = p2.x;
      rec2.y = p2.y;
      rec2.width = p2.width;
      rec2.height = p2.height;

      rec3.x = cpu.x;
      rec3.y = cpu.y;
      rec3.width = cpu.width;
      rec3.height = cpu.height;

      if (isPVP) {
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                    rec1) ||
            CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                    rec2)) {
          ball.speed_x *= -1;
        }

      } else {

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                    rec3) ||
            CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                    rec2)) {
          ball.speed_x *= -1;
        }
      }

      ClearBackground(background);
      DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
      ball.draw();

      if (isPVP) {
        p1.draw();
      } else {
        cpu.draw();
      }
      p2.draw();

      DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80,
               WHITE);
      DrawText(TextFormat("%i", p2_score), 3 * screen_width / 4 - 20, 20, 80,
               WHITE);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
