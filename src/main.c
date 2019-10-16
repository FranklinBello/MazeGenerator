#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// Dimensions of the Maze
#define ROWS 10
#define COLS 10

#define TOP     0
#define RIGHT   1
#define BOTTOM  2
#define LEFT    3


typedef uint8_t SMALL;

// Cell structure to store the information of each cell
typedef struct Cell{
    SMALL row;      // row
    SMALL col;      // col
    bool walls[4];  // [0]top [1]right [2]bottom [3]left
    bool visited;
}Cell;

// Node structure for linked list
typedef struct Node
{
    Cell *cell;         // Pointer of cell
    struct Node *next;  // Pointer to the next node
}Node;

// Adds an element at the beginning of the list
void push(Node **head, Cell *cell){
    // Allocate the node that will go at the beginning
    Node *newHead = (Node*) malloc(sizeof(Node));
    newHead->cell = cell;
    newHead->next = *head;

    // Move the head to point to the new node
    *head = newHead;
}

void freeList(Node **head){
    Node *p = *head;
    Node* tmp;

    while (p != NULL)
    {
        tmp = p;
        p = p->next;
        free(tmp);
    }
}

Cell* getIndex(Node **head, SMALL index){
    
    Node *p = *head;
    
    for(SMALL i = 0; i < index; i++)
        p = p->next;

    return p->cell;
}

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
    // Bottom neighbor
    Cell *bottomNeighbor = getBottomNeighbor(cell);
    // Left neighbor
    Cell *leftNeighbor = getLeftNeighbor(cell);    

    Node *head = NULL;
    SMALL n = 0;

    if(topNeighbor != NULL && !topNeighbor->visited){
        // printf("Top: (%i, %i)\n", topNeighbor->row, topNeighbor->col);
        push(&head, topNeighbor);
        n++;
    }
    if(rightNeighbor != NULL && !rightNeighbor->visited){
        // printf("Right: (%i, %i)\n", rightNeighbor->row, rightNeighbor->col);
        push(&head, rightNeighbor);
        n++;
    }
    if(bottomNeighbor != NULL && !bottomNeighbor->visited){
        // printf("Bottom: (%i, %i)\n", bottomNeighbor->row, bottomNeighbor->col);
        push(&head, bottomNeighbor);
        n++;
    }
    if(leftNeighbor != NULL && !leftNeighbor->visited){
        // printf("Left: (%i, %i)\n", leftNeighbor->row, leftNeighbor->col);
        push(&head, leftNeighbor);
        n++;
    }

    if (n == 0)
        return NULL;

    int r = rand() % n;

    Cell* neighbor = getIndex(&head, r);

    freeList(&head);

    return neighbor;
}

void removeWalls(Cell *curr, Cell *next){

    SMALL y = curr->row - next->row;
    // [2, 0] [1, 0]    GO UP       curr = 2, next = 1 => curr - next = 1    
    // [1, 0] [2, 0]    GO DOWN     curr = 1, next = 2 => curr - next = -1   
    SMALL x = curr->col - next->col;
    // [0, 2] [0, 1]    GO LEFT     curr = 2, next = 1 => curr - next = 1    
    // [0, 1] [0, 2]    GO RIGHT    curr = 1, next = 2 => curr - next = -1   

    // Remove top wall
    if (y == 1){
        curr->walls[TOP] = false;
        next->walls[BOTTOM] = false;
    }
    // Remove right wall
    else if (x == -1){
        curr->walls[RIGHT] = false;
        next->walls[LEFT] = false;
    } 
    // Remove bottom wall
    else if (y == -1){
        curr->walls[BOTTOM] = false;
        next->walls[TOP] = false;
    } 
    // Remove left wall
    else if (x == 1){
        curr->walls[LEFT] = false;
        next->walls[RIGHT] = false;
    }
}

int main(void){

    srand(time(0));

    Cell grid[ROWS][COLS];

    // Pointer that traverses the grid
    Cell *curr = *grid;
    // Auxiliar pointer that stores the neighbor
    Cell *next = NULL;

    // Initialize grid
    initGrid(curr);

    // The maze starts generating at (0,0)
    curr->visited = true;
    printf("%i, %i\n", curr->row, curr->col);

    /* Step 1*/
    while(true){
        next = checkNeighbors(curr);
        if (next == NULL)
            break;
        removeWalls(curr, next);
        curr = next;
        curr->visited = true;
        printf("%i, %i\n", curr->row, curr->col);
    }

    return 0;
}