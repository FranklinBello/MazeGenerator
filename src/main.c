#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// Dimensions of the Maze
#define ROWS 10
#define COLS 10

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

Cell* getIndex(Node **head, SMALL index){
    
    Node *p = *head;
    
    for(SMALL i = 0; i < index; i++)
        p = p->next;

    return p->cell;
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
        printf("Top: (%i, %i)\n", topNeighbor->row, topNeighbor->col);
        push(&head, topNeighbor);
        n++;
    }
    if(rightNeighbor != NULL && !rightNeighbor->visited){
        printf("Right: (%i, %i)\n", rightNeighbor->row, rightNeighbor->col);
        push(&head, rightNeighbor);
        n++;
    }
    if(bottomNeighbor != NULL && !bottomNeighbor->visited){
        printf("Bottom: (%i, %i)\n", bottomNeighbor->row, bottomNeighbor->col);
        push(&head, bottomNeighbor);
        n++;
    }
    if(leftNeighbor != NULL && !leftNeighbor->visited){
        printf("Left: (%i, %i)\n", leftNeighbor->row, leftNeighbor->col);
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

int main(void){

    srand(time(NULL));

    Cell grid[ROWS][COLS];

    // Set ups the pointer that will traverse the grid
    Cell *ptr = *grid;

    // Initialize grid
    initGrid(ptr);

    // The maze starts generating at (0,0)
    ptr->visited = true;

    printf("First\n");
    ptr = checkNeighbors(ptr);
    ptr->visited = true;
    printf("Second\n");
    ptr = checkNeighbors(ptr);
    ptr->visited = true;
    printf("Third\n");
    ptr = checkNeighbors(ptr);
    ptr->visited = true;

    return 0;
}