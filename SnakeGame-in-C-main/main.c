// In main.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "snake.h"
#include "leaderboard.h" // Make sure leaderboard is included if menu uses it

int main() {
    srand(time(NULL));
    char playAgainChoice;

    // Show the initial menu only once before starting the game loop
    menu();

    do {
        // --- Game Setup ---
        SnakeNode* snakeHead = setup();
        int foodX = rand() % WIDTH;
        int foodY = rand() % HEIGHT;
        int score = 0;
        int currentDirection = RIGHT;
        int gameOver = 0;
        hideCursor(); // Hide cursor at the start of each game

        // --- Game Loop ---
        while (!gameOver) {
            draw(snakeHead, foodX, foodY, score);

            if (_kbhit()) {
                int newDirection = _getch();
                switch (newDirection) {
                    case 'w':
                    case 'W': // Add uppercase check
                        if (currentDirection != DOWN) currentDirection = UP;
                        break;
                    case 's':
                    case 'S': // Add uppercase check
                        if (currentDirection != UP) currentDirection = DOWN;
                        break;
                    case 'a':
                    case 'A': // Add uppercase check
                        if (currentDirection != RIGHT) currentDirection = LEFT;
                        break;
                    case 'd':
                    case 'D': // Add uppercase check
                        if (currentDirection != LEFT) currentDirection = RIGHT;
                        break;
                    case 'x':
                    case 'X': // Add uppercase check for exit
                        gameOver = 1; // Set game over to exit loop cleanly
                        playAgainChoice = 'n'; // Ensure we don't retry
                        break;
                }
            }

            // Adjust sleep based on the *current* direction
            if (currentDirection == UP || currentDirection == DOWN) {
                Sleep(90); // Adjusted speed for vertical
            } else {
                Sleep(50); // Adjusted speed for horizontal
            }

             // Only update logic if the game is not already over from input 'x'
            if (!gameOver) {
                 snakeHead = logic(snakeHead, currentDirection, &foodX, &foodY, &score, &gameOver);
            }
             // Ensure snakeHead is not NULL before proceeding if logic could return NULL
             if (snakeHead == NULL) {
                 gameOver = 1; // Handle case where snake might become NULL
             }
        } // --- End of Game Loop ---

        // Check if game over was triggered by 'x' key, if so, skip gameOv
        if (playAgainChoice != 'n') {
             playAgainChoice = gameOv(snakeHead, score); // Call game over screen and get choice
        }


    } while (playAgainChoice == 'y'); // Continue loop only if user entered 'y'

    system("cls");
    printf("\nReturning to main menu...\n");
    Sleep(600); 
    system("cls");
    main(); 
    return 0; 
}
