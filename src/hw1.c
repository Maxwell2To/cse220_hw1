#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hw1.h"

char board[MAX_ROWS][MAX_COLS] = {0};
/*
Hint: Consider adding a global variable to store a string large enough to store a board.
*/
int checkHorizontal(int cols, int rowInput, int colInput, char piece){
    int sum = 0;
    for (int i = 1; i < 4; i++) {
        if (colInput - i < 0)
            break;
        if (board[rowInput][colInput - i] != piece)
            break;
        else
            sum++;
    }

    for (int i = 1; i < 4; i++) {
        if (colInput + i > cols - 1)
            break;
        if (board[rowInput][colInput + i] != piece)
            break;
        else
            sum++;
    }
    return sum;
}

int checkVertical(int rows, int rowInput, int colInput, char piece){
    int sum = 0;
    for (int i = 1; i < 4; i++) {
        if (rowInput - i < 0)
            break;
        if (board[rowInput - i][colInput] != piece)
            break;
        else
            sum++;
    }

    for (int i = 1; i < 4; i++) {
        if (rowInput + i > rows - 1)
            break;
        if (board[rowInput + i][colInput] != piece)
            break;
        else
            sum++;
    }
    return sum;
}

int checkLeft2RightDiagonal(int rows, int cols, int rowInput, int colInput, char piece){
    int sum = 0;
    for (int i = 1; i < 4; i++) {
        if (rowInput - i < 0 || colInput - i < 0)
            break;
        if (board[rowInput - i][colInput - i] != piece)
            break;
        else
            sum++;
    }

    for (int i = 1; i < 4; i++) {
        if (rowInput + i > rows - 1 || colInput + i > cols - 1)
            break;
        if (board[rowInput + i][colInput + i] != piece)
            break;
        else
            sum++;
    }
    return sum;
}

int checkRight2LeftDiagonal(int rows, int cols, int rowInput, int colInput, char piece){
    int sum = 0;
    for (int i = 1; i < 4; i++) {
        if (rowInput - i < 0 || colInput + i > cols - 1)
            break;
        if (board[rowInput - i][colInput + i] != piece)
            break;
        else
            sum++;
    }

    for (int i = 1; i < 4; i++) {
        if (rowInput + i > rows - 1 || colInput - i < 0)
            break;
        if (board[rowInput + i][colInput - i] != piece)
            break;
        else
            sum++;
    }
    return sum;
}

int checker(int rows, int cols, int rowInput, int colInput, char piece){
    int has4inRow = 0;
    if (checkHorizontal(cols, rowInput, colInput, piece) >= 3 
    || checkVertical(rows, rowInput, colInput, piece) >= 3 
    || checkLeft2RightDiagonal(rows, cols, rowInput, colInput, piece) >= 3 
    || checkRight2LeftDiagonal(rows, cols, rowInput, colInput, piece) >= 3)
        has4inRow = 1;
    return has4inRow;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node { 
	int row;
	int col; 
	struct Node* next; 
}; 

void push(struct Node** head_ref, 
          int new_row, int new_col) 
{ 
	struct Node* new_node 
		= (struct Node*)malloc(sizeof(struct Node)); 
	new_node->row = new_row; 
	new_node->col = new_col; 
	new_node->next = (*head_ref); 
	(*head_ref) = new_node; 
} 

void deleteNode(struct Node** head_ref, int keyRow, int keyCol) 
{ 
	struct Node *temp = *head_ref, *prev; 

	if (temp != NULL && 
        temp->row == keyRow &&
        temp->col == keyCol) { 
		*head_ref = temp->next; 
		free(temp);
		return; 
	} 

	while (temp != NULL &&
           (temp->row != keyRow || temp->col != keyCol)) { 
		prev = temp; 
		temp = temp->next; 
	} 

	if (temp == NULL) 
		return; 

	prev->next = temp->next; 

	free(temp);
} 
//return 
int findCellNeededToForceAnXOrO(struct Node* node, int *outRow, int *outCol, int num_rows, int num_cols)
{ 
    (*outRow) = -1; // initialize to not found
    (*outCol) = -1;  

	while (node != NULL) { 
        int tempRow = node->row;
        int tempCol = node->col;
        int has4inRowx = checker(num_rows, num_cols, tempRow, tempCol, 'x');
        int has4inRowo = checker(num_rows, num_cols, tempRow, tempCol, 'o');
        // #### TODO:
        // modify this if condition to use your checker thing.
        // and see if node->row, node->col will result in 4inARow, if true, go in and update board with the opposite 'x' or 'o'
        // x or o in this cell
        if (has4inRowx == 1 && has4inRowo == 1)
            return -3;
                
        if (has4inRowx == 0 && has4inRowo == 1) {
            board[tempRow][tempCol] = 'x';
            *outRow = tempRow;
            *outCol = tempCol;
            return 1;
        }
                
        if (has4inRowx == 1 && has4inRowo == 0) {
            board[tempRow][tempCol] = 'o';
            *outRow = tempRow;
            *outCol = tempCol;
            return 1;
        }
            // #### TODO:
            // do the actual update
            // board[node->row][node->col] = 'x' or 'o' // that will NOT give 4InARow
        node = node->next;  
	}
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initialize_board(const char *initial_state, int num_rows, int num_cols) {
    int count = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            board[i][j] = initial_state[count++];     
        }
    }
}

int solve(const char *initial_state, int num_rows, int num_cols, int *num_x, int *num_o) {   
    initialize_board(initial_state, num_rows, num_cols);

    int has4inRow1 = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            char piece = board[i][j];
            if (piece != 'x' && piece != 'o' && piece != '-')
                return INITIAL_BOARD_INVALID_CHARACTERS;
            if (piece == 'x' || piece == 'o')
                has4inRow1 = checker(num_rows, num_cols, i, j, piece);
            if (has4inRow1 == 1)
                return INITIAL_BOARD_FOUR_IN_A_ROW;
        }
    }

    struct Node* head = NULL;
    int has4inRow2 = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            char piece = board[i][j];
            if (piece == '-') {
                has4inRow1 = checker(num_rows, num_cols, i, j, 'x');
                has4inRow2 = checker(num_rows, num_cols, i, j, 'o');
                
                if (has4inRow1 == 1 && has4inRow2 == 1)
                    return INITIAL_BOARD_NO_SOLUTION;
                
                if (has4inRow1 == 0 && has4inRow2 == 1) {
                    board[i][j] = 'x';
                    has4inRow2 = 0;
                }
                
                if (has4inRow1 == 1 && has4inRow2 == 0) {
                    board[i][j] = 'o';
                    has4inRow1 = 0;
                }

                if (has4inRow1 == 0 && has4inRow2 == 0)
                    push(&head, i, j);
            }
        }
    }
/////////////////////////////////////////////
    int outRow = -1; // initialize to -1 to indicate none was found.
    int outCol = -1;
    int didItChange = 1;
    while(didItChange == 1) {
        didItChange = findCellNeededToForceAnXOrO(head, &outRow, &outCol, num_rows, num_cols);
        if (didItChange == -3)
            return INITIAL_BOARD_NO_SOLUTION;
        else if (didItChange == 1) {
            deleteNode(&head, outRow, outCol);   /// remove from linked list
        }
    }

    int local_num_x = 0;
    int local_num_o = 0;
    int num_dash = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (board[i][j] == 'x')
                (local_num_x)++;
            else if (board[i][j] == 'o')
                (local_num_o)++;
            else if (board[i][j] == '-')
                num_dash++;
        }
    }

    (*num_x) = local_num_x;
    (*num_o) = local_num_o;

    if (num_dash > 0)
        return HEURISTICS_FAILED;

    return FOUND_SOLUTION;
}


char* generate_medium(const char *final_state, int num_rows, int num_cols) { 
    (void) final_state;
    (void) num_rows;
    (void) num_cols;
    return 0;
}


