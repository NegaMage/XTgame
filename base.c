#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define blank ' '
#define playerX 'x'
#define playerO 'o'
#define null '*'

//32 is whitespace
char local[9][9];
char global[3][3];
int curr;
int choice;
float p1time, p2time;

void init(){
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
    curr=-1;
    choice=-1;
}

void clrscr(){
    system("clear");
    return;
}

void readme(){
    printf("WIP\n");
}
void credits(){
    printf("WIP\n");
}

void startscreen(){
    printf("\033[1;31m");
    printf("_______________  ___________________________________   _____  ___________ ___________.____________   ________________  _________   ___________________  ___________._.\n");
    printf("\\_   _____/\\   \\/  /\\__    ___/\\______   \\_   _____/  /     \\ \\_   _____/ \\__    ___/|   \\_   ___ \\  \\__    ___/  _  \\ \\_   ___ \\  \\__    ___/\\_____  \\ \\_   _____/| |\n");
    printf(" |    __)_  \\     /   |    |    |       _/|    __)_  /  \\ /  \\ |    __)_    |    |   |   /    \\  \\/    |    | /  /_\\  \\/    \\  \\/    |    |    /   |   \\ |    __)_ | |\n");
    printf(" |        \\ /     \\   |    |    |    |   \\|        \\/    Y    \\|        \\   |    |   |   \\     \\____   |    |/    |    \\     \\____   |    |   /    |    \\|        \\ \\|\n");
    printf("/_______  //___/\\  \\  |____|    |____|_  /_______  /\\____|__  /_______  /   |____|   |___|\\______  /   |____|\\____|__  /\\______  /   |____|   \\_______  /_______  / __\n");
    printf("        \\/       \\_/                   \\/        \\/         \\/        \\/                         \\/                  \\/        \\/                     \\/        \\/  \\/\n");
    printf("\033[0m");
     printf("\033[1;32m");
    printf("+: Start\nr: readme\nc: credits\n");
    printf("\033[0m");
}

void printgrid(){
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


    if(global[0][0]==global[1][1] && global[1][1]==global[2][2] && global[1][1]!='*')
        return global[1][1];
    if(global[2][0]==global[1][1] && global[1][1]==global[0][2] && global[1][1]!='*')
        return global[1][1];
    
    if(global[0][0]==global[1][0] && global[1][0]==global[2][0] && global[1][0]!='*')
        return global[0][0];
    if(global[0][1]==global[1][1] && global[1][1]==global[2][1] && global[1][1]!='*')
        return global[1][1];
    if(global[0][2]==global[1][2] && global[1][2]==global[2][2] && global[1][2]!='*')
        return global[2][2];
    
    
    if(global[0][0]==global[0][1] && global[0][1]==global[0][2] && global[0][1]!='*')
        return global[0][0];
    if(global[1][0]==global[1][1] && global[1][1]==global[1][2] && global[1][1]!='*')
        return global[1][0];
    if(global[2][0]==global[2][1] && global[2][1]==global[2][2] && global[2][1]!='*')
        return global[2][0];
    
    return(32);
}

void printglobal(){
    for(int i=0;i<3;i++){
        printf(" %c | %c | %c\n", global[i][0], global[i][1], global[i][2]);
        if(i<2)
            printf("-----------\n");
    }
}

void numpad_to_row_col(int num, int *row, int *col){
    switch(num){
        case 1 : *row=2; *col=0; break;
        case 2 : *row=2; *col=1; break;
        case 3 : *row=2; *col=2; break;
        
        case 4 : *row=1; *col=0; break;
        case 5 : *row=1; *col=1; break;
        case 6 : *row=1; *col=2; break;

        case 7 : *row=0; *col=0; break;
        case 8 : *row=0; *col=1; break;
        case 9 : *row=0; *col=2; break;
        default: *row=0; *col=0; break;
    }
}

