#include <cstdlib>
#include <deque>
#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

using namespace std;

struct coordinates {
  int x;
  int y;

  coordinates(int x, int y) : x(x), y(y) {}
};

// clang-format off
template <typename T, typename Container = deque<T> >
// clang-format on

deque<coordinates> snakeBody;

bool gameOver;
const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score = 0;

enum Direction { STOP = 0, UP, DOWN, LEFT, RIGHT };
Direction dir;

void Setup() {
  gameOver = false;
  initscr();
  start_color();
  curs_set(0);
  noecho();
  keypad(stdscr, TRUE);
  timeout(100);
  refresh();
  dir = STOP;
  x = width / 2;
  y = height / 2;
  fruitX = rand() % (width - 2) + 1;
  fruitY = rand() % (height - 2) + 1;
}

void Draw() {

  clear();

  mvprintw(0, 0, "####################");

  for (int i = 1; i < height - 1; ++i) {
    mvprintw(i, 0, "#");
    mvprintw(i, width - 1, "#");
  }
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(3));

  deque<coordinates>::iterator it;
  for (it = snakeBody<coordinates>.begin(); it != snakeBody<coordinates>.end();
       ++it) {
    coordinates c = *it;
    mvprintw(c.x, c.y, "o");
  }
  mvprintw(x, y, "O");

  init_pair(1, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(1));
  mvprintw(fruitX, fruitY, "*");

  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  attron(COLOR_PAIR(2));

  mvprintw(height - 1, 0, "####################");

  refresh();
}

void Input() {
  int ch = getch();
  switch (ch) {
  case 'w':
    if (dir != DOWN) {
      dir = UP;
    }
    break;
  case 'a':
    if (dir != RIGHT) {
      dir = LEFT;
    }
    break;
  case 's':
    if (dir != UP) {
      dir = DOWN;
    }
    break;
  case 'd':
    if (dir != LEFT) {
      dir = RIGHT;
    }
    break;
  default:
    break;
  }
}

bool checkPosition(coordinates coor, deque<coordinates> snake) {
  deque<coordinates>::iterator it;

  for (it = snakeBody<coordinates>.begin(); it != snakeBody<coordinates>.end();
       ++it) {
    coordinates c = *it;

    if (c.x == coor.x && c.y == coor.y) {
      return false;
    }
  }
  return true;
}

void Logic() {
  switch (dir) {
  case UP:
    x--;
    break;
  case DOWN:
    x++;
    break;
  case RIGHT:
    y++;
    break;
  case LEFT:
    y--;
    break;
  default:
    break;
  }

  if (!checkPosition(coordinates(x, y), snakeBody<coordinates>)) {
    gameOver = true;
    return;
  }

  snakeBody<coordinates>.push_back(coordinates(x, y));

  if (x == 0) {
    snakeBody<coordinates>.pop_back();
    x = height - 1;
    snakeBody<coordinates>.push_back(coordinates(x, y));
  } else if (x == height - 1) {
    snakeBody<coordinates>.pop_back();
    x = 1;
    snakeBody<coordinates>.push_back(coordinates(x, y));
  } else if (y == 0) {
    snakeBody<coordinates>.pop_back();
    y = width - 2;
    snakeBody<coordinates>.push_back(coordinates(x, y));
  } else if (y == width - 1) {
    snakeBody<coordinates>.pop_back();
    y = 1;
    snakeBody<coordinates>.push_back(coordinates(x, y));
  }

  if (fruitY == y && fruitX == x) {
    score += 10;
    while (
        !checkPosition(coordinates(fruitX, fruitY), snakeBody<coordinates>)) {
      fruitX = rand() % (width - 2) + 1;
      fruitY = rand() % (height - 2) + 1;
    }
  } else {
    snakeBody<coordinates>.pop_front();
  }
}

int main() {

  Setup();
  while (!gameOver) {
    Draw();
    Input();
    Logic();
    this_thread::sleep_for(chrono::milliseconds(100));
  }
  clear();
  cout << endl << "SCORE: " << score << endl;

  char c = getchar();
  endwin();
  return 0;
}
