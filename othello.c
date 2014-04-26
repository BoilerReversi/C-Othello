#define EMPTY_MASK "TODO"
#define MARKED_BLACK_MASK "TODO"
#define MARKED_WHITE_MASK "TODO"

typedef enum {EMPTY, MARKED_BLACK, MARKED_WHITE} Square;
typedef enum {BLACK, WHITE} Player;

typedef struct {
  Player p;
  Square grid[8][8];
} Board;

static char[3][8] ledGrid;//initialize to all 0's
static Board[2] states;
static int currState = 0;

//Input coordinate conversion
//Mb make these macros
int numToX(int n) {
  
}
int numToY(int n) {
  
}

//Game logic (also updates internal global state :3)
void initializeBoard(Board *b) {
  
}

void makeMove(Board * b, int x, int y) {
  
  //be sure to make a copy so we can undo
}

int isLegal(Board *b, int x, int y) {
  
}

int gameOver(Board *b) {
  
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
  boardToLED(states[currState]);
}


//non-embedded helpers
void printBoard(Board *b) {

}
