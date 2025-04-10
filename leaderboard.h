// leaderboard.h
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#define MAX_SCORES 10
#define MAX_NAME_LENGTH 20
#define LEADERBOARD_FILE "leaderboard.txt" // Changed the filename

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} ScoreEntry;

void loadLeaderboard();
void saveLeaderboard();
void addScore(const char *name, int score);
void displayLeaderboard();
void deleteScore();

#endif // LEADERBOARD_H
