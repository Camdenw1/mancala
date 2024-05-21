// Board.cpp

#include "Board.h"
#include <iostream>

Board::Board(int nHoles, int nInitialBeansPerHole) {
    if (nHoles < 1){
        m_holes = 2; // the pots count as holes
    }else{
        m_holes = nHoles + 1; // the pots count as holes
    }
    if(nInitialBeansPerHole < 0){
        nInitialBeansPerHole = 0;
    }
    for(int i = 0; i < m_holes; i++){
        northHoles.push_back(nInitialBeansPerHole); // hole 0 is North pot
        southHoles.push_back(nInitialBeansPerHole); // hole 0 is South pot
    }
    // set pots to 0
    northHoles[0] = 0;
    southHoles[0] = 0;
}

Board::Board(const Board& other){
    m_holes = other.m_holes;
    for(int i = 0; i<=other.holes(); i++){
        northHoles.push_back(other.beans(NORTH,i));
    }
    // southholes has to be pushed back backwards because the way I implemented it
    southHoles.push_back(other.beans(SOUTH,0));
    for(int i = other.holes(); i>0; i--){
        southHoles.push_back(other.beans(SOUTH,i));
    }
}

int Board::holes() const {
    return m_holes - 1; // returns holes not including pot
}

int Board::beans(Side s, int hole) const {
    // invalid hole number
    if(hole < 0 || hole >= m_holes) return -1;
    
    // flips south holes
    if(s == SOUTH && hole != 0){
        hole = m_holes - hole;
    }
    // find beans
    if(s == NORTH){
        return northHoles[hole];
    }else{
        return southHoles[hole];
    }
}

int Board::beansInPlay(Side s) const {
    // total to keep track of beans
    int total = 0;
    // if north tally north holes else tally south holes
    if(s == NORTH){
        for(int i = 1; i < m_holes; i++){
            total += northHoles[i];
        }
    }else{
        for(int i = 1; i < m_holes; i++){
            total += southHoles[i];
        }
    }
    return total;
}

int Board::totalBeans() const {
    // total keeps track of totalBeans
    int total = 0;
    // all 4 parts of the gameboard where beans exists are added to total
    total += beansInPlay(NORTH);
    total += beansInPlay(SOUTH);
    total += beans(NORTH,POT);
    total += beans(SOUTH,POT);
    return total;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
    if(hole < 1 || hole >= m_holes || beans(s,hole) == 0) return false;
    
    // take the beans in the hole and put them in your hand
    int beansInHand = beans(s,hole);
    // empty current hole
    setBeans(s, hole, 0);
    
    // distribute beans
    endSide = s;
    
    while(beansInHand > 0){
        // behavior when gets to pot
        // either skip if not your pot or don't if it is your pot
        if(hole == 0){
            if(endSide == NORTH){
                endSide = SOUTH;
                hole = 1;
            }else{
                endSide = NORTH;
                hole = holes();
            }
            beansInHand--;
            setBeans(endSide, hole, beans(endSide,hole)+1);
        }else if(hole == 1 && endSide == NORTH){
            // behavior when approaching pot from North
            hole--;
            if(endSide == s){
                beansInHand--;
                setBeans(s, POT, beans(s,POT)+1);
            }else{
                hole = 1;
                endSide = SOUTH;
            }
        }else if(hole == holes() && endSide == SOUTH){
            // behavior when approaching pot from south
            hole = 0;
            if(endSide == s){
                beansInHand--;
                setBeans(s, POT, beans(s,POT)+1);
            }else{
                hole = holes();
                endSide = NORTH;
            }
        }else{
            // standard behavior
            if(endSide == NORTH){
                hole--;
                beansInHand--;
                setBeans(endSide, hole, beans(endSide,hole)+1);
            }else{
                hole++;
                beansInHand--;
                setBeans(endSide, hole, beans(endSide,hole)+1);
            }
        }
    }
    endHole = hole;
    return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner) {
    if(hole < 1 || hole >= m_holes) return false;

    // add beans to pot
    setBeans(potOwner, 0, beans(potOwner, 0)+beans(s,hole));
    // add beans to pot
    setBeans(s, hole, 0);
    return true;
}

bool Board::setBeans(Side s, int hole, int beans) {
    if(hole < 0 || hole >= m_holes) return false;
    
    if(s == SOUTH && hole != 0){
        hole = m_holes - hole;
    }
    
    if(beans < 0) return false;
    if(s == NORTH){
        northHoles[hole] = beans;
    }else{
        southHoles[hole] = beans;
    }
    return true;
}

