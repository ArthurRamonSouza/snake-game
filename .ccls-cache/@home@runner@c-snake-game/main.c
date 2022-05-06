#include <stdio.h>
#include <stdlib.h>

#define R 20
#define C 60

int column, row, head, tail, snake_x, snake_y, game;
int fixBug = 0; // THe bottom is duplicated without this
int Field[C][R];

void snakeInitialization() {

  // Snake starting position, the head will be placed in coordinates
  // [snake_x][snake_y]
  snake_x = C / 2;
  snake_y = R / 2;
  head = 4;
  tail = 1;
  game = 0;
  
  
  // Putting the snake in the field
  for (row = 1; row <= snake_y; row++) {
    for (column = 1; column <= snake_x; column++) {
      if (row == snake_y && column == snake_x - head) {
        int node = tail;
        while (node <= head) {
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

  for (row = 1; row <= R; row++) {
    for (column = 0; column <= C + 1; column++) {
      if (column == 0 || column == C + 1) {
        printf("%c", 43);
      } else if (Field[column][row] == 0) {
        printf(" ");
      } else if (Field[column][row] > 0 && Field[column][row] != head) {
        printf("%c", 111);
      } else if (Field[column][row] == head) {
        printf("%c", 62);
      }
    }
    printf("\n");
  }
  makeTopAndBottom();
}

void resetScreenPosition(){
  printf("\033[%d;%dH", 0, 0);
  // THe bottom is duplicated without this
  if (fixBug == 0){
    system("clear");
    fixBug = 1;
  }
}

int main(void) {
  snakeInitialization();
  
  while (game == 0){
    createField();
    resetScreenPosition();
  }
  
  for (row = 1; row <= R; row++) {
    for (column = 1; column <= C; column++) {
      int array = Field[column][row];
      printf("%d", array);
    }
    printf("\n");
  }
  return 0;
}