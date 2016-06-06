/*
 * main.h
 *
 *  Created on: Jun 3, 2016
 *      Author: Swayze
 */

#ifndef MAIN_H_
#define MAIN_H_

void printGrid(bool);
    void printRow(int, bool);
    void printRowCoords(int*);
    void printBlankLine();

    bool runLoop();
    bool playerTurn(int);
    bool askPlayAgain();

    bool winnerFound();
    bool getInputAndCheckWin(int);
    void requestInput(char);

    bool checkForSequence(char*, int);
    bool gridFull();
    bool isValidLocation(int);
    bool spaceIsAvailable(int);

    //  Debug methods for quick-and-dirty filling of the grid;
    void assignValue(int,char);

    char players[2];                    //  Array holding the players' characters; assigned in main()
    int playersScore[2];
    bool reverseOrder = false;
    std::string buffer;



#endif /* MAIN_H_ */