void row_col_in_text(int row, int col){
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

void editlocal(){
    int row, col;
    row=col=0;
    for(int k=1;k<10;k++){
        numpad_to_row_col(k, &row, &col);
        switch(global[row][col]){
            case playerX:
                    local[row*3+1][col*3]=blank;
                    local[row*3+2][col*3+1]=blank;
                    local[row*3+1][col*3+2]=blank;
                    local[row*3][col*3+1]=blank;

                    local[row*3][col*3]=playerX;
                    local[row*3+1][col*3+1]=playerX;
                    local[row*3+2][col*3+2]=playerX;
                    local[row*3+2][col*3]=playerX;
                    local[row*3][col*3+2]=playerX;
                    break;
            case playerO:
                    local[row*3+1][col*3+1]=blank;

                    local[row*3][col*3]=playerO;
                    local[row*3+1][col*3]=playerO;
                    local[row*3+2][col*3]=playerO;
                    local[row*3+2][col*3+1]=playerO;

                    local[row*3][col*3+1]=playerO;
                    local[row*3][col*3+2]=playerO;
                    local[row*3+1][col*3+2]=playerO;
                    local[row*3+2][col*3+2]=playerO;

                    local[row*3][col*3]=blank;
                    local[row*3+1][col*3+1]=blank;
                    local[row*3+2][col*3+2]=blank;
                    local[row*3+2][col*3]=blank;
                    local[row*3][col*3+2]=blank;

                    break;
            case null:
                    for(int i=0;i<3;i++){
                        for(int j=0;j<3;j++){
                            local[row*3+i][col*3+j]=null;
                        }
                    }
                    break;
            default:break;
        }
    }
}

void getnewcurr(){
    printf("Choose a grid to play in.\n");
    scanf(" %d", &curr);
    int i,j;
    numpad_to_row_col(curr, &i, &j);
    while(curr < 0 || curr > 9 || global[i][j] != blank){
        printf("Pick another grid\n");
        scanf(" %d", &curr);
        numpad_to_row_col(curr, &i, &j);
    }
}

int getslot(int row, int col){
    printf("Pick a slot in the ");
    row_col_in_text(row, col);
    printf("grid");
    scanf(" %d", &choice);
    if(choice == 113){//'q'==113
        printf("Exiting now");
        return 1;
    }
    int i, j;
    numpad_to_row_col(choice, &i, &j);
    while(local[row*3+i][col*3+j]!=blank){
        printf("That slot is taken, pick another.\n");
        scanf(" %d", &choice);
        numpad_to_row_col(choice, &i, &j);
    }
    return 0;
}

int move(char player){
    int row, col, i, j;
    row=col=0;
    printf("It's %c's move\n", player);
    //There are two cases, either curr is taken, or curr isn't.
    numpad_to_row_col(curr, &row, &col);
    if(global[row][col]==blank){
        //The curr value is not claimed yet.
        int quit = getslot(row, col);
        if(quit)
            return 1;
        numpad_to_row_col(choice, &i, &j);
        local[row*3+i][col*3+j]=player;
        curr=choice;
        checklocal();
        checkglobal(); 
        editlocal();       
    }else{
        //the curr value has been taken.
        //Let them choose curr,
        getnewcurr();
        int quit = getslot(row, col);
        if(quit)
            return 1;
        numpad_to_row_col(choice, &i, &j);
        local[row*3+i][col*3+j]=player;
        curr=choice;
        checklocal();
        checkglobal();
        editlocal(); 
    }
    return 0;
}

void twoplayer(){
    init();
    clrscr();
    printglobal();

    printf("Player X goes first.\n");
    char winner = blank;
    int turn=0;
    printf("Okay, enter the grid you want to start in: \n");
    getnewcurr();
    while(winner == blank){
        
        printgrid();
        if(turn%2){
            int quit = move(playerO);
            if(quit)
                return;
        }else{
            int quit = move(playerX);
            if(quit)
                return;
        }
        checklocal();
        winner = checkglobal();
        turn++;
        clrscr();
        printglobal();
        printf("GLOBAL GRID\n");
    }
    printgrid();
    printglobal();
    printf("Player %c won!\nExiting...", (char)winner);
}

int main(){
    init();
    // printglobal();
    // printgrid();
    twoplayer();
    

    return(0);
}