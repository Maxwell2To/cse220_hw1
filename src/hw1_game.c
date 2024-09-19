#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hw1.h"

////////////////move showboard function into here

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


        if (checkFree(row, col) == 0) {
            printf("Invalid choice. That space is already occupied.\n");
            continue;
        }

        int is4inRow = checker(num_rows, num_cols, row, col, piece);
        if (is4inRow == 1) {
            printf("Invalid choice. You have created 4-in-a-row.\n");
            continue;
        }
        else
            putPiece(piece, row, col);

        int filled = 0;
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                if (checkFree(i, j) == 0)
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



