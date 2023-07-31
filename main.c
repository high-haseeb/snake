#include <stdio.h>
#define ROWS 10
#define COLS 10

int head_x;
int head_y;
int score;
int gameover;

// draw game boundaries
void drawBounds(void);
// initialize everything
void setup(void);

int main(void) {
  setup();
  return 0;
}

void setup(void) { drawBounds(); }
void drawBounds(void) {
  for (int i = 0; i < COLS; i++)
    printf("_");

  printf("\n");
  for (int i = 0; i < ROWS; i++) {
    printf("|");
    for (int j = 0; j < COLS; j++) {
      printf(" ");
    }
    printf("|\n");
  }

  for (int i = 0; i < COLS; i++)
    printf("_");

  printf("\n");
}
