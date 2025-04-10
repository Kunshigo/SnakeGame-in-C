#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "snake.h"

int main() {
    srand(time(NULL));
    menu();

    SnakeNode* snakeHead = setup();
    int foodX = rand() % WIDTH;
    int foodY = rand() % HEIGHT;
    int score = 0;
    int currentDirection = RIGHT; // Keep track of the current direction
    int gameOver = 0;

    while (!gameOver) {
        draw(snakeHead, foodX, foodY, score);

        if (_kbhit()) {
            int newDirection = _getch();
            switch (newDirection) {
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
        }

        // Adjust sleep based on the *current* direction
        if (currentDirection == UP || currentDirection == DOWN) {
            Sleep(30);
        } else {
            Sleep(10);
        }

        snakeHead = logic(snakeHead, currentDirection, &foodX, &foodY, &score, &gameOver);
    }

    gameOv(snakeHead);
    return 0;
}
