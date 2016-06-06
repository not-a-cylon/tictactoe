//	The file contains functions that fill specified portions of the grid; a pointer to the array in question is passed as a parameter.
//	Primarily used for debugging.

#include <iostream>
#include "debug.h"

//  Fill the entire grid by filling up each of the three rows,
//  INPUT: character to fill the cells with, and size of grid;
void debugFillGrid(char* c, char content, int GRID_SIZE){
    for(int i = 0; i < GRID_SIZE; i++){
        debugFillRow(c+i*GRID_SIZE, content, GRID_SIZE);
    }
}

void debugFillRow(char* c, char content, int GRID_SIZE){
    debugFillSequence(c, content, 1, GRID_SIZE);
}

void debugFillColumn(char* c, char content, int GRID_SIZE){
    debugFillSequence(c, content, GRID_SIZE, GRID_SIZE);
}

//  A diagonal from top-left to bottom-right corner.
void debugFillDiag_1to9(char* c, char content, int GRID_SIZE){
    debugFillSequence(c, content, GRID_SIZE+1, GRID_SIZE);
}

//  A diagonal from top-right to bottom-left corner.
void debugFillDiag_3to7(char* c, char content, int GRID_SIZE){
    debugFillSequence(c, content, GRID_SIZE-1, GRID_SIZE);
}

//  All filler methods refer to this one; there are 4 different functions to allow for better readability.
//  INPUT: Starting pointer of array, character to fill cells with, and int to increment pointer by;
void debugFillSequence(char* c, char content, int mod, int GRID_SIZE){
    for(int i = 0; i < GRID_SIZE; i++){
        *c = content;
        c+=mod;
    }
}
