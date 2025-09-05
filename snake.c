#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define WIDTH 20
#define HEIGHT 10
int direction = 0; 
int snakeX[100], snakeY[100];
int snakeLength = 3;
int fruitX, fruitY;
int score = 0;
int randRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}
void placeFruit() {
    fruitX = randRange(1, WIDTH - 2);
    fruitY = randRange(1, HEIGHT - 2);
}
void initializeGame() {
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    snakeX[1] = WIDTH / 2 - 1;
    snakeY[1] = HEIGHT / 2;
    snakeX[2] = WIDTH / 2 - 2;
    snakeY[2] = HEIGHT / 2;
    placeFruit();
    score = 0;
}

void updateGame() {

    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

   
    switch (direction) {
        case 0: snakeX[0]++; break; 
        case 1: snakeY[0]--; break;
        case 2: snakeX[0]--; break; 
        case 3: snakeY[0]++; break; 
    }
    if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
        printf("Game Over!\n");
        exit(0);
    }
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            printf("Game Over!\n");
            exit(0);
        }
    }
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        score++;
        snakeLength++;
        placeFruit();
    }
}
void drawGame() {
    system("cls"); 
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");
    for (int y = 0; y < HEIGHT; y++) {
        printf("#"); 
        for (int x = 0; x < WIDTH; x++) {
            if (x == snakeX[0] && y == snakeY[0]) {
                printf("O"); 
            } else {
                int isSnakePart = 0;
                for (int i = 1; i < snakeLength; i++) {
                    if (x == snakeX[i] && y == snakeY[i]) {
                        printf("o"); 
                        isSnakePart = 1;
                        break;
                    }
                }
                if (!isSnakePart) {
                    if (x == fruitX && y == fruitY) {
                        printf("*"); 
                    } else {
                        printf(" ");
                    }
                }
            }
        }
        printf("#\n");
    }
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");
    printf("Score: %d\n", score);
}

int main() {
    srand(time(NULL));
    initializeGame();
    while (1) {
        drawGame();
        if (_kbhit()) {
            switch (_getch()) {
                case 'w': if (direction != 3) direction = 1; break; 
                case 's': if (direction != 1) direction = 3; break; 
                case 'a': if (direction != 0) direction = 2; break;
                case 'd': if (direction != 2) direction = 0; break; 
                case 'x': exit(0);
            }
        }
        updateGame();
        usleep(100000); 
    }

    return 0;
}