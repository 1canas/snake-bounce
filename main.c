#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int** allocateTable();
void mountTable(int** table);
void printTable(int** table, int rowSize, int colSize);
void setRandomSeed(unsigned int value);
int isOnTableLimit(int positionX, int positionY);
int kbhit();

int main(void) {
    int keyBind = 0, isOnLimit = 0, snakeChar = 219, viewChar = 32, foodChar = 206;
    int snakeXLimit = 1, snakeYLimit = 1, snakeYPosition = 10, snakeXPosition = 10, foodXPosition, foodYPosition; 
    int snakeSize = 2, foodBool = 0, tailCount = 0, snakeTailX[2000], snakeTailY[2000];

    int** table = allocateTable();

    setRandomSeed(snakeSize);

    mountTable(table);

    while (1) {
        if (kbhit()) {
            keyBind = getchar();
        }

        printTable(table, 25, 50);

        isOnLimit = isOnTableLimit(snakeXPosition, snakeYPosition);
        if (isOnLimit) {
            break;
        }
        
        snakeTailX[tailCount] = snakeXPosition;
        snakeTailY[tailCount] = snakeYPosition;
        tailCount++;

        if (!foodBool) {
            foodYPosition = rand() % 23;
            foodXPosition = rand() % 48;
            table[foodYPosition][foodXPosition] = foodChar;

            foodBool = 1;
        }

        if (snakeXPosition == foodXPosition && snakeYPosition == foodYPosition) {
            foodBool = 0;
            snakeSize++;
        } else {
            snakeXLimit = snakeTailX[tailCount-snakeSize];
            snakeYLimit = snakeTailY[tailCount-snakeSize];
        }

        if (keyBind == 100) { // right
            snakeXPosition++;
        }

        if (keyBind == 97) { // left
            snakeXPosition--;
        }

        if (keyBind == 115) { // down
            snakeYPosition++;
        }

        if (keyBind == 119) { // up
            snakeYPosition--;
        }

        table[snakeYPosition][snakeXPosition] = snakeChar;
        table[snakeYLimit][snakeXLimit] = viewChar;

        usleep(110000);

        system("clear");
    }
    
    system("clear");

    return 0;
}

void setRandomSeed(unsigned int value) {
    srand(value);
}

int** allocateTable() {
    int** table = (int**) malloc(sizeof(int*) * 24);
    for (int row = 0; row < 25; row++) {
        table[row] = (int*) malloc(sizeof(int) * 49);
    }

    return table;
}

int isOnTableLimit(int xPosition, int yPosition) {
    if (xPosition == 0 || xPosition == 49 || \
        yPosition == 0 || yPosition == 24) {
        return 1;
    }
    
    return 0;
}

void mountTable(int** table) {
    int viewChar = 32, limitChar = 219;

    for (int row = 0; row < 25; row++) {
        for (int col = 0; col < 50; col++) {
            table[row][col] = viewChar;
        }
    }

    for (int row = 0; row < 25; row++) {
        table[row][0] = limitChar;
        table[row][49] = limitChar;
    }

    for (int col = 0; col < 50; col++) {
        table[0][col] = limitChar;
        table[24][col] = limitChar;
    }
}

void printTable(int** table, int rowSize, int colSize) {
    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {
            printf("%c", table[row][col]);
        }

        printf("\n");
    }
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    fd_set readfds;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
    
    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return 1; 
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0; 
}