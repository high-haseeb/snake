#include <curses.h>
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 40

bool gameover = false;
float speed = 0.001;
int score = 0;

struct Snake {
  float head_x;
  float head_y;
  char dir;
  int body[ROWS + COLS][2];
  int length;
};
struct Food {
  int x;
  int y;
};
struct Snake snake;
struct Food food;
void init(void) {
  snake.head_y = 5;
  snake.head_x = 10;
  snake.length = 0;
  food.x = rand() % COLS;
  food.y = rand() % ROWS;
}
void draw(void) {
  move(0, 0);
  refresh();
  printw("  score:>>> %i\n", score);
  for (int i = 0; i < COLS + 2; i++)
    printw("_");

  printw("\n");
  for (int y = 0; y < ROWS; y++) {
    addstr("|");
    for (int x = 0; x < COLS; x++) {
      if ((int)snake.head_y == y && (int)snake.head_x == x) {
        addstr("#");
      } else if (food.x == x && food.y == y) {
        addstr("O");
      } else {
        for (int l = 0; l < snake.length; l++) {
          if (snake.body[l][0] == x && snake.body[l][1] == y)
            addstr("x");
        }
      }
      addstr(" ");
    }
    addstr("|\n");
  }

  for (int i = 0; i < COLS + 2; i++)
    printw("_");
}
void update(void) {
  switch (snake.dir) {
  case 'N':
    snake.head_y -= speed;
    break;
  case 'S':
    snake.head_y += speed;
    break;
  case 'E':
    snake.head_x += speed;
    break;
  case 'W':
    snake.head_x -= speed;
    break;
  }
  for (int i = score; i > 0; i--) {
    snake.body[i][0] = snake.body[i - 1][0];
    snake.body[i][1] = snake.body[i - 1][1];
  }
  snake.body[0][0] = (int)snake.head_x;
  snake.body[0][1] = (int)snake.head_y;
}
void input(void) {
  int chr = getch();
  switch (chr) {
  case KEY_UP:
    snake.dir = 'N';
    break;
  case KEY_DOWN:
    snake.dir = 'S';
    break;
  case KEY_LEFT:
    snake.dir = 'W';
    break;
  case KEY_RIGHT:
    snake.dir = 'E';
    break;
  }
}
void spawnFood(void) {
  food.x = rand() % COLS;
  food.y = rand() % ROWS;
}
void logic(void) {
  if (snake.head_x <= 0 || snake.head_x >= COLS || snake.head_y <= 0 ||
      snake.head_y >= ROWS) {
    gameover = true;
  }
  if ((int)snake.head_x == food.x && (int)snake.head_y == food.y) {
    score++;
    spawnFood();
  }
}
int main() {
  initscr(); // init ncurses window
  init();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  while (!gameover) {
    input();
    update();
    draw();
    logic();
  }
  printw("you lost motherfucker!! you pussy ass noob");
  return 0;
}
