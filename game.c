#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "snake.h"

// ANSI color codes
#define ANSI_RESET   "\x1b[0m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_WHITE   "\x1b[37m"
#define ANSI_BOLD    "\x1b[1m"

const char SNAKE_HEAD_CHAR = 'O';
const char SNAKE_BODY_CHAR = 'o';
const char FOOD_CHAR = 'F';
const char WALL_CHAR = '#';
const int FRAME_DELAY = 100; // milliseconds between frames

// Buffer for the game screen to reduce flicker
char screenBuffer[HEIGHT][WIDTH + 2];

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void showCursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {100, TRUE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Initialize the screen buffer
void initScreenBuffer() {
    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH + 2; j++) {
            if (j == 0 || j == WIDTH + 1) {
                screenBuffer[i][j] = WALL_CHAR;
            } else {
                screenBuffer[i][j] = ' ';
            }
        }
    }
}

SnakeNode* setup() {
    int initialLength = 3; // Start with a length of 3
    int startX = WIDTH / 2;
    int startY = HEIGHT / 2;
    int i;

    SnakeNode* head = (SnakeNode*)malloc(sizeof(SnakeNode));
    if (!head) {
        perror("Failed to allocate memory for snake head");
        exit(EXIT_FAILURE);
    }
    head->x = startX;
    head->y = startY;
    head->next = NULL;

    SnakeNode* current = head;
    for (i = 1; i < initialLength; i++) {
        SnakeNode* newSegment = (SnakeNode*)malloc(sizeof(SnakeNode));
        if (!newSegment) {
            perror("Failed to allocate memory for snake segment");
            exit(EXIT_FAILURE);
        }
        newSegment->x = startX - i; // Add segments to the left
        newSegment->y = startY;
        newSegment->next = NULL;
        current->next = newSegment;
        current = newSegment;
    }
    return head;
}

void draw(SnakeNode* head, int foodX, int foodY, int score) {
    int i, j;
    char output[(HEIGHT + 10) * (WIDTH * 4)];
    char* ptr = output;

    // Title banner
    ptr += sprintf(ptr, "\n  =============================\n");
    ptr += sprintf(ptr,   "        S N A K E   G A M E    \n");
    ptr += sprintf(ptr,   "  =============================\n");

    // Top border
    ptr += sprintf(ptr, "+");
    for (i = 0; i < WIDTH; i++) ptr += sprintf(ptr, "--");
    ptr += sprintf(ptr, "+\n");

    // Game area
    for (i = 0; i < HEIGHT; i++) {
        ptr += sprintf(ptr, "|");
        for (j = 0; j < WIDTH; j++) {
            char ch = ' ';
            SnakeNode* current = head;
            int isHead = 1;
            while (current != NULL) {
                if (current->x == j && current->y == i) {
                    ch = isHead ? 'O' : 'o';
                    break;
                }
                current = current->next;
                isHead = 0;
            }
            if (foodX == j && foodY == i) ch = '@';
            ptr += sprintf(ptr, "%c ", ch); // Add space for clarity
        }
        ptr += sprintf(ptr, "|\n");
    }

    // Bottom border
    ptr += sprintf(ptr, "+");
    for (i = 0; i < WIDTH; i++) ptr += sprintf(ptr, "--");
    ptr += sprintf(ptr, "+\n");

    // Separator
    ptr += sprintf(ptr, "----------------------------------------\n");

    // Score, difficulty, and controls
    ptr += sprintf(ptr, "Score: %d   Difficulty: %s\n", score, currentDifficulty);
    ptr += sprintf(ptr, "Controls: W/A/S/D to move, X to exit\n");

    *ptr = '\0';
    gotoxy(0, 0);
    fputs(output, stdout);
    fflush(stdout);
}

int lastDirection = RIGHT;

int input(int currentDirection) {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                if (currentDirection != DOWN) currentDirection = UP;
                break;
            case 's':
                if (currentDirection != UP) currentDirection = DOWN;
                break;
            case 'a':
                if (currentDirection != RIGHT) currentDirection = LEFT;
                break;
            case 'd':
                if (currentDirection != LEFT) currentDirection = RIGHT;
                break;
            case 'x':
                exit(0);
        }
        lastDirection = currentDirection;
    }
    return currentDirection;
}

SnakeNode* logic(SnakeNode* head, int direction, int* foodX, int* foodY, int* score, int* gameOver) {
    int headX = head->x;
    int headY = head->y;

    switch (direction) {
        case UP:
            headY--;
            break;
        case DOWN:
            headY++;
            break;
        case LEFT:
            headX--;
            break;
        case RIGHT:
            headX++;
            break;
    }

    // Check wall collision
    if (headX < 0 || headX >= WIDTH || headY < 0 || headY >= HEIGHT) {
        *gameOver = 1;
        return head;
    }

    // Check self collision (optimized to only check body parts)
    SnakeNode* current = head->next;
    while (current != NULL) {
        if (current->x == headX && current->y == headY) {
            *gameOver = 1;
            return head;
        }
        current = current->next;
    }

    // Create new head
    SnakeNode* newHead = (SnakeNode*)malloc(sizeof(SnakeNode));
    if (!newHead) {
        perror("Failed to allocate memory for new snake head");
        exit(EXIT_FAILURE);
    }
    newHead->x = headX;
    newHead->y = headY;
    newHead->next = head;
    head = newHead;

    // Check food collision
    if (headX == *foodX && headY == *foodY) {
        (*score)++;
        // Generate new food position (ensuring it's not on the snake)
        do {
            *foodX = rand() % WIDTH;
            *foodY = rand() % HEIGHT;
            current = head;
            while (current != NULL) {
                if (current->x == *foodX && current->y == *foodY) {
                    *foodX = -1; // Force regeneration
                    break;
                }
                current = current->next;
            }
        } while (*foodX == -1);
    } else {
        // Remove tail
        SnakeNode* temp = head;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
    }

    return head;
}

void freeSnake(SnakeNode* head) {
    SnakeNode* current = head;
    SnakeNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
