#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOP     0
#define RIGHT   1
#define BOTTOM  2
#define LEFT    3

typedef int8_t SMALL;

/* Dimensions of the Maze */
SMALL nrow;
SMALL ncol;

/* Store the information of each cell */
typedef struct Cell{
    SMALL row;     
    SMALL col;  
    bool walls[4]; 
    bool visited;
}Cell;

/* Linked list of Cells */
typedef struct Node{
    Cell *cell;         // Pointer to cell
    struct Node *next;  // Pointer to the next node
}Node;

/* Adds an element at the top of the stack */
void push(Node **head, Cell *cell){
    Node *newHead = (Node*) malloc(sizeof(Node));
    newHead->cell = cell;
    newHead->next = *head;
    *head = newHead;
}

/* Removes element from the top of the stack and returns it value */
Cell* pop(Node **head){
    if(*head == NULL)
        return NULL;
    Node *p = *head;
    Cell *c = p->cell;
    *head = p->next; // The new top is the Node that follows
    free(p);         // Free the popped Node
    return c;        // Returns address of the popped cell
}

/* Check if the stack is empty */
bool isEmpty(Node **head){
    Node *curr = *head;
    while(curr != NULL){
        if (curr != NULL)
            return false;
        curr = curr->next;
    }
    return true;
}

/* Free the node from memory */
void freeList(Node **head){
    Node *p = *head;
    Node* tmp;
    while (p != NULL){
        tmp = p;
        p = p->next;
        free(tmp);
    }
}

/* Initializes each cell with default values */
void initGrid(Cell *grid){
    Cell *ptr = NULL;
    for(int i = 0; i < nrow; i++)
        for(int j = 0; j < ncol; j++){
            ptr = grid + i*ncol + j;
            /* The coordinates of each cell */
            ptr->row = i;
            ptr->col = j;
            /* All walls are closed */
            ptr->walls[0] = true;   
            ptr->walls[1] = true;
            ptr->walls[2] = true;
            ptr->walls[3] = true;
            /* Every cell is unvisited*/
            ptr->visited = false;
        }
}

/* Returns the nth element from the stack */
Cell* getIndex(Node **head, SMALL n){
    Node *p = *head;
    for (SMALL i = 0; i < n; i++)
        p = p->next;
    return p->cell;
}

/* Returns the top neighbor of the cell if available */
Cell* getTopNeighbor(Cell *cell){
    if (cell->row - 1 < 0)
        return NULL;
    else
        return cell - ncol;
}

/* Returns the right neighbor of the cell if available */
Cell* getRightNeighbor(Cell *cell){
    if (cell->col + 1 > ncol - 1)
        return NULL;
    else
        return cell + 1;
    
}

/* Returns the bottom neighbor of the cell if available */
Cell* getBottomNeighbor(Cell *cell){
    if (cell->row + 1 > nrow - 1)
        return NULL;
    else
        return cell + ncol;
}

/* Returns the left neighbor of the cell if available */
Cell* getLeftNeighbor(Cell *cell){
    if (cell->col - 1 < 0)
        return NULL;
    else
        return cell - 1;
    
}

/* Returns a random neighbor of the cell if available */
Cell* checkNeighbors(Cell *cell){
    /* Get the neighbors of the cell */
    Cell *topNeighbor    = getTopNeighbor(cell);
    Cell *rightNeighbor  = getRightNeighbor(cell);
    Cell *bottomNeighbor = getBottomNeighbor(cell);
    Cell *leftNeighbor   = getLeftNeighbor(cell);    

    SMALL n = 0;
    /* Stack that will contain the unvisited neighbors */
    Node *head = NULL;

    /* If the neighbor hasn't been visited, push it to the stack */
    if(topNeighbor != NULL && !topNeighbor->visited){
        push(&head, topNeighbor);
        n++;
    }
    if(rightNeighbor != NULL && !rightNeighbor->visited){
        push(&head, rightNeighbor);
        n++;
    }
    if(bottomNeighbor != NULL && !bottomNeighbor->visited){
        push(&head, bottomNeighbor);
        n++;
    }
    if(leftNeighbor != NULL && !leftNeighbor->visited){
        push(&head, leftNeighbor);
        n++;
    }

    /* If none of the neighbors are available, then return NULL*/
    if (n == 0)
        return NULL;

    /* Get a random neighbor from the stack */
    int r = rand() % n;
    Cell* neighbor = getIndex(&head, r);
    /* Free the stack from the heap */
    freeList(&head);

    return neighbor;
}

