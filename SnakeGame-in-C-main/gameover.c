
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  
#include "snake.h"
#include "leaderboard.h"


char gameOv(SnakeNode* head, int finalScore) { 


Sleep(500); 
printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");

    printf("\n\n");
    printf("+---------+\n");
    printf("|GAME OVER|\n");
    printf("+---------+\n\n");
    printf("Your Score: %d\n\n", finalScore);

    // Get player's name
    char playerName[MAX_NAME_LENGTH];
    printf("Enter your name: ");
   
    fflush(stdin);
    fgets(playerName, MAX_NAME_LENGTH, stdin);
    playerName[strcspn(playerName, "\n")] = 0; 

    addScore(playerName, finalScore);
    displayLeaderboard();

    char choice;
    printf("\nPlay again? (y/n): ");
    fflush(stdin);
    choice = getchar();
    getchar(); 

    freeSnake(head); 

    return tolower(choice); 
}

