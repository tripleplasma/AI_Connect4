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
        nextAvailRow[i] = ROWS - 1;
    }
    printBoard();

    while(!done){
        printf("Select a column (1-7): ");
        int col = fgetc(stdin);
        while(col < 49 || col > 55){

            //To iterate through the entire line so we can get the next input
            int nextChar = fgetc(stdin);
            while(nextChar != 10){ //10 is '\n'
                nextChar = fgetc(stdin);
            }

            printf("Please select a column (1-7): ");
            col = fgetc(stdin);
        }
        col-=48; //turn the char number to numbers 1-7
        
        done = 1;
    }
    // How to clear screen
    // printf("\033[2J");
    // printf("\033[H");
    return 0;
}