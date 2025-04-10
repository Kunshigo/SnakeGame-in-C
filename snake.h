#ifndef SNAKE_H
#define SNAKE_H

#define WIDTH 70
#define HEIGHT 35

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

typedef struct SnakeNode {
    int x;
    int y;
    struct SnakeNode* next;
} SnakeNode;

int i, j;
void menu();
void gameOv(SnakeNode* head);
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

#endif // SNAKE_H
