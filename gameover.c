#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include "leaderboard.h" 

void gameOv(SnakeNode* head, int score) {
    printf("\t\t\t+---------+\n");
    printf("\t\t\t|GAME OVER|\n");	
    printf("\t\t\t+---------+\n");
    printf("Score: %d\n", score);

    showCursor(); // Show cursor for user input
    // Get player's name
    char playerName[MAX_NAME_LENGTH];
    printf("Enter your name: ");
    fgets(playerName, MAX_NAME_LENGTH, stdin);
    playerName[strcspn(playerName, "\n")] = 0; // Remove trailing newline

    // Add score to the leaderboard
    addScore(playerName, score);

    // Display the leaderboard
    displayLeaderboard();

    freeSnake(head); // Free the memory allocated for the snake
    hideCursor(); // Hide cursor again if returning to game
}
