#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R 20
#define C 60

// Main variables
int column, row, head, tail, snake_x, snake_y, game, apple, apple_x, apple_y;
int fixBug = 0; // THe bottom is duplicated without this
int Field[C][R];

void snakeInitialization() {

  // Snake starting position, the head will be placed in coordinates[snake_x][snake_y]
  snake_x = C / 2;
  snake_y = R / 2;
  head = 4;
  tail = 1;
  game = 0;
  apple_x = 1 + rand() % 18;
  apple_y = 1 + rand() % 58;

  // Putting the snake in the field
  for (row = 1; row <= snake_y; row++) {
    for (column = 1; column <= snake_x; column++) {
      if (row == snake_y && column == snake_x - head) {
        int node = tail;
        while (node <= head) {
          system("setterm -foreground yellow");
          Field[column][row] = node;
          node++;
          column++;
        }
      } else {
          // Assigning value of 0 to empty spaces
          Field[column][row] = 0; 
        }
    }
  }
}

// Make the top and bottom edge
void makeTopAndBottom() {
  for (column = 0; column <= C + 1; column++) {
    if (column == 0 || column == C + 1) {
      printf("%c", 43);
    } else {
      printf("%c", 45);
    }
  }
  printf("\n");
}

void createField() {
  makeTopAndBottom();

  for (row = 1; row < R; row++) {
    for (column = 0; column <= C + 1; column++) {
      if (column == 0 || column == C + 1) {
        system("setterm -foreground green");
        printf("%c", 43);
      } else if (Field[column][row] == 0) {
        printf(" ");
      } else if (Field[column][row] > 0 && Field[column][row] != head) {
        printf("%c", 111);
      } else if (Field[column][row] == -1) {
        printf("%c", 64);
      } else if (Field[column][row] == head) {
        printf("%c", 62);
      }
    }
    printf("\n");
  }
  makeTopAndBottom();
}

void resetScreenPosition() {
  printf("\033[%d;%dH", 0, 0);
  // THe bottom is duplicated without this
  if (fixBug == 0) {
    system("clear");
    fixBug = 1;
  }
}

void foodGenerator() {
  srand(time(0)); // Generating random numbers from the time
  apple_x = rand() % R;
  apple_y = rand() % C;

  // If there is no apple on the screen and the space is empty, the space gets -1
  if (apple == 0 && Field[apple_x][apple_y] == 0) {
    Field[apple_x][apple_y] = -1;
    apple = 1;
  }
}

int main(void) {
  snakeInitialization();

  for (row = 1; row < R; row++) {
    for (column = 1; column <= C; column++) {
      int array = Field[column][row];
      printf("%d", array);
    }
    printf("\n");
  }

  while (game == 0) {
    createField();
    resetScreenPosition();
    foodGenerator();
  }

  return 0;
}