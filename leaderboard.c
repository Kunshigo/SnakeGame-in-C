// leaderboard.c
#include "leaderboard.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For isdigit

static ScoreEntry leaderboard[MAX_SCORES];
static int numScores = 0;

// Comparison function for sorting scores in descending order
int compareScores(const void *a, const void *b) {
    return ((ScoreEntry *)b)->score - ((ScoreEntry *)a)->score;
}

void loadLeaderboard() {
    FILE *file = fopen(LEADERBOARD_FILE, "r");
    if (file == NULL) {
        numScores = 0;
        return;
    }

    numScores = 0;
    while (numScores < MAX_SCORES &&
           fscanf(file, "%s %d", leaderboard[numScores].name, &leaderboard[numScores].score) == 2) {
        numScores++;
    }
    fclose(file);
    qsort(leaderboard, numScores, sizeof(ScoreEntry), compareScores);
}

void saveLeaderboard() {
    FILE *file = fopen(LEADERBOARD_FILE, "w");
    if (file == NULL) {
        printf("Error opening leaderboard file for saving!\n");
        return;
    }

    for (i = 0; i < numScores; i++) {
        fprintf(file, "%s %d\n", leaderboard[i].name, leaderboard[i].score);
    }
    fclose(file);
}

void addScore(const char *name, int score) {
    loadLeaderboard();
    int added = 0;
    if (numScores < MAX_SCORES) {
        strncpy(leaderboard[numScores].name, name, MAX_NAME_LENGTH - 1);
        leaderboard[numScores].name[MAX_NAME_LENGTH - 1] = '\0';
        leaderboard[numScores].score = score;
        numScores++;
        added = 1;
    } else {
        if (score > leaderboard[MAX_SCORES - 1].score) {
            strncpy(leaderboard[MAX_SCORES - 1].name, name, MAX_NAME_LENGTH - 1);
            leaderboard[MAX_SCORES - 1].name[MAX_NAME_LENGTH - 1] = '\0';
            leaderboard[MAX_SCORES - 1].score = score;
            added = 1;
        }
    }

    if (added) {
        qsort(leaderboard, numScores, sizeof(ScoreEntry), compareScores);
        saveLeaderboard();
    }
}

void displayLeaderboard() {
    loadLeaderboard();
    printf("\n========================================\n");
    printf("            LEADERBOARD\n");
    printf("========================================\n");

    if (numScores == 0) {
        printf("  No scores yet.\n");
    } else {
        printf("+-----+----------------------+-------+\n");
        printf("| #   | Name                 | Score |\n");
        printf("+-----+----------------------+-------+\n");
        for (i = 0; i < numScores; i++) {
            printf("| %-3d | %-20s | %-5d |\n", i + 1, leaderboard[i].name, leaderboard[i].score);
        }
        printf("+-----+----------------------+-------+\n");
    }
    printf("========================================\n");
}

void deleteScore() {
    loadLeaderboard();
    if (numScores == 0) {
        printf("Leaderboard is empty. Nothing to delete.\n");
        return;
    }

    displayLeaderboard();
    printf("Enter the number of the score to delete (or 0 to cancel): ");
    char input[10];
    fgets(input, sizeof(input), stdin);

    if (input[0] == '0' && (input[1] == '\n' || input[1] == '\0')) {
        printf("Deletion cancelled.\n");
        return;
    }

    int indexToDelete = -1;
    // Validate if the input is a number
    int is_number = 1;
    for (i = 0; input[i] != '\0' && input[i] != '\n'; i++) {
        if (!isdigit(input[i])) {
            is_number = 0;
            break;
        }
    }

    if (is_number) {
        indexToDelete = atoi(input);
        if (indexToDelete >= 1 && indexToDelete <= numScores) {
            // Adjust index to be 0-based
            indexToDelete--;

            // Shift the remaining scores to overwrite the deleted one
            for (i = indexToDelete; i < numScores - 1; i++) {
                leaderboard[i] = leaderboard[i + 1];
            }
            numScores--;
            printf("Score at position %d deleted.\n", indexToDelete + 1);
            saveLeaderboard(); // Update the file
        } else {
            printf("Invalid score number.\n");
        }
    } else {
        printf("Invalid input. Please enter a number.\n");
    }
}
