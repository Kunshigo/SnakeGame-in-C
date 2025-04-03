#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>


int i, j;

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void init_game(Snake* snake, Food* food) {
    SnakeSegment* head = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    head->x = WIDTH / 2;
    head->y = HEIGHT / 2;
    head->next = NULL;
    
    snake->head = head;
    snake->tail = head;
    snake->direction = RIGHT;
    snake->length = 1;
    snake->score = 0;
    
    food->x = rand() % WIDTH;
    food->y = rand() % HEIGHT;
}

void draw(const Snake* snake, const Food* food) {
    gotoxy(0, 2);
    hideCursor();
    
    for (i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (j == 0) printf("#");

            if (snake->head->x == j && snake->head->y == i) {
                printf("O");
            }
            else if (food->x == j && food->y == i) {
                printf("F");
            }
            else {
                SnakeSegment* current = snake->head->next;
                bool isBodyPart = false;
                
                while (current != NULL) {
                    if (current->x == j && current->y == i) {
                        printf("o");
                        isBodyPart = true;
                        break;
                    }
                    current = current->next;
                }
                
                if (!isBodyPart) printf(" ");
            }

            if (j == WIDTH - 1) printf("#");
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    printf("Score: %d\n", snake->score);
}

void process_input(Snake* snake) {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                if (snake->direction != DOWN) snake->direction = UP;
                break;
            case 's':
                if (snake->direction != UP) snake->direction = DOWN;
                break;
            case 'a':
                if (snake->direction != RIGHT) snake->direction = LEFT;
                break;
            case 'd':
                if (snake->direction != LEFT) snake->direction = RIGHT;
                break;
            case 'x':
                exit(0);
        }
    }
}

void move_snake(Snake* snake) {
    SnakeSegment* new_head = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    new_head->next = snake->head;
    
    switch(snake->direction) {
        case UP:
            new_head->x = snake->head->x;
            new_head->y = snake->head->y - 1;
            break;
        case DOWN:
            new_head->x = snake->head->x;
            new_head->y = snake->head->y + 1;
            break;
        case LEFT:
            new_head->x = snake->head->x - 1;
            new_head->y = snake->head->y;
            break;
        case RIGHT:
            new_head->x = snake->head->x + 1;
            new_head->y = snake->head->y;
            break;
    }
    
    snake->head = new_head;
    snake->length++;
}

void grow_snake(Snake* snake) {
    move_snake(snake);
}

void update_snake(Snake* snake) {
    move_snake(snake);
    
    SnakeSegment* current = snake->head;
    while(current->next != snake->tail) {
        current = current->next;
    }
    
    free(snake->tail);
    current->next = NULL;
    snake->tail = current;
    snake->length--;
}

bool check_food_collision(const Snake* snake, const Food* food) {
    return (snake->head->x == food->x && snake->head->y == food->y);
}

bool check_collision(const Snake* snake) {
    if (snake->head->x < 0 || snake->head->x >= WIDTH ||
        snake->head->y < 0 || snake->head->y >= HEIGHT) {
        return true;
    }
    
    SnakeSegment* current = snake->head->next;
    while(current != NULL) {
        if (current->x == snake->head->x && current->y == snake->head->y) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

void update_game(Snake* snake, Food* food) {
    if (check_food_collision(snake, food)) {
        grow_snake(snake);
        snake->score += 10;
        food->x = rand() % WIDTH;
        food->y = rand() % HEIGHT;
    } else {
        update_snake(snake);
    }
}

void free_snake(Snake* snake) {
    SnakeSegment* current = snake->head;
    while(current != NULL) {
        SnakeSegment* next = current->next;
        free(current);
        current = next;
    }
}
