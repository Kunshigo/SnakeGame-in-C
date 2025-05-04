#ifndef SNAKE_H
#define SNAKE_H

#define WIDTH 70
#define HEIGHT 35

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// ANSI color codes
#define ANSI_RESET   "\x1b[0m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_WHITE   "\x1b[37m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_BOLD    "\x1b[1m"

void enableAnsiColors();

typedef struct SnakeNode {
    int x;
    int y;
    struct SnakeNode* next;
} SnakeNode;

int i, j;
void menu();
void gameOv(SnakeNode* head, int score);
SnakeNode* setup();
void gotoxy(int x, int y);
void hideCursor();
void draw(SnakeNode* head, int foodX, int foodY, int score);
int input(int currentDirection);
SnakeNode* logic(SnakeNode* head, int direction, int* foodX, int* foodY, int* score, int* gameOver);
void freeSnake(SnakeNode* head);

// Global constants
extern const char SNAKE_HEAD_CHAR;
extern const char SNAKE_BODY_CHAR;
extern const char FOOD_CHAR;
extern const char WALL_CHAR;

extern int lastDirection;
extern int frameDelay;
extern char currentDifficulty[16];
void setDifficulty();

#endif // SNAKE_H
