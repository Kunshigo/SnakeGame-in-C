#include "snake.h"
#include <windows.h>

int main() {
    Snake snake;
    Food food;
    
    init_game(&snake, &food);
    
    while (1) {
        draw(&snake, &food);
        process_input(&snake);
        update_game(&snake, &food);
        
        if (check_collision(&snake)) {
            gotoxy(WIDTH / 2, HEIGHT / 2);
            printf("GAME OVER! Final Score: %d", snake.score);
            break;
        }
        
        Sleep(10); //adjustable game speed
    }
    
    free_snake(&snake);
    return 0;
}
