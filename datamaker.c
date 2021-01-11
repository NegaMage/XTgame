/*
To complete the project, we need a lot of data. We'll be shifting from making a
playable version to making a version that can run from RNG.

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Predefined for ease of code
#define blank ' '
#define playerX 'x'
#define playerO 'o'
#define null '*'
#define ll long long

// Datastructures need to be global, no security concerns atm
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

void printGlobal(){
    for(int i=0;i<3;i++){
        printf(" %c | %c | %c\n", global[i][0], global[i][1], global[i][2]);
        if(i<2)
            printf("-----------\n");
    }
}

void printBoard(){
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

void display(){
    clrscr();
    printf("GLOBAL GRID\n");
    printGlobal();
    printf("GAMEBOARD\n");
    printBoard();
    printf("=============================\n");
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
void checkWinSlotAll(){
    // checks all grids for a win. 
    
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

void checkWinSlotRecent(){
    // Needs to be called before setting grid for next player
    // we're talking about grid(row, col)
    int i=row;
    int j=col;
    if(local[i*3][j*3]==local[i*3+1][j*3+1] && local[i*3+1][j*3+1]==local[i*3+2][j*3+2] && local[i*3][j*3]!=blank){
        global[i][j]=local[i*3+1][j*3+1];
    }
    else if(local[i*3+0][j*3+2]==local[i*3+1][j*3+1] && local[i*3+1][j*3+1]==local[i*3+2][j*3+0] && local[i*3+1][j*3+1]!=blank){
        global[i][j]=local[i*3+1][j*3+1];
    }
    //rows
    else if(local[i*3][j*3]==local[i*3][j*3+1] && local[i*3][j*3+1]==local[i*3][j*3+2] && local[i*3][j*3]!=blank){
        global[i][j]=local[i*3][j*3];
    }
    else if(local[i*3+1][j*3]==local[i*3+1][j*3+1] && local[i*3+1][j*3+1]==local[i*3+1][j*3+2] && local[i*3+1][j*3+1]!=blank){
        global[i][j]=local[i*3+1][j*3];
    }
    else if(local[i*3+2][j*3]==local[i*3+2][j*3+1] && local[i*3+2][j*3+1]==local[i*3+2][j*3+2] && local[i*3+2][j*3]!=blank){
        global[i][j]=local[i*3+2][j*3];
    }

    //columns
    else if(local[i*3][j*3]==local[i*3+1][j*3] && local[i*3+1][j*3]==local[i*3+2][j*3] && local[i*3][j*3]!=blank){
        global[i][j]=local[i*3][j*3];
    }
    else if(local[i*3][j*3+1]==local[i*3+1][j*3+1] && local[i*3+1][j*3+1]==local[i*3+2][j*3+1] && local[i*3+1][j*3+1]!=blank){
        global[i][j]=local[i*3][j*3+1];
    }
    else if(local[i*3][j*3+2]==local[i*3+1][j*3+2] && local[i*3+1][j*3+2]==local[i*3+2][j*3+2] && local[i*3][j*3+2]!=blank){
        global[i][j]=local[i*3][j*3+2];
    }
    else{
        global[i][j]=blank;
    }
}

char checkGlobal(){
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

void numToRowCol(int num, int *row, int *col){
    //still calibrated to numpad
    *row = 2-(num-1)/3;
    *col = (num+2)%3;
}

int checkGrid(){
    if(grid>=10 || grid<=0){
        return(1);
    }
    numToRowCol(grid, &row, &col);
    if(global[row][col]!=blank){
        return(1);
    }
    return(0);
}

int checkSlot(){
    if(slot>=10 || slot<=0){
        return(1);
    }
    numToRowCol(slot, &x, &y);
    x+=row*3;
    y+=col*3;
    if(local[x][y]!=blank){
        return(1);
    }
    return(0);
}

void textRowCol(int row, int col){
    switch(row){
        case 0 : printf("Top "); break;
        case 1 : printf("Middle "); break;
        case 2 : printf("Bottom "); break;
    }
    switch(col){
        case 0 : printf("Left "); break;
        case 1 : printf("Middle "); break;
        case 2 : printf("Right "); break;
    }
}

int oneMove(char player){
    if(grid==-1){
        printf("You're not currently in a grid\nPlease select a grid\n>>");
        scanf(" %d", &grid);
    }
    while(checkGrid()){
        printf("That grid is filled, please pick another\n>>");
        scanf(" %d", &grid);
    }
    
    printf("You're playing in the ");
    textRowCol(row, col);
    printf("grid.\n");

    printf("Pick a slot to play as %c:\n>>", player);
    scanf(" %d", &slot);
    while(checkSlot()){
        printf("That slot has already been filled\nPlease pick another\n>>");
        scanf(" %d", &slot);
    }
    
    local[x][y]=player;
    checkWinSlotRecent();
    winner = checkGlobal();
    if(winner!=blank){
        printf("Game over! Player %c won!!\n\n", player);
        return(0);
    }
    
    x%=3;y%=3;
    
    grid=slot;
    if(global[x][y]!=blank){
        grid=-1;
    }
    display();
    return(0);
}

int oneMoveAutomated(int input, char player){
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
    display();
    return(1);
}

void playAGame(){
    clearSlotsAndGrids();

    for(int i=0;i>=0;i++){
        //Part where input is randomly generated

        player = (i%2==0) ? playerX : playerO;
        move = oneMove(player);
        
        fprintf(record, "%d%c%d ", grid, player, slot);

        winner = checkGlobal();
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
    // while(iters--){
    //     printf("Playing game %d\n", iters);
    //     playAGame();
    // }
    playAGame();
    fclose(record);
    return 0;
}