#include <stdio.h>
#include "./utils.h"

void printTable(int** table, int rowSize, int colSize) {
    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {
            printf("%c", table[row][col]);
        }

        printf("\n");
    }
}