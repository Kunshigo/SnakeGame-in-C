#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "snake.h"

int main() {
    int currentDirection;
    int gameOver;
    int score;
    int foodX, foodY;
    SnakeNode* snakeHead;
    char playAgain = 'y';
    DWORD frameStart, frameEnd, frameElapsed, frameDelayLocal;

    srand((unsigned int)time(NULL));
    menu();
    hideCursor();

    while (playAgain == 'y' || playAgain == 'Y') {
        setDifficulty();
        snakeHead = setup();
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        score = 0;
        currentDirection = RIGHT;
        gameOver = 0;

        while (!gameOver) {
            frameStart = GetTickCount();

            // Input
            if (_kbhit()) {
                int newDirection = _getch();
                switch (newDirection) {
                    case 'w': if (currentDirection != DOWN) currentDirection = UP; break;
                    case 's': if (currentDirection != UP) currentDirection = DOWN; break;
                    case 'a': if (currentDirection != RIGHT) currentDirection = LEFT; break;
                    case 'd': if (currentDirection != LEFT) currentDirection = RIGHT; break;
                    case 'x': gameOver = 1; break;
                }
            }

            snakeHead = logic(snakeHead, currentDirection, &foodX, &foodY, &score, &gameOver);
            draw(snakeHead, foodX, foodY, score);

            // Frame timing
            frameEnd = GetTickCount();
            frameElapsed = frameEnd - frameStart;
            frameDelayLocal = frameDelay > frameElapsed ? frameDelay - frameElapsed : 1;
            Sleep(frameDelayLocal);
        }

        gameOv(snakeHead, score);

        printf("Do you want to play again? (y/n): ");
        playAgain = getchar();
        getchar();
        system("cls");
        if (playAgain != 'y' && playAgain != 'Y') {
            menu();
            playAgain = 'y'; // So the loop can continue if the user chooses to play again from the menu
        }
    }

    showCursor();
    return 0;
}
