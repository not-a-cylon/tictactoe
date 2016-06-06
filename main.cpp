#include <iostream>
#include "main.h"
#include "debug.h"

#define GRID_SIZE 3

char grid[GRID_SIZE][GRID_SIZE];    //  Playing grid;

int main(std::string args[]){

    bool keepPlaying = true;
    int round = 0;
    if(GRID_SIZE > 3){
        buffer = " ";
    }   else{
        buffer = "";
    }
    players[0] = 'X';
    players[1] = 'O';

    std::cout<<"Let\'s play Tic Tac Toe"<<std::endl;

    debugFillGrid(&grid[0][0],' ',GRID_SIZE);
    while(keepPlaying){
        round++;
        std::cout<<"XOXOXOXOXO ---- ROUND "<<round<<" ---- OXOXOXOXOX" <<std::endl;
        printBlankLine();
        std::cout<<"PLAYER 1: "<<playersScore[0]<<";               PLAYER 2: "<<playersScore[1]<<std::endl;
        debugFillGrid(&grid[0][0],' ',GRID_SIZE);
        keepPlaying = runLoop();
        reverseOrder = !reverseOrder;
    }
    return 0;
}

//  Main loop that runs throughout thee game; breaks when the game is finished through either a clear win or a full grid;
//      then asks the players if they want to do another round.
//  RETURNS true if yes.
bool runLoop(){
    bool gameFinished = false;
    while(!gameFinished){
    	gameFinished = playerTurn(reverseOrder);
        if(gameFinished){
            break;
        }
        gameFinished = playerTurn(!reverseOrder);
                if(gameFinished){
                    break;
                }
    }
    return askPlayAgain();
}

//  Runs one player turn; requests input and checks if the player won, both through getInputAndCheckWin;
//      returns true if the player won, or if the grid is full with no definite winner.
//  INPUT: index corresponding to the player in the players[] array; (1 or 2)
bool playerTurn(int p){
    if(getInputAndCheckWin(p)){
        playersScore[p]++;
        return true;
    }
    if(gridFull()){
        printBlankLine();
        std::cout<<"Grid is full with no winner..."<<std::endl;
        return true;
    }
    return false;
}

//  Gets input from the player as to where he wants to go, and checks if he won;
//      returns a bool accordingly.
//  INPUT: Player number and associated character;
bool getInputAndCheckWin(int p){
    bool endGame = false;
    char c = players[p];
    printBlankLine();
    printBlankLine();
    std::cout<<"--"<<c<<c<<" PLAYER "<<p+1<<" "<<c<<c<<"--"<<std::endl;
    requestInput(c);
    if(winnerFound()){
        endGame=true;
        printBlankLine();
        printBlankLine();
        std::cout<<c<<c<<c<<c<<c<<" PLAYER "<<p+1<<" WINS "<<c<<c<<c<<c<<c<<std::endl;
    }
    return endGame;
}

//  Asks the players if they want to play again, and screens input for 'y' or 'n';
//      returns a bool accordingly;
bool askPlayAgain(){
    char input;
    bool keepGoing=true;
    while(keepGoing){
        printBlankLine();
        printBlankLine();
        std::cout<<"Another round (y/n)? ";
        std::cin >> input;
        if(input == 'y'){
            printBlankLine();
            return true;
        }   else if(input == 'n'){
            printBlankLine();
            return false;
        }   else{
            printBlankLine();
            std::cout<<"I didn't catch that..."<<std::endl;
        }
    }
    return false;
}

//  Requests a numerical input from the player, corresponding to location on the grid;
//      BUG: stars looping if the input is longer than 1 character... even after cin.clear();
void requestInput(char m){
    int input;
    bool locationChosen=false;
    while(!locationChosen){
        printGrid(true);
        printBlankLine();
        printBlankLine();
        std::cout<<"Where do you want to move? Choose a number."<<std::endl;
        printBlankLine();
        std::cin>>input;
        if(!isValidLocation(input)){
            //std::cout<<std::endl<<"You chose "<<input<<std::endl;
            std::cout<<"-----------------------------------------"<<std::endl;
            std::cout<<std::endl<<"That\'s not a valid location... try again."<<std::endl;
        }   else    {
            locationChosen = true;
            assignValue(input-1,m);
            printGrid(false);
        }
        std::cin.clear();
    }
}