/* Remove the walls between two adjacent cells */
void removeWalls(Cell *curr, Cell *next){

    SMALL dr = curr->row - next->row; // Difference between the rows
    SMALL dc = curr->col - next->col; // Difference between the columns

    /* Remove top wall */
    if (dr == 1){
        curr->walls[TOP] = false;
        next->walls[BOTTOM] = false;
    }
    /* Remove right wall */
    else if (dc == -1){
        curr->walls[RIGHT] = false;
        next->walls[LEFT] = false;
    } 
    /* Remove bottom wall */
    else if (dr == -1){
        curr->walls[BOTTOM] = false;
        next->walls[TOP] = false;
    } 
    /* Remove left wall */
    else if (dc == 1){
        curr->walls[LEFT] = false;
        next->walls[RIGHT] = false;
    }
}

/* Display the maze on console */
void showMaze(Cell *curr){
    Cell *p = NULL;
    printf("\t");
    for(int j = 0; j < ncol; j++){
        p = curr + j;
        if(p->walls[TOP])
            printf(" _");
    }
    printf("\n");
    for(int i = 0; i < nrow; i++){
        printf("\t");
        for(int j = 0; j < ncol; j++){
            p = curr + i*ncol + j;
            if(p->walls[LEFT] && p->walls[BOTTOM])
                printf("|_");
            else if (p->walls[LEFT])
                printf("| ");
            else if (p->walls[BOTTOM])
                printf(" _");
            else
                printf("  ");
        }
        printf("|\n");
    }
}

/* Writes the maze on a file with the date and time when it was generated */
void printMaze(Cell *curr, FILE *file){

    if (file == NULL)
        return;

    fprintf(file, "\t%ix%i Maze\n\n", nrow, ncol);

    Cell *p = NULL;
    fprintf(file, "\t");
    for(int j = 0; j < ncol; j++){
        p = curr + j;
        if(p->walls[TOP])
            fprintf(file, " _");
    }
    fprintf(file, "\n");
    for(int i = 0; i < nrow; i++){
        fprintf(file, "\t");
        for(int j = 0; j < ncol; j++){
            p = curr + i*ncol + j;
            if(p->walls[LEFT] && p->walls[BOTTOM])
                fprintf(file, "|_");
            else if (p->walls[LEFT])
                fprintf(file, "| ");
            else if (p->walls[BOTTOM])
                fprintf(file, " _");
            else
                fprintf(file, "  ");
        }
        fprintf(file, "|\n");
    }
}

/* Accepts two parameters, the no. of rows and the no. of columns of the maze */
int main(int argc, char *argv[]){

    /* Incorrect number of parameters */
    if (argc != 3) {
        SMALL err = 1;
        printf("Usage: ./main nrow ncol\n");
        printf("%i\n", err);
        return err;
    }

    nrow = atoi(argv[1]);
    ncol = atoi(argv[2]);
    
    /* Number of rows and columns must be greater or equal to 1 */
    if (!(nrow >= 1 && ncol >= 1)){
        SMALL err = 2;
        printf("Usage: nrow > 0 and ncol > 0\n");
        printf("%i\n", err);
        return err;
    }
    
    /* Number of rows and columns must be less than 128 */
    if (!(nrow < 128 && ncol < 128)){
        SMALL err = 3;
        printf("Usage: nrow < 128 and ncol < 128\n");
        printf("%i\n", err);
        return err;
    }

    srand(time(0));

    /* Declare the grid */
    Cell grid[nrow][ncol];

    /* Pointer that will traverses the grid */
    Cell *curr = *grid;

    /* Pointer that stores the address of the neighbor */
    Cell *next = NULL;

    /* Initialize grid */
    initGrid(curr);
    curr->visited = true;

    /* Declare the stack that will be used for backtracking */
    Node *stack = NULL;

    /* Generating maze */
    while(true){
        /* Getting neighbor */
        next = checkNeighbors(curr);
        /* Traversing the grid */
        if (next != NULL){
            push(&stack, curr);
            removeWalls(curr, next);
            curr = next;
            curr->visited = true;
        } 
        /* Backtracking */
        else if (!isEmpty(&stack)) {
            Cell *temp = pop(&stack);
            while (!isEmpty(&stack) && checkNeighbors(temp) == NULL){
                temp = pop(&stack);
            }
            curr = temp;
        } else {
            break;
        }
    }

    /* show maze on console */
    printf("Succesfully generated a %ix%i maze\n", nrow, ncol);
    showMaze(curr);

    /* Prints the maze into a file */
    char filename[30];
    sprintf(filename, "Maze_%ix%i.txt", nrow, ncol);
    FILE *file = fopen(filename, "w+");
    printMaze(curr, file);
    fclose(file);

    return 0;
}