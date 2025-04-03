#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#define WIDTH 70
#define HEIGHT 35

// Directions (using #define as requested)
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// Snake segment (node)
typedef struct SnakeSegment {
    int x;
    int y;
    struct SnakeSegment* next;
} SnakeSegment;

// Snake structure
typedef struct {
    SnakeSegment* head;
    SnakeSegment* tail;
    int direction;  // Changed from enum to int
    int length;
    int score;
} Snake;

// Food structure
typedef struct {
    int x;
    int y;
} Food;

// Function declarations
void init_game(Snake* snake, Food* food);
void draw(const Snake* snake, const Food* food);
void process_input(Snake* snake);
void update_game(Snake* snake, Food* food);
bool check_collision(const Snake* snake);
void free_snake(Snake* snake);
void gotoxy(int x, int y);
void hideCursor();

#endif
