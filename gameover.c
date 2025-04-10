#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include "leaderboard.h" 

void gameOv(SnakeNode* head) {
    printf("\t\t\t+---------+\n");
    printf("\t\t\t|GAME OVER|\n");	
    printf("\t\t\t+---------+\n");
    int score;
    printf("Score: %d\n", score); // Assuming 'score' is still globally accessible or passed

    // Get player's name
    char playerName[MAX_NAME_LENGTH];
    printf("Enter your name: ");
    fgets(playerName, MAX_NAME_LENGTH, stdin);
    playerName[strcspn(playerName, "\n")] = 0; // Remove trailing newline

    // Add score to the leaderboard
    addScore(playerName, score);

    // Display the leaderboard
    displayLeaderboard();

    printf("Do you want to retry? (y/n): ");
    char retry = getchar();
    getchar(); // Consume the newline character

    freeSnake(head); // Free the memory allocated for the snake

    if (retry == 'y' || retry == 'Y') {
        system("cls");
        // setup() will be called again from main
    } else {
        system("cls");
        menu();
    }
}
