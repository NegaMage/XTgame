/*
To complete the project, we need a lot of data. We'll be shifting from making a
playable version to making a version that can run from RNG.

*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

// Predefined for ease of code
#define blank ' '
#define playerX 'x'
#define playerO 'o'
#define null '*'
#define ll long long
#define strategyX 5
#define strategyO 0

// Datastructures need to be global, no security concerns atm
char local[9][9];
char global[3][3];
int grid, slot;
int row, col;
// row and col are stand-ins for the row and col on 3*3 array.
int x, y;
// x and y will be the positions played on the 9*9 array
int recentMove;
char player;
char winner;
int input;
float p1time, p2time;
bool automated;
vector<int> nullGrids;
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
    if(!automated)
        clrscr();
    /*
    cout<<"GLOBAL GRID\n";
    printGlobal();
    cout<<"GAMEBOARD\n";
    printBoard();
    printf("=============================\n");
    */
}

void clearSlotsAndGrids(){
    // Resets board for a game.
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
    nullGrids.clear();
    grid=-1;
    slot=-1;
    winner = blank;
    player=blank;
    x=0; y=0; row=0; col=0;
}

bool checkFilledGrid(){
    // Returns true if the grid has been filled. It must then be set 
    // to null.
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(local[row*3+i][col*3+j]==blank){
                return(false);
            }
        }
    }
    return(true);
}

bool checkFilledGame(){
    // Returns true if the global game board has been filled. The game 
    // ends in a draw.
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(global[i][j]==blank){
                return(false);
            }
        }
    }
    return(true);
}

void checkWinSlotRecent(){
    // Needs to be called before setting grid for next player
    // we're talking about grid(row, col)
    if(local[row*3][col*3]==local[row*3+1][col*3+1] && local[row*3+1][col*3+1]==local[row*3+2][col*3+2] && local[row*3][col*3]!=blank){
        global[row][col]=local[row*3+1][col*3+1];
    }
    else if(local[row*3+0][col*3+2]==local[row*3+1][col*3+1] && local[row*3+1][col*3+1]==local[row*3+2][col*3+0] && local[row*3+1][col*3+1]!=blank){
        global[row][col]=local[row*3+1][col*3+1];
    }
    //rows
    else if(local[row*3][col*3]==local[row*3][col*3+1] && local[row*3][col*3+1]==local[row*3][col*3+2] && local[row*3][col*3]!=blank){
        global[row][col]=local[row*3][col*3];
    }
    else if(local[row*3+1][col*3]==local[row*3+1][col*3+1] && local[row*3+1][col*3+1]==local[row*3+1][col*3+2] && local[row*3+1][col*3+1]!=blank){
        global[row][col]=local[row*3+1][col*3];
    }
    else if(local[row*3+2][col*3]==local[row*3+2][col*3+1] && local[row*3+2][col*3+1]==local[row*3+2][col*3+2] && local[row*3+2][col*3]!=blank){
        global[row][col]=local[row*3+2][col*3];
    }

    //columns
    else if(local[row*3][col*3]==local[row*3+1][col*3] && local[row*3+1][col*3]==local[row*3+2][col*3] && local[row*3][col*3]!=blank){
        global[row][col]=local[row*3][col*3];
    }
    else if(local[row*3][col*3+1]==local[row*3+1][col*3+1] && local[row*3+1][col*3+1]==local[row*3+2][col*3+1] && local[row*3+1][col*3+1]!=blank){
        global[row][col]=local[row*3][col*3+1];
    }
    else if(local[row*3][col*3+2]==local[row*3+1][col*3+2] && local[row*3+1][col*3+2]==local[row*3+2][col*3+2] && local[row*3][col*3+2]!=blank){
        global[row][col]=local[row*3][col*3+2];
    }
    else if(checkFilledGrid()){
        global[row][col]=null;
        nullGrids.push_back(row*3+col);
    }
    else{
        global[row][col]=blank;
    }
}

