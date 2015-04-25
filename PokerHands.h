/* 
 * File:   PokerHands.h
 * Author: John
 *
 * Created on February 25, 2015, 3:24 PM
 */

#ifndef POKERHANDS_H
#define	POKERHANDS_H
#include <string>

using namespace std;

class PokerHands {
public:
    PokerHands();
    PokerHands(std::string s);
    PokerHands(const PokerHands& orig);
    virtual ~PokerHands();
    
    int handValue();

private:
   
    int rank[15];
    int suit[4];
    int value;
    string hand;

    void setValue();
    bool isFlush(); //returns true if hand is a flush
    int straightPos(); //returns position of where the straight starts returns -1 if no straight

};

#endif	/* POKERHANDS_H */

