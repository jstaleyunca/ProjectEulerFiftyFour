/* 
 * File:   main.cpp
 * Author: John
 *
 * Created on February 25, 2015, 2:57 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "PokerHands.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string line;
    string playerOne;
    string playerTwo;
    ifstream file;
    file.open("singlehand.txt");
    if(!file.is_open()) {
        cout << "Unable to open file." << endl;
    }   
    PokerHands player1, player2;
    int player1Count = 0;
    while (getline(file, line)) {
        playerOne = line.substr(0,14);
        playerTwo = line.substr(15);
        player1 = new PokerHands(playerOne);
        player2 = new PokerHands(playerTwo);
        if (player1.handValue() > player2.handValue())
            player1Count++;
    }
    cout << "Player1 wins: " << player1Count << endl;
    //finish this
    file.close();
}

