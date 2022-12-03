#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "utils.h"

void mountTable(int** table);

int main(void) {
    int keyBind, snakeChar = 219, viewChar = 32, foodChar = 206;
    int snakeXLimit = 1, snakeYLimit = 1, snakeYPosition = 10, snakeXPosition = 10, foodXPosition, foodYPosition; 
    int snakeSize = 2, foodBool = 0, tailCount = 0, snakeTailX[2000], snakeTailY[2000];

    int** table = (int**) malloc(sizeof(int*) * 24);
    for (int row = 0; row < 25; row++) {
        table[row] = (int*) malloc(sizeof(int) * 49);
    }

    srand(snakeSize);

    mountTable(table);

    while (1) {
        if (kbhit()) {
            keyBind = getch();
        }

        printTable(table, 25, 50);

        if (snakeXPosition == 0 || snakeXPosition == 49 || \
            snakeYPosition == 0 || snakeYPosition == 24) {
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

        system("cls");
    }
    
    system("cls");

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