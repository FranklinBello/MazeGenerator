#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// Dimensions of the Maze
#define ROWS 10
#define COLS 10

typedef uint8_t SMALL;

typedef struct Cell{
    SMALL row;      // row
    SMALL col;      // col
    bool walls[4];  // [0]top [1]right [2]bottom [3]left
    bool visited;
}Cell;

void initGrid(Cell *grid){
    
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            Cell *ptr = grid + i*COLS + j;
            ptr->row = i;
            ptr->col = j;
            ptr->walls[0] = true;
            ptr->walls[1] = true;
            ptr->walls[2] = true;
            ptr->walls[3] = true;
            ptr->visited = false;
            printf("(%i, %i) ", ptr->row, ptr->col);
        }
        printf("\n");
    }
}

Cell* getTopNeighbor(Cell *cell){
    if(cell->row - 1 < 0){
        return NULL;
    } else {
        return cell - COLS;
    }
}

Cell* getRightNeighbor(Cell *cell){
    if(cell->col + 1 > COLS - 1){
        return NULL;
    } else {
        return cell + 1;
    }
}

Cell* getBottomNeighbor(Cell *cell){
    if(cell->row + 1 > ROWS - 1){
        return NULL;
    } else {
        return cell + COLS;
    }
}

Cell* getLeftNeighbor(Cell *cell){
    if(cell->col - 1 < 0){
        return NULL;
    } else {
        return cell - 1;
    }
}

Cell* checkNeighbors(Cell *cell){
    // Top neighbor
    Cell *topNeighbor = getTopNeighbor(cell);
    // Right neighbor
    Cell *rightNeighbor = getRightNeighbor(cell);
    // bottom neighbor
    Cell *bottomNeighbor = getBottomNeighbor(cell);
    // left neighbor
    Cell *leftNeighbor = getLeftNeighbor(cell);

    if(topNeighbor != NULL && !topNeighbor->visited){
        printf("Top: (%i, %i)\n", topNeighbor->row, topNeighbor->col);
    }
    if(rightNeighbor != NULL && !rightNeighbor->visited){
        printf("Right: (%i, %i)\n", rightNeighbor->row, rightNeighbor->col);
    }
    if(bottomNeighbor != NULL && !bottomNeighbor->visited){
        printf("Bottom: (%i, %i)\n", bottomNeighbor->row, bottomNeighbor->col);
    }
    if(leftNeighbor != NULL && !leftNeighbor->visited){
        printf("Left: (%i, %i)\n", leftNeighbor->row, leftNeighbor->col);
    }

    srand(0);

    return NULL;
}

int main(void){

    Cell grid[ROWS][COLS];

    // Set ups the pointer that will traverse the grid
    Cell *ptr = *grid;

    // Initialize grid
    initGrid(ptr);

    // The maze starts generating at (0,0)
    ptr->visited = true;

    ptr = checkNeighbors(ptr);

    return 0;
}