//  Prints out the 2D array grid that was passed to it;
//  INPUT:  c is a pointer to beginning of array;
//  INPUT:  if printCoords is true, he screen prints out indexes in place of blank cells, to help choose location;
//
//  IMPROVE: checks specifically for X and O characters; make more flexible?
void printGrid(bool printCoords){
    for(int i = 0; i < GRID_SIZE; i++){
        printRow(i*GRID_SIZE, printCoords);
    }
}

//  Prints out one row of cells from the grid;
//  INPUT: int mod is the modifier to add to the beginning grid pointer; marks beginning of the row;
//  INPUT: bool printCoords prints out an adjacent grid with coordinates of cells shown;
void printRow(int mod, bool printCoords){
    printBlankLine();
    char* ptr = &grid[0][0];
    int row[GRID_SIZE];
    ptr += mod;
    for(int i = 0; i<GRID_SIZE; i++){
        if(*ptr == 'X'||*ptr == 'O'){
            row[i]=0;
        }   else{
            row[i] = mod+i+1;
        }
        std::cout<<"["<<*ptr<<"]";
        ptr++;
    }
    if(printCoords){
        printRowCoords(&row[0]);
    }
}

//  Prints out the coordinates of the row on the same line;
//      INPUT: address to first cell of arrayholding the numbers to print;
void printRowCoords(int* a){
    std::cout<<"              ";
    for(int j = 0; j < GRID_SIZE; j++){
        std::cout<<"[";
        if(*(a+j)==0){
            std::cout<<" "<<buffer;
        }   else if(*(a+j) <= 9) {
            std::cout<<*(a+j)<<buffer;
        }   else {
            std::cout<<*(a+j);
        }
        std::cout<<"]";
    }
}

//  Checks if the selected number is within bounds (between 1 and size of grid, inclusive)
//      and passes it to spaceIsAvailable to make sure the space is blank.
//  INPUT: val is the modifier(+1) to add to the starting array pointer.
bool isValidLocation(int val){
    if(val<=0 || val > GRID_SIZE*GRID_SIZE){
        return false;
    }   else if(!spaceIsAvailable(val-1)) {
        return false;
    }
    return true;
}


//  Checks if the chosen space is up for grabs; returns true or false, accordingly.
//  INPUT: modifier to add to pointer of the first cell of array;
bool spaceIsAvailable(int mod){
    char* ptr = &grid[0][0];
    return(*(ptr+mod)!='X'&&*(ptr+mod)!='O');
}

//  Assigns a value to the given cell;
//  INPUTS: modifier to offset the origin pointer, and character to insert there.
void assignValue(int mod, char val){
    char* ptr = &grid[0][0];
    ptr+=mod;
    *ptr = val;
}

//  Checks if the grid is full, and returns a bool accordingly; basically if any cell has ' ' in it, returns false;
//  INPUT: pointer to the first char in the array as a parameter.
bool gridFull(){
    char* ptr = &grid[0][0];
    for(int i = 0; i < GRID_SIZE*GRID_SIZE; i++){
        if(*(ptr+i)==' '){
            return false;
        }
    }
    return true;
}

//  Literally prints a blank line; does not save space, but exists to make code more readable;
void printBlankLine(){
    std::cout<<std::endl;
}

//  Checks if there's a definite winner by looking for all possible horizontal, vertical, and diagonal completions.
//  INPUT: pointer to the starting cell of array.
bool winnerFound(){
    bool winnerFound = false;
    char* ptr = &grid[0][0];
    //  FOR loop checks for row and column completions;
    for(int col = 0; col < GRID_SIZE; col++){
        //  First check is for the column, sequence modifier is GRID_SIZE,
        //  Second check is for the row, sequence modifier is 1,
        if(checkForSequence(ptr+col,GRID_SIZE)||checkForSequence(ptr+col*GRID_SIZE,1)){
            return true;
        }
    }
    //  Check for diagonal completions; first a 1to9, then a 3to7;
    if(checkForSequence(ptr,GRID_SIZE+1)||checkForSequence(ptr+GRID_SIZE-1,GRID_SIZE-1)){
        return true;
    }
    return false;
}

//  Checks if there's a complete line formed;
//  INPUT: pointer to the starting cell of array, and
//  INPUT: int modifier to increment the pointer by;
//        for columns, mod = GRID_SIZE; rows -> 1;
//        top-left to bottom-right diag -> GRID_SIZE + 1:
//        top-right to bottom-left diag -> GRID_SIZE - 1:
bool checkForSequence(char* ptr, int mod){
    char c;
    for(int i = 0; i < GRID_SIZE; i++){
        c = *(ptr+mod*i);
        if(c!=*ptr||(c!='X'&&c!='O')){
            return false;
        }
    }
    return true;
}
