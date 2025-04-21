#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "snake.h"
 
const char SNAKE_HEAD_CHAR = 'O';
const char SNAKE_BODY_CHAR = 'o';
const char FOOD_CHAR = 'F';
const char WALL_CHAR = '#';

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
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
    gotoxy(0, 0);
    hideCursor();

    for (i = 0; i < WIDTH + 2; i++) {
        printf("%c", WALL_CHAR);
    }
    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("%c", WALL_CHAR);

            SnakeNode* current = head;
            int isBodyPart = 0;
            int isHead = 1;
            while (current != NULL) {
                if (current->y == i && current->x == j) {
                    printf("%c", isHead ? SNAKE_HEAD_CHAR : SNAKE_BODY_CHAR);
                    isBodyPart = 1;
                    break;
                }
                current = current->next;
                isHead = 0;
            }

            if (!isBodyPart) {
                if (i == foodY && j == foodX)
                    printf("%c", FOOD_CHAR);
                else
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("%c", WALL_CHAR);
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH + 2; i++) {
        printf("%c", WALL_CHAR);
    }
    printf("\n");

    printf("Score: %d\n", score);
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

    if (headX < 0 || headX >= WIDTH || headY < 0 || headY >= HEIGHT) {
        *gameOver = 1;
        return head;
    }

    SnakeNode* current = head;
    while (current != NULL) {
        if (current != head && current->x == headX && current->y == headY) {
            *gameOver = 1;
            return head;
        }
        current = current->next;
    }

    SnakeNode* newHead = (SnakeNode*)malloc(sizeof(SnakeNode));
    if (!newHead) {
        perror("Failed to allocate memory for new snake head");
        exit(EXIT_FAILURE);
    }
    newHead->x = headX;
    newHead->y = headY;
    newHead->next = head;
    head = newHead;

    if (headX == *foodX && headY == *foodY) {
        (*score)++;
        *foodX = rand() % WIDTH;
        *foodY = rand() % HEIGHT;
    } else {
        SnakeNode* temp = head;
        if (temp == NULL) return NULL;
        if (temp->next == NULL) {
            free(temp);
            return NULL; // snake died? should not happen in normal gameplay
        }
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
