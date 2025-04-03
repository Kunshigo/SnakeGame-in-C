#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// game resolution
#define WIDTH 70
#define HEIGHT 35
#define MAX_SNAKE_LENGTH 100

// directions
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

int i, j, k;
int x, y, foodX, foodY, score;
int snakeX[MAX_SNAKE_LENGTH], snakeY[MAX_SNAKE_LENGTH];
int snakeLength;
int direction;
char choice;

void menu();

void gameOv(){
    printf("\t\t\t+---------+\n");
    printf("\t\t\t|GAME OVER|\n");
    printf("\t\t\t+---------+\n");
    printf("Score: %d\n", score);
    printf("Do you want to retry? (y/n): ");
    char retry = getchar();
    getchar();

    if (retry == 'y' || retry == 'y') {
        system("cls");
        setup();
    } else {
        system("cls");
        menu();
    }
}

void menu()
{
    char choice;
    printf("\nSNAKE GAME Version 1.0  ");
    printf("\n\n");
    printf("\n1. Play Game ");
    printf("\n2. Exit ");
    printf("\n\n");
    printf("\nEnter Your Choice :=> ");
    choice = getchar();
    getchar();

    if (choice == '1') {
        setup();
    }
    else if (choice == '2') {
        exit(0);
    }
    else {
        system("cls");
        printf("\nInvalid Option Try Again...");
        printf("\n\n");
        menu();
    }
}

void setup() {
    x = WIDTH / 2;
    y = HEIGHT / 2;
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
    score = 0;
    snakeLength = 1;
    direction = RIGHT;
}

void gotoxy(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void draw() {
    gotoxy(0, 0);
    hideCursor();

    for (i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");

            if (i == y && j == x)
                printf("O");
            else if (i == foodY && j == foodX)
                printf("F");
            else {
                int isBodyPart = 0;
                for (k = 0; k < snakeLength; k++) {
                    if (snakeX[k] == j && snakeY[k] == i) {
                        printf("o");
                        isBodyPart = 1;
                    }
                }
                if (!isBodyPart) {
                    printf(" ");
                }
            }

            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");


    printf("Score: %d\n", score);
    fflush(stdout);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                if (direction != DOWN) direction = UP;
                break;
            case 's':
                if (direction != UP) direction = DOWN;
                break;
            case 'a':
                if (direction != RIGHT) direction = LEFT;
                break;
            case 'd':
                if (direction != LEFT) direction = RIGHT;
                break;
            case 'x':
                exit(0);
        }
    }
}

void logic() {
    int prevX = snakeX[0];
    int prevY = snakeY[0];
    int prev2X, prev2Y;
    snakeX[0] = x;
    snakeY[0] = y;

    for (i = 1; i < snakeLength; i++) {
        prev2X = snakeX[i];
        prev2Y = snakeY[i];
        snakeX[i] = prevX;
        snakeY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
         gameOv();
    }

    for (i = 0; i < snakeLength; i++) {
        if (snakeX[i] == x && snakeY[i] == y) {
            gameOv();
        }
    }

    if (x == foodX && y == foodY) {
        score += 1;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        snakeLength++;
    }
}

int main() {
    menu();
    setup();
    while (1) {
        draw();
        input();
        logic();
        Sleep(10);
    }

    return 0;
}
