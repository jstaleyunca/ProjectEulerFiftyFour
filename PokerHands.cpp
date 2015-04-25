/* 
 * File:   PokerHands.cpp
 * Author: John
 * 
 * Created on February 25, 2015, 3:24 PM
 */

#include "PokerHands.h"
#include <cstdlib>
#include <string>

using namespace std;

PokerHands::PokerHands() {
    hand = "";
    value = 0;
    for(int o = 0; o < sizeof(rank); o++) {
        rank[o] = 0;
    }
    for(int p = 0; p < sizeof(suit); p++) {
        suit[p] = 0;
    }
}

PokerHands::PokerHands(std::string s) {
    //initialize rank and suit arrays
    //fill in rank and suit arrays
    hand = s;
    value = 0;
    for(int o = 0; o < sizeof(rank); o++) {
        rank[o] = 0;
    }
    for(int p = 0; p < sizeof(suit); p++) {
        suit[p] = 0;
    }
    for (int i = 0; i < hand.length(); i++) { //while more cards in 's'  
        int pos = 0;
        int pos2 = 0;
        switch (hand[i]) {
            case 'T': pos = 10; rank[pos]++; break;
            case 'J': pos = 11; rank[pos]++; break;
            case 'Q': pos = 12; rank[pos]++; break;
            case 'K': pos = 13; rank[pos]++; break;
            case 'A': pos = 14; rank[pos]++; rank[1]++; break;//also add to one for aces
            case 'C': pos2 = 0; suit[pos2]++; break;               
            case 'D': pos2 = 1; suit[pos2]++; break;
            case 'H': pos2 = 2; suit[pos2]++; break;
            case 'S': pos2 = 3; suit[pos2]++; break;
            case ' ': break; //is this necessary?
            default: pos = (int)hand[i] - (int)'0'; rank[pos]++; //only works for 2 through 9
        }
        //rank[pos]++ (not necessary if above works)
    }
    
    setValue();
}

PokerHands::PokerHands(const PokerHands& orig) {
    hand = orig.hand;
}

PokerHands::~PokerHands() {
    
}

int PokerHands::handValue() {
    return value;
}

void PokerHands::setValue() {
    int handRank;
    int rankValue;
    int totalCardValue = 0;
    //array to store rankValues in spots that determine handRank
    int cardCombinations[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    bool pair; //shows if a pair is already present to check for two pairs
    for (int x = 1; x < sizeof (rank); x++) {
        if (rank[x] != 0) {
            if (rank[x] == 1) { //high card
                cardCombinations[0] = rank[x];
            } else if (rank[x] == 2 && pair == true) { //two pair
                cardCombinations[2] = x;
            } else if (rank[x] == 2) { //one pair
                cardCombinations[1] = x;
                pair = true; //marks pair as present for possible two pair
            } else if (rank[x] == 3) { //three of a kind
                cardCombinations[3] = x;
            } else if (rank[x] == 4) { //four of a kind present
                cardCombinations[7] = x;
            }
        }
    }
    if (straightPos() != 0) { //for straight based card combos 
        if (straightPos() == 10 && isFlush() == true) {
            cardCombinations[9] = 1; //there is a royal flush
        } else if (straightPos() != 10 && isFlush() == true) {
            cardCombinations[8] = straightPos(); //there is a straight flush at this number
        } else {
            cardCombinations[4] = straightPos(); //there is a normal straight present
        }
    }   
    if (isFlush() == true && straightPos() == -1) { //normal flush
        for(int j = 1; sizeof(rank); j++) {
            if(rank[j] != 0) {
                cardCombinations[5] = cardCombinations[5] + (j * rank[j]);                       
            }
        }
    }
    if (cardCombinations[1] != 0 && cardCombinations[3] != 0) { //full house
        cardCombinations[6] = (cardCombinations[1] * 2) + (cardCombinations[3] * 3);
    }
    
    if (handRank == 0) { //high card
        rankValue = cardCombinations[0];
    } else if (handRank == 1) { //one pair
        rankValue = (cardCombinations[1] * 2);
    } else if (handRank == 2) { //two pair
        rankValue = (cardCombinations[1] * 2) + (cardCombinations[2] * 2);
    } else if (handRank == 3) { //3 of a kind
        rankValue = (cardCombinations[3] * 3);
    } else if (handRank == 4) { //plain straight
        rankValue = (cardCombinations[4] * 5) + 10;
    } else if (handRank == 5) { //plain flush
        rankValue = cardCombinations[5];
    } else if (handRank == 6) { //full house
        rankValue = cardCombinations[6];
    } else if (handRank == 7) { //4 of a kind
        rankValue = (cardCombinations[7] * 4);
    } else if (handRank == 8) { //straight flush
        rankValue = (cardCombinations[8] * 5) + 10;
    } else { //royal flush
        rankValue = 60;
    }
    
    for (int y = 0; y < sizeof (cardCombinations); y++) { //gets highest present rank
        if (cardCombinations[y] != 0) {
            handRank = y;
        }
    }
    
    for (int z = 2; z < sizeof (rank); z++) { //gets totalCardValue
        if (rank[z] != 0) {
            totalCardValue = totalCardValue + (z * rank[z]);
        }
    }

    value = (handRank * 10000) + (rankValue * 100) + totalCardValue;
}

bool PokerHands::isFlush() {
    //if all cards are of one suit return true
    if (suit[0] == 5 || suit[1] == 5 || suit[2] == 5 || suit[3] == 5) {
        return true;
    }
    return false;
}

int PokerHands::straightPos() {
    //if a number is present and the next 4 are also present
    for (int i = 1; i < sizeof (rank); i++) {
        if (rank[i] == 1 && rank[i + 1] == 1 && rank[i + 2] == 1 && rank[i + 3] == 1
                && rank[i + 4] == 1) {
            return rank[i]; //return the position
        }
    }
    return -1; //returns -1 if no straight
}