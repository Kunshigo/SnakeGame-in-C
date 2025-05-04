#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "snake.h"

int frameDelay = 100; // Default to Normal
char currentDifficulty[16] = "Normal";

void setDifficulty() {
    int choice;
    printf("\n==============================\n");
    printf("   SELECT DIFFICULTY\n");
    printf("==============================\n");
    printf(" 1. Easy   (Slower)\n");
    printf(" 2. Normal (Default)\n");
    printf(" 3. Hard   (Faster)\n");
    printf(" 4. Custom (Enter ms per frame)\n");
    printf("------------------------------\n");
    printf(" Enter choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline
    switch (choice) {
        case 1:
            frameDelay = 150;
            strcpy(currentDifficulty, "Easy");
            break;
        case 2:
            frameDelay = 100;
            strcpy(currentDifficulty, "Normal");
            break;
        case 3:
            frameDelay = 60;
            strcpy(currentDifficulty, "Hard");
            break;
        case 4:
            printf(" Enter ms per frame (e.g. 80): ");
            scanf("%d", &frameDelay);
            getchar();
            strcpy(currentDifficulty, "Custom");
            break;
        default:
            printf(" Invalid choice. Defaulting to Normal.\n");
            frameDelay = 100;
            strcpy(currentDifficulty, "Normal");
    }
    printf("------------------------------\n");
    printf(" Difficulty set to %s (%d ms/frame)\n", currentDifficulty, frameDelay);
    printf("==============================\n");
}

void menu() {
    int choice;
    do {
        system("cls");
        printf("\n========================================\n");
        printf("         S N A K E   G A M E\n");
        printf("========================================\n");
        printf("| 1. Play Game                      |\n");
        printf("| 2. Leaderboard                    |\n");
        printf("| 3. Exit                           |\n");
        printf("========================================\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline
        switch (choice) {
            case 1:
                return; // Difficulty will be prompted in main.c
            case 2:
                displayLeaderboard();
                printf("Press Enter to return to the menu...");
                getchar();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf(" Invalid choice. Try again.\n");
        }
    } while (1);
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