char checkGlobalHelper(){
    // Helper function to check winner on Global grid.
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

char checkGlobal(){
    // Actual function to check winner on global grid. Returns winner if 
    // it exists, and blank if there's no winner.
    // If some grids are null, they can be used by both players. 

    if(checkFilledGame()){
        return(null);
    }

    int t1, t2;
    //Checking if current player can use null grids to win
    for(auto nullSlot: nullGrids){
        t1 = nullSlot/3;
        t2 = nullSlot%3;//could change to keypad format
        global[t1][t2]=player;
    }
    winner = checkGlobalHelper();

    //If previous check fails, checking if other player
    // can use null grids to win
    if(winner==blank){
        for(auto nullSlot: nullGrids){
            t1 = nullSlot/3;
            t2 = nullSlot%3;
            global[t1][t2]= (player==playerO)?playerX:playerO;
        }
        winner = checkGlobalHelper();
    }

    //Resetting null grids to previous state
    for(auto nullSlot: nullGrids){
        t1 = nullSlot/3;
        t2 = nullSlot%3;
        global[t1][t2]=null;
    }
    
    return(winner);
}

void numToRowCol(int num, int *row, int *col){
    //still calibrated to numpad
    //may change to keypad
    *row = 2-(num-1)/3;
    *col = (num+2)%3;
}

bool checkGrid(){
    // Check if the Grid we've selected is valid to play in.
    if(grid>=10 || grid<=0){
        return(true);
    }
    numToRowCol(grid, &row, &col);
    if(global[row][col]!=blank){
        //printf("GRID NOT BLANK\n");
        display();
        //exit(0);
        return(true);
    }
    return(false);
}

bool checkSlot(){
    // Check if the Slot we've selected is valid to play in.
    if(slot>=10 || slot<=0){
        return(true);
    }
    numToRowCol(slot, &x, &y);
    x+=row*3;
    y+=col*3;
    if(local[x][y]!=blank){
        return(true);
    }
    return(false);
}

void textRowCol(int row, int col){
    // Prints out the selected row and column so players find it easier to 
    // play.
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
    // Completes one move from the passed player in an interactive game.
    cout<<"You're playing as "<<player<<"\n";
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

    grid=slot;
    numToRowCol(grid, &row, &col);
    if(global[row][col]!=blank){
        grid=-1;
    }
    display();
    return(0);
}

void playAGame(){
    // Plays one interactive game.
    clearSlotsAndGrids();
    automated=false;
    int moveNo=0;

    while(winner==blank){
        //Part where input is randomly generated

        player = (moveNo%2==0) ? playerX : playerO;
        recentMove = oneMove(player);
        
        fprintf(record, "%d%c%d ", grid, player, slot);

        winner = checkGlobal();
        if(winner!=blank){
            fprintf(record, "W%c\n", winner);
            if(winner==null){
                cout<<"IT'S A DRAW!!\n";
                break;
            }
            cout<<winner<<" HAS WON!!\n";
            break;
        }
        moveNo++;
    }
}

bool oneMoveAutomated(int input, char player){
    // Plays one move in the automated game. 
    // Returns true when a move has been made succesfully. A move is 
    // classified as a defined slot in a playable grid.
    // Dual use (grid and slot selection)
    if(grid==-1){
        // The grid hasn't been selected yet. Mark this event in the 
        // log file.
        grid=input;
        //printf("grid not selected");
        return(false);
    }
    if(checkGrid()){
        // That grid has already been filled. Don't mark in logs.
        //printf("grid filled");
        grid = -1;
        return(false);
    }
    slot = input;
    if(checkSlot()){
        // That slot in the grid has already been taken.
        //printf("slot taken");
        return(false);
    }
    local[x][y]=player;
    checkWinSlotRecent();
    winner = checkGlobal();
    if(winner!=blank){
        printf("Game over! Player %c won!!\n\n", player);
        return(true);
    }
    fprintf(record, "%d%c%d ", grid, player, slot);
    grid=slot;
    numToRowCol(grid, &row, &col);
    if(global[row][col]!=blank){
        grid=-1;
    }
    display();
    //printf("returning true");
    return(true);
}
// corners>edges>center
int Move_Method_one(){
    int rando = rand()%84;
    if(rando >=0 && rando <=15 )
    {
        return 1;
    }
    else if (rando >= 16 && rando <= 31)
    {
        return 3;
    }
    else if (rando >= 32 && rando <= 47)
    {
        return 7;
    }
    else if (rando >= 48 && rando <= 63)
    {
        return 9;
    }
    else if (rando >= 64 && rando <= 67)
    {
        return 2;
    }
    else if (rando >= 68 && rando <= 71)
    {
        return 4;
    }
    else if (rando >= 72 && rando <= 75)
    {
        return 6;
    }
    else if (rando >= 76 && rando <= 79)
    {
        return 8;
    }
    else if (rando >= 80 && rando <= 83)
    {
        return 5;
    }
    return 1;
}
// corners>center>edges

int Move_Method_two(){
    int rando = rand()%84;
    if(rando >=0 && rando <=15 )
    {
        return 1;
    }
    else if (rando >= 16 && rando <= 31)
    {
        return 3;
    }
    else if (rando >= 32 && rando <= 47)
    {
        return 7;
    }
    else if (rando >=48 && rando <= 63)
    {
        return 9;
    }
    else if (rando >= 64 && rando <= 79)
    {
        return 5;
    }
    else if (rando == 80)
    {
        return 2;
    }
    else if (rando == 81)
    {
        return 4;
    }
    else if (rando == 82)
    {
        return 6;
    }
    else if (rando == 83)
    {
        return 8;
    }
   
    return 1;
}

// center>edges>corners

int Move_Method_three(){
    int rando = rand()%84;
    if(rando >=0 && rando <= 63 )
    {
        return 5;
    }
    else if (rando >= 64 && rando <= 67)
    {
        return 2 ;
    }
    else if (rando >= 68 && rando <=71)
    {
        return 4 ;
    }
    else if (rando >= 72 && rando <= 75 )
    {
        return 6;
    }
    else if (rando >= 76 && rando <= 79)
    {
        return 8;
    }
    else if (rando == 80)
    {
        return 1;
    }
    else if (rando == 81)
    {
        return 3;
    }
    else if (rando == 82)
    {
        return 7;
    }
    else if (rando == 83)
    {
        return 9;
    }
   
    return 1;
}
// center>corners>edges

int Move_Method_four(){
    int rando = rand()%84;
    if(rando >=0 && rando <= 63 )
    {
        return 5;
    }
    else if (rando >= 64 && rando <= 67)
    {
        return 1;
    }
    else if (rando >= 68 && rando <= 71)
    {
        return 3;
    }
    else if (rando >= 72 && rando <= 75)
    {
        return 7;
    }
    else if (rando >= 76 && rando <= 79)
    {
        return 9;
    }
    else if (rando == 80)
    {
        return 2;
    }
    else if (rando == 81)
    {
        return 4;
    }
    else if (rando == 82)
    {
        return 6;
    }
    else if (rando == 83)
    {
        return 8;
    }
    return 1;
}
// edges>center>corners

int Move_Method_five(){
    int rando = rand()%84;
    if(rando >=0 && rando <= 15 )
    {
        return 2;
    }
    else if (rando >= 16 && rando <= 31)
    {
        return 4 ;
    }
    else if (rando == 32 && rando <= 47)
    {
        return 6 ;
    }
    else if (rando == 48 && rando <= 63)
    {
        return 8;
    }
    else if (rando >= 64 && rando <= 79)
    {
        return 5;
    }
    else if (rando == 80)
    {
        return 1;
    }
    else if (rando == 81)
    {
        return 3;
    }
    else if (rando == 82)
    {
        return 7;
    }
    else if (rando == 83)
    {
        return 9;
    }
   
    return 1;
}
// edges>corners>center

int Move_Method_six(){
    int rando = rand()%84;
    if(rando >=0 && rando <= 15 )
    {
        return 2;
    }
    else if (rando >= 16 && rando <= 31)
    {
        return 4;
    }
    else if (rando >= 32 && rando <= 47)
    {
        return 6 ;
    }
    else if (rando >= 48 && rando <= 63)
    {
        return 8;
    }
    else if (rando >= 64 && rando <=67)
    {
        return 1;
    }
    else if (rando >= 68 && rando <= 71)
    {
        return 3;
    }
    else if (rando >= 72 && rando <= 75)
    {
        return 7;
    }
    else if (rando >= 76 && rando <= 79)
    {
        return 9;
    }
    else if (rando >= 80 && rando <= 83)
    {
        return 5;
    }
   
    return 1;
}

int Strategy_mapper(int player)
{
    int strategy;
    if(player == playerX)
        strategy = strategyX;
    else
        strategy = strategyO;
    switch (strategy)
    {
        case 0: return rand()%9 + 1;
                break;
        case 1: return Move_Method_one();
                break;
        case 3: return Move_Method_three();
                break;
        case 5: return Move_Method_five();
                break;
    }

}



void autoGame(){
    clearSlotsAndGrids();
    int moveNo=0;
    automated=true;

    while(winner==blank){
        if(moveNo>=90){
            display();
            cout<<"\n\nTOO MANY MOVES\n\n";
            fprintf(record, "ERR_TOO_MANY_MOVES\n");
            exit(0);
        }
        player = (moveNo%2==0) ? playerX : playerO;

        recentMove= Strategy_mapper(player);
        while(!oneMoveAutomated(recentMove, player)){           
            recentMove=Strategy_mapper(player);
            // cout<<moveNo<<":"<<recentMove<<"\n";
        }
        // cout<<moveNo<<":"<<recentMove<<"\n";
        if(grid != -1)
        {
            // fprintf(record, "%d%c%d ", grid, player, slot);
        }

        if(winner!=blank){
            fprintf(record, "W%c\n", winner);
            if(winner==null){
                cout<<"IT'S A DRAW!!=============================================\n--------------------";
            }else
                cout<<winner<<" HAS WON!!==============================================\n-------------------------------";
            display();
            return;
        }
        moveNo++;
    }
}



int main(int argc, char *argv[]){
    int iters = 1;
    cout<<"Number of games to record:\n>> ";
    cin>>iters;
    
    
    srand(time(0));
    record = fopen("rawData/file_5_0", "a");

    if(record==NULL){
        cout<<"File not found.\n";
        return(1);
    } 
    while(iters--){
        printf("Playing game %d\n", iters);
        autoGame();
    }
    fclose(record);
    return 0;
}