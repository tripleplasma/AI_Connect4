#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* args[]){
    char twoPlayer = 0;
    for(int i = 1; i < argc; i++){
        printf("%s\n",args[i]);
        if(strcmp("-2",args[i]) == 0){
            printf("Players: %d\n", numPlayers);
        }
    }
    return 0;
}