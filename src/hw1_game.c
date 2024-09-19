#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hw1.h"


void showBoard(int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
/*
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
*/
int main(int argc, char **argv) {
    assert(argc == 4);
    initialize_board(argv[3], (int)strtoul(argv[1], NULL, 10), (int)strtoul(argv[2], NULL, 10));
	//Write your code here
    int num_rows = (int)strtoul(argv[1], NULL, 10);
    int num_cols = (int)strtoul(argv[2], NULL, 10);

        char piece = '-';

    while(piece != 'q') {    
        piece = '-';
        showBoard(num_rows, num_cols);
        while((piece != 'x') && (piece != 'o') && (piece != 'q')) {
            printf("Choose a piece (x or o) or q to quit: ");
            scanf(" %c", &piece);
            if (piece == 'q')
                break;
            if ((piece != 'x') && (piece != 'o')) 
                printf("Invalid choice. ");
        } 
    
        if (piece == 'q')
                break;

        int row = -1;
        while((row < 0) || (row >= num_rows)) {
            printf("Choose a row (0-%i): ", num_rows-1);
            scanf(" %i", &row);                     //there is a bug if you type a letter. will keep spamming with no end
            if ((row < 0) || (row >= num_rows)) 
                printf("Invalid choice. ");
        } 

        int col = -1;
        while((col < 0) || (col >= num_cols)) {
            printf("Choose a column (0-%i): ", num_cols-1);
            scanf(" %i", &col);                     //there is a bug if you type a letter. will keep spamming with no end
            if ((col < 0) || (col >= num_cols)) 
                printf("Invalid choice. ");
        } 


        if ((board[row][col] == 'x') || (board[row][col] == 'o')) {
            printf("Invalid choice. That space is already occupied.\n");
            continue;
        }

        int is4inRow = checker(num_rows, num_cols, row, col, piece);
        if (is4inRow == 1) {
            printf("Invalid choice. You have created 4-in-a-row.\n");
            continue;
        }
        else
            board[row][col] = piece;

        int filled = 0;
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                if (board[i][j] == 'x' || board[i][j] == 'o')
                    filled++;
            }
        }

        if (filled == (num_rows * num_cols)) {
            printf("Congratulations, you have filled the board with no 4-in-a-rows!\n");
            showBoard(num_rows, num_cols);
            break;
        }
    }

    return 0;
}



