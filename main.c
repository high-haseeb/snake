#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 10

int head_x = 0;
int head_y = 0;
int score = 0;
int gameover = 0;

void draw(void);
void setup(void);
void gameloop(void);
void drawSnake(void);
void update(void);

int main(void) {
  // setup();
  gameloop();
  return 0;
}

void gameloop(void) {
  while (!gameover) {
    draw();
    update();
  }
}
void update(void) {
  switch (getch()) {
    case KEY_UP:
      head_y += 1;
      break;
    case KEY_DOWN:
      head_y -= 1;
      break;
    case KEY_LEFT:
      head_x += 1;
      break;
    case KEY_RIGHT:
      head_x -= 1;
      break;
  }
  return;
}
void setup(void) { draw(); }
void draw(void) {
  system("clear");
  for (int i = 0; i < COLS; i++)
    printf("_");

  printf("\n");
  for (int i = 0; i < ROWS; i++) {
    printf("|");
    for (int j = 0; j < COLS; j++) {
      if (i == head_y && j == head_x) {
        printf("#");
      } else {
        printf(" ");
      }
    }
    printf("|\n");
  }

  for (int i = 0; i < COLS; i++)
    printf("_");

  printf("\n");
}
