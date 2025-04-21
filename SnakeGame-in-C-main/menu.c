#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "snake.h"

void menu() {
    char choice;
    printf("\nSNAKE GAME Version 1.2 ");
    printf("\n\n");
    printf("\n1. Play Game ");
    printf("\n2. View Leaderboard ");
    printf("\n3. Exit ");
    printf("\n\n");
    printf("\nEnter Your Choice :=> ");
    choice = getchar();
    getchar(); // Consume the newline character

    switch (choice) {
        case '1':
            // setup() will be called from main
            break;
        case '2':
            displayLeaderboardMenu(); // Call the new leaderboard menu function
            break;
        case '3':
            exit(0);
        default:
            system("cls");
            printf("\nInvalid Option Try Again...");
            printf("\n\n");
            menu();
    }
}	

void displayLeaderboardMenu() {
    char choice;
    system("cls");
    displayLeaderboard();
    printf("\nLeaderboard Options:\n");
    printf("1. Delete a Score\n");
    printf("2. Return to Main Menu\n");
    printf("\nEnter your choice: ");
    choice = getchar();
    getchar(); // Consume the newline

    switch (choice) {
        case '1':
            deleteScore();
            printf("Press any key to return to the Leaderboard Menu...");
            getch();
            displayLeaderboardMenu(); // Go back to the leaderboard menu
            break;
        case '2':
            system("cls");
            menu(); // Return to the main menu
            break;
        default:
            printf("Invalid option. Press any key to return to the Leaderboard Menu...");
            getch();
            displayLeaderboardMenu(); // Go back to the leaderboard menu
            break;
    }
}
