#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Dimensions of the Maze
#define ROWS 10
#define COLS 10

typedef uint8_t SMALL;

typedef struct Cell{
    SMALL r;  // row
    SMALL c;  // col
    bool n; // north 
    bool s; // south 
    bool e; // east
    bool w; // west
}Cell;

int main(void){

    Cell grid[ROWS][COLS];
    Cell *ptr = *grid;

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            (ptr + i*COLS + j)->r = i;
            (ptr + i*COLS + j)->c = j;
            (ptr + i*COLS + j)->n = true;
            (ptr + i*COLS + j)->s = true;
            (ptr + i*COLS + j)->e = true;
            (ptr + i*COLS + j)->w = true;
            printf("(%i, %i) ", (ptr + i*COLS + j)->r, (ptr + i*COLS + j)->c);
        }
        printf("\n");
    }

    printf("Size of grid: %i bytes", sizeof(grid));

    return 0;
}