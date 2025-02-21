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
    printf("\033[2J\033[2J");
    printf("\033[H");
    printf("+-1---2---3---4---5---6---7-+\n");
    for(int i = 0; i < ROWS; i++){
        printf("|");
        for(int j = 0; j < COLS; j++){

            if(board[i][j] == p1){
                printf(" \033[31m%c\033[0m |",board[i][j]);
            }else if(board[i][j] == p2){
                printf(" \033[33m%c\033[0m |",board[i][j]);
            }else{
                printf("   |");
            }

            if(j == COLS - 1){
                printf("\n+---+---+---+---+---+---+---+\n");
            }
        }
    }
}

int getNextCol(const char* printPhrase){
    printf("%s",printPhrase);
    int col = fgetc(stdin);
    while(col < 49 || col > 55){

        //Clear the line, so next input is the new line and not the old one
        while(col != 10 && fgetc(stdin) != 10){}//10 is '\n'

        printf("%s",printPhrase);
        col = fgetc(stdin);
    }
    //Clear the line, so next input is the new line and not the old one
    while(fgetc(stdin) != 10){}//10 is '\n'
    return col-49; //turn the char number to indexes 0-6
}

int currentBoardState(char playerChar){

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            if(board[i][j] != playerChar) continue;

            int rightWin = 1;
            int bottomWin = 1;
            int lowerRightDiagWin = 1;
            int lowerLeftDiagWin = 1;
            for(int a = 1; a < 4; a++){
                if(j+a <= COLS-1){
                    if(board[i][j+a] == playerChar && ++rightWin == 4) {
                        // printf("RIGHT WIN\n");
                        return 1;
                    }
                }
                if(i+a <= ROWS-1){
                    if(board[i+a][j] == playerChar && ++bottomWin == 4){
                        // printf("BOTTOM WIN\n");
                        return 1;
                    }
                }
                if(j+a <= COLS-1 && i+a <= ROWS-1){
                    if(board[i+a][j+a] == playerChar && ++lowerRightDiagWin == 4){
                        // printf("RIGHT-DIAG WIN\n");
                        return 1;
                    }
                }
                if(j-a >= 0 && i+a <= ROWS-1){
                    if(board[i+a][j-a] == playerChar && ++lowerLeftDiagWin == 4){
                        // printf("LEFT-DIAG WIN\n");
                        return 1;
                    }
                }
            }
        }
    }

    //Check if all the columns are filled, means a draw
    int filledColumns = 0;
    for(int i = 0; i < COLS; i++){
        filledColumns += nextAvailRow[i] == -1 ? 1 : 0;
    }
    if(filledColumns == COLS){
        return 0; //Draw
    }

    return -1;
}

int getAIDecision(){
    int ai_col = rand() % 7;
    while(nextAvailRow[ai_col] == -1){
        ai_col = rand() % 7;
    }
    return ai_col;
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

    while(!done){
        char currentPlayer = p1Turn ? p1 : p2;
        char* printPhrase = p1Turn ? "Player 1, Select a column: " : "Player 2, Select a column: ";
        int col;

        if(!p1Turn && !twoPlayer){
            col = getAIDecision();
        }else{
            col = getNextCol(printPhrase);
            while(nextAvailRow[col] == -1){
                printf("That column is full!, pick a new column.\n");
                col = getNextCol(printPhrase);
            }
        }
        
        int row = nextAvailRow[col]--;
        board[row][col] = currentPlayer;
        printBoard();
        
        int currentState = currentBoardState(currentPlayer);
        if(currentState == 1){ //current Player Won
            printf("Player %c Wins!\n",currentPlayer);
            done = 1;
        }else if(currentState == 0){ //Draw
            done = 1;
            printf("The game ended in a draw.\n");
        }
        p1Turn = !p1Turn;
    }
    return 0;
}