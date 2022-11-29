#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "utils.h"

#define TABLE_ROWS 25
#define TABLE_COLS 50

void mountTable(int** table);
void snakeController(int** table);

int main(void) {
    // int keyBind;
    // int* snakeYPosition, snakeXPosition;

    int** table = (int**) malloc(sizeof(int*) * 24);
    for (int row = 0; row < 25; row++) {
        table[row] = (int*) malloc(sizeof(int) * 49);
    }

    mountTable(table);
    printTable(table, 25, 50);

    // while (1) {
    //     if (kbhit()) {
    //         keyBind = getch();
    //     }
    // }

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