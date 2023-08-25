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

void spawnFood(void) {
  food.x = rand() % COLS;
  food.y = rand() % ROWS;
}

void init(void) {
  snake.head_y = 5;
  snake.head_x = 10;
  snake.length = 0;
  spawnFood();
}

bool drawBody(int x, int y) {
  for (int l = 0; l < score; l++) 
    if (snake.body[l][0] == x && snake.body[l][1] == y)
      return true;
  return false;
}
void draw(void) {
  move(0, 0);
  refresh();
  printw("  score:>>> %i\n", score);
  printw("  X:>>> %i y:>>> %i\n", (int)snake.head_x, (int)snake.head_y);
  printw("  X:>>> %i y:>>> %i\n", (int)snake.body[1][0], (int)snake.body[1][1]);

  for (int i = 0; i < COLS + 2; i++)
    printw("_");

  printw("\n");
  for (int y = 0; y < ROWS; y++) {
    addstr("|");
    for (int x = 0; x < COLS; x++) {
      if ((int)snake.head_y == y && (int)snake.head_x == x) {
        addstr("@");
      } else if (food.x == x && food.y == y) {
        addstr("O");
      } else if (drawBody(x, y)) {
        addstr("*");
      } else {
        addstr(" ");
      }
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

  if (snake.body[0][0] == (int)snake.head_x &&
    snake.body[0][1] == (int)snake.head_y) return;

  for (int i = score; i > 0; i--) {
    snake.body[i][0] = snake.body[i - 1][0];
    snake.body[i][1] = snake.body[i - 1][1];
  }
  snake.body[0][0] = (int)snake.head_x;
  snake.body[0][1] = (int)snake.head_y;
}
char inputDir = 'R';
void input(void) {

  int chr = getch();
  if (chr == ERR)
    return;

  switch (chr) {
  case KEY_UP:
    inputDir = 'N';
    break;
  case KEY_DOWN:
    inputDir = 'S';
    break;
  case KEY_LEFT:
    inputDir = 'W';
    break;
  case KEY_RIGHT:
    inputDir = 'E';
    break;
  }
  if (inputDir == 'N' && snake.dir == 'S') return;
  if (inputDir == 'S' && snake.dir == 'N') return;
  if (inputDir == 'W' && snake.dir == 'E') return;
  if (inputDir == 'E' && snake.dir == 'W') return;
  snake.dir = inputDir;
}
void logic(void) {
  if (snake.head_x <= 0 || snake.head_x >= COLS 
    || snake.head_y <= 0 || snake.head_y >= ROWS) gameover = true;

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
    draw();
    update();
    logic();
  }
  printw("you lost motherfucker!! you pussy ass noob");
  return 0;
}
