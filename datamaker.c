/*
To complete the project, we need a lot of data. We'll be shifting from making a
playable version to making a version that can run from RNG.

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Predefined for ease of code
#define blank ' '
#define playerX 'x'
#define playerO 'o'
#define null '*'
#define ll long long

//Datastructures need to be global, no security concerns atm
char local[9][9];
char global[3][3];
int grid, slot;
int row, col;
int x, y;
int move;
char player;
char winner;
int input;
float p1time, p2time;
FILE *record;

//Functions
void clrscr(){
    system("clear");
    return;
}

void printGrid(){
    clrscr();
    for(int i=0;i<9;i++){
        if(i==3 || i==6){
            printf("-----------------------------\n");
        }
        for(int j=0;j<9;j++){
            if(j==3 || j==6){
                printf("|");
            }
            printf(" %c ", local[i][j]);
        }
        printf("\n");
    }
}

void clearSlotsAndGrids(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            local[i][j]=blank;
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            global[i][j]=blank;
        }
    }
    grid=-1;
    slot=-1;
}
void checklocal(){
    int row, col;
    char localwin;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            //this block checks the <i,j>th grid of the major grid.
            //diagonals
            if(local[i*3][j*3]==local[i*3+1][j*3+1] && local[i*3+1][j*3+1]==local[i*3+2][j*3+2] && local[i*3][j*3]!=blank){
                global[i][j]=local[i*3+1][j*3+1];
                continue;
            }
            else if(local[i*3+0][j*3+2]==local[i*3+1][j*3+1] && local[i*3+1][j*3+1]==local[i*3+2][j*3+0] && local[i*3+1][j*3+1]!=blank){
                global[i][j]=local[i*3+1][j*3+1];
                continue;
            }
            //rows
            else if(local[i*3][j*3]==local[i*3][j*3+1] && local[i*3][j*3+1]==local[i*3][j*3+2] && local[i*3][j*3]!=blank){
                global[i][j]=local[i*3][j*3];
                continue;
            }
            else if(local[i*3+1][j*3]==local[i*3+1][j*3+1] && local[i*3+1][j*3+1]==local[i*3+1][j*3+2] && local[i*3+1][j*3+1]!=blank){
                global[i][j]=local[i*3+1][j*3];
                continue;
            }
            else if(local[i*3+2][j*3]==local[i*3+2][j*3+1] && local[i*3+2][j*3+1]==local[i*3+2][j*3+2] && local[i*3+2][j*3]!=blank){
                global[i][j]=local[i*3+2][j*3];
                continue;
            }

            //columns
            else if(local[i*3][j*3]==local[i*3+1][j*3] && local[i*3+1][j*3]==local[i*3+2][j*3] && local[i*3][j*3]!=blank){
                global[i][j]=local[i*3][j*3];
                continue;
            }
            else if(local[i*3][j*3+1]==local[i*3+1][j*3+1] && local[i*3+1][j*3+1]==local[i*3+2][j*3+1] && local[i*3+1][j*3+1]!=blank){
                global[i][j]=local[i*3][j*3+1];
                continue;
            }
            else if(local[i*3][j*3+2]==local[i*3+1][j*3+2] && local[i*3+1][j*3+2]==local[i*3+2][j*3+2] && local[i*3][j*3+2]!=blank){
                global[i][j]=local[i*3][j*3+2];
                continue;
            }
            else{
                global[i][j]=blank;
            }
        }
    }
}

int checkglobal(){


    if(global[0][0]==global[1][1] && global[1][1]==global[2][2] && global[1][1]!=blank)
        return global[1][1];
    if(global[2][0]==global[1][1] && global[1][1]==global[0][2] && global[1][1]!=blank)
        return global[1][1];
    
    if(global[0][0]==global[1][0] && global[1][0]==global[2][0] && global[1][0]!=blank)
        return global[0][0];
    if(global[0][1]==global[1][1] && global[1][1]==global[2][1] && global[1][1]!=blank)
        return global[1][1];
    if(global[0][2]==global[1][2] && global[1][2]==global[2][2] && global[1][2]!=blank)
        return global[2][2];
    
    
    if(global[0][0]==global[0][1] && global[0][1]==global[0][2] && global[0][1]!=blank)
        return global[0][0];
    if(global[1][0]==global[1][1] && global[1][1]==global[1][2] && global[1][1]!=blank)
        return global[1][0];
    if(global[2][0]==global[2][1] && global[2][1]==global[2][2] && global[2][1]!=blank)
        return global[2][0];
    
    return(blank);
}
int checkWinner(){
    checklocal();
    return(checkglobal());
}

void numToRowCol(int num, int *row, int *col){
    *row = 2-num/3;
    *col = num%3;
}

int checkGrid(){
    numToRowCol(grid, &row, &col);
    if(global[row][col]!=blank){
        return(1);
    }
    return(0);
}

int checkSlot(){
    numToRowCol(slot, &x, &y);
    x+=row*3;
    y+=row*3;
    if(local[x][y]!=blank){
        return(1);
    }
    return(0);
}

int oneMove(int input, char player){
    if(grid==-1){
        grid=input;
        return(0);
    }
    if(checkGrid()){
        return(0);
    }
    slot = input;
    if(checkSlot()){
        return(0);
    }
    local[x][y]=player;
    x%=3;y%=3;
    if(global[x][y]!=blank){
        grid=-1;
    }
    printGrid();
    return(1);
}

void playAGame(){
    clearSlotsAndGrids();

    for(int i=0;i>0;i++){
        //Part where input is randomly generated
        scanf("%d", &input);

        player = (i%2==0) ? playerX : playerO;
        move = oneMove(input, player);
        while(move==0){
            //generate random number input and try again
            scanf("%d", &input);
            move = oneMove(input, player);
        }
        fprintf(record, "%d ", input);

        winner = checkWinner();
        if(winner!=blank){
            fprintf(record, "W%c\n", winner);
            break;
        }
    }
}



int main(int argc, char *argv[]){
    int iters = 1000;
    
    record = fopen("file", "a");

    if(record==NULL){
        printf("File not found.\n");
        return(1);
    } 
    while(iters--){
        printf("Playing game %d\n", iters);
        playAGame();
    }

    fclose(record);
    return 0;
}