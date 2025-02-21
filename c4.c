#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 7

const char p1 = 'X';
const char p2 = 'O';
static char board[ROWS][COLS];
static int nextAvailRow[COLS];
char done = 0;
char p1Turn = 1;

void printBoard(){
    printf("\033[2J");
    printf("\033[H");
    printf("+-1---2---3---4---5---6---7-+\n");
    for(int i = 0; i < ROWS; i++){
        printf("|");
        for(int j = 0; j < COLS; j++){
            printf(" %c |",board[i][j]);
            if(j == COLS - 1){
                printf("\n+---+---+---+---+---+---+---+\n");
            }
        }
    }
}

int getNextCol(const char* printPhrase){
    printf(printPhrase);
    int col = fgetc(stdin);
    while(col < 49 || col > 55){

        //Clear the line, so next input is the new line and not the old one
        while(fgetc(stdin) != 10){}//10 is '\n'

        printf(printPhrase);
        col = fgetc(stdin);
    }
    //Clear the line, so next input is the new line and not the old one
    while(fgetc(stdin) != 10){}//10 is '\n'

    return col-49; //turn the char number to indexes 0-6
}

int main(int argc, char* args[]){
    char twoPlayer = 0;
    for(int i = 1; i < argc; i++){
        printf("%s\n",args[i]);
        if(strcmp("-2",args[i]) == 0){
            twoPlayer = 1;
        }
    }
    
    // INIT Board and Next Available Rows
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            board[i][j] = ' ';
        }
    }
    for(int i = 0; i < COLS; i++){
        nextAvailRow[i] = ROWS-1;
    }
    printBoard();
    int count = 0; //NOTE: This is just for testing
    while(count < 7){
        char* printPhrase = p1Turn ? "Player 1, Select a column: " : "Player 2, Select a column: ";
        int col = getNextCol(printPhrase);
        while(nextAvailRow[col] == -1){
            printf("That column is full!, pick a new column.\n");
            col = getNextCol(printPhrase);
        }
        int row = nextAvailRow[col]--;
        board[row][col] = p1Turn ? p1 : p2;
        
        printBoard();

        //TODO: Do a win condition check on current player, if win, exit while loop
        p1Turn = twoPlayer ? !p1Turn : p1Turn;

        //TODO: If not 2 player game, this will be AI turn, otherwise have other player pick
        // done = 1;
        count++;
    }
    return 0;
}