#include <stdio.h>

#define EMPTY_MASK "TODO"
#define MARKED_BLACK_MASK "TODO"
#define MARKED_WHITE_MASK "TODO"

typedef enum {EMPTY, MARKED_BLACK, MARKED_WHITE} Square;
typedef enum {BLACK, WHITE} Player;

typedef struct {
  Player p;
  Square grid[8][8];
} Board;

static char ledGrid[3][8]; //initialize to all 0's
static Board states[2];
static int currState = 0;

//Input coordinate conversion
//Mb make these macros
int numToX(int n) {
  //TODO: Depends on PCB  
}
int numToY(int n) {
  //TODO: Depends on PCB  
}

//Game logic (also updates internal global state :3)
void initializeBoard(Board *b) {
  int x,y;
  for (x = 0; x < 8; x++) {
    for (y = 0; y < 8; y++) {
      if (((x == 3) && (y == 3)) ||
	  ((x == 4) && (y == 4))) {
	b->grid[x][y] = MARKED_WHITE;
      } else if (((x == 3) && (y == 4)) ||
		 ((x == 4) && (y == 3))) {
	b->grid[x][y] = MARKED_BLACK;
      } else {
	b->grid[x][y] = EMPTY;
      }
    }
  }
}

void makeMove(int x, int y) {
  int backup = (currState == 0) ? 1 : 0;
  int xi, yi;
  Board * b = &states[currState];
  Player enemy = (b->p == WHITE) ? BLACK : WHITE;
  Square color = (b->p == WHITE) ? MARKED_WHITE : MARKED_BLACK;

  if (isLegal(x,y) == 0) {
    return;
  }

  //Move is legal, so we should back up our state before making the move
  for (xi = 0; xi < 8; xi++) {
    for (yi = 0; yi < 8; yi++) {
      states[backup].grid[xi][yi] = b->grid[xi][yi];
    }
  }

  //it's legal, so mark the square
  b->grid[x][y] = color;
  b->p = enemy;//swap turns

  //NORTH
  xi = x - 1;
  yi = y;
  while ((xi < 8) && (yi < 8) &&
	 (b->grid[xi][yi] != EMPTY)) {
    if (b->grid[xi][yi] == color) {
      //flip back to my spot
      for (xi = xi + 1; xi != x; xi++) {
	b->grid[xi][yi] = color;
      }
      break;
    } else {
      xi--;//move north
    }
  }

  //NORTHEAST
  xi = x - 1;
  yi = y + 1;
  while ((xi < 8) && (yi < 8) &&
	 (b->grid[xi][yi] != EMPTY)) {
    if (b->grid[xi][yi] == color) {
      //flip back to spot
      for (xi = xi + 1, yi = yi - 1; (xi != x) && (yi != y); xi++, yi--) {
	printf("%d %d\n", xi, yi);
	b->grid[xi][yi] = color;
      }
      break;
    } else {
      xi--;//move north
      yi++;//move east
    }
  }

  //EAST
  xi = x;
  yi = y + 1;
  while ((xi < 8) && (yi < 8) &&
	 (b->grid[xi][yi] != EMPTY)) {
    if (b->grid[xi][yi] == color) {
      //flip back to my spot
      for (yi = yi - 1; yi != y; yi--) {
	printf("%d %d\n", xi, yi);
	b->grid[xi][yi] = color;
      }
      break;
    } else {
      yi++;//move east
    }
  }

  //SOUTHEAST
  xi = x + 1;
  yi = y + 1;
  while ((xi < 8) && (yi < 8) &&
	 (b->grid[xi][yi] != EMPTY)) {
    if (b->grid[xi][yi] == color) {
      //flip back to spot
      for (xi = xi - 1, yi = yi - 1; xi != x, yi != y; xi--, yi--) {
	b->grid[xi][yi] = color;
      }
      break;
    } else {
      xi++;//move south
      yi++;//move east
    }
  }

  //SOUTH
  xi = x + 1;
  yi = y;
  while ((xi < 8) && (yi < 8) &&
	 (b->grid[xi][yi] != EMPTY)) {
    if (b->grid[xi][yi] == color) {
      //flip back to spot
      for (xi = xi - 1; xi != x; xi--) {
	b->grid[xi][yi] = color;
      }
      break;
    } else {
      xi++;//move south
    }
  }

  //SOUTHWEST
  xi = x + 1;
  yi = y - 1;
  while ((xi < 8) && (yi < 8) &&
	 (b->grid[xi][yi] != EMPTY)) {
    if (b->grid[xi][yi] == color) {
      //flip back to spot
      for (xi = xi - 1, yi = yi + 1; xi != x, yi != y; xi--, yi++) {
	b->grid[xi][yi] = color;
      }
      break;
    } else {
      xi++;//move south
      yi--;//move west
    }
  }


  //WEST
  xi = x;
  yi = y - 1;
  while ((xi < 8) && (yi < 8) &&
	 (b->grid[xi][yi] != EMPTY)) {
    if (b->grid[xi][yi] == color) {
      //flip back to my spot
      for (yi = yi + 1; yi != y; yi++) {
	b->grid[xi][yi] = color;
      }
      break;
    } else {
      yi--;//move west
    }
  }

  //NORTHEAST
  xi = x - 1;
  yi = y - 1;
  while ((xi < 8) && (yi < 8) &&
	 (b->grid[xi][yi] != EMPTY)) {
    if (b->grid[xi][yi] == color) {
      //flip back to spot
      for (xi = xi + 1, yi = yi + 1; xi != x, yi != y; xi++, yi++) {
	b->grid[xi][yi] = color;
      }
      break;
    } else {
      xi--;//move north
      yi--;//move west
    }
  }
}

int isLegal(int x, int y) {
  return 1;
}

int gameOver(Board *b) {
  //do we even care about game over?
  //PSSCs say no (t'-'t)
}

//LED output logic
void boardToLED(Board * b) {
  
}

//
void legalMovesToLED(Board *b) {
  
}

void undo() {
  if (currState == 0) {
    currState = 1;
  } else {
    currState = 0;
  }
}

//non-embedded helpers
void printBoard(Board *b) {
  int x,y;
  char out;
  printf("  0 1 2 3 4 5 6 7\n");
  for (x = 0; x < 8; x++) {
    printf("%d ", x);
    for (y = 0; y < 8; y++) {
      switch(b->grid[x][y]) {
      case EMPTY:
	out = '-';
	break;
      case MARKED_BLACK:
	out = '*';
	break;
      case MARKED_WHITE:
	out = 'O';
	break;
      default:
	out = '?';
      }
      printf("%c ", out);
    }
    printf("%d\n", x);
  }
  printf("  0 1 2 3 4 5 6 7\n");
  if (b->p == BLACK) {
    printf("To move: * BLACK\n");
  } else {
    printf("To move: O WHITE\n");
  }
}

int main (int argc, char ** argv) {
  initializeBoard(&states[currState]);
  printBoard(&states[currState]);
  makeMove(2,3);
  printBoard(&states[0]);
  makeMove(2,2);
  printBoard(&states[currState]);
  makeMove(3,2);
  printBoard(&states[currState]);
  makeMove(4,2);
  printBoard(&states[currState]);
  makeMove(5,1);
  printBoard(&states[currState]);
  makeMove(3,5);
  printBoard(&states[currState]);
  makeMove(2,4);
  printBoard(&states[currState]);
  makeMove(4,1);
  printBoard(&states[currState]);
  makeMove(5,5);
  printBoard(&states[currState]);
  return 0;
}
