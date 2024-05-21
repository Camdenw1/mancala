// Board.h

#ifndef Board_h
#define Board_h

#include "Side.h"
#include <vector>
using namespace std;

class Board {
    
public:
    // Constructor
    Board(int nHoles, int nInitialBeansPerHole);
    Board(const Board& other);
    
    // Accessors
    int holes() const;
    int beans(Side s, int hole) const;
    int beansInPlay(Side s) const;
    int totalBeans() const;
    
    // Mutators
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool moveToPot(Side s, int hole, Side potOwner);
    bool setBeans(Side s, int hole, int beans);
private:
    vector<int> northHoles;
    vector<int> southHoles;
    int m_holes; //number of holes in each side
};

#endif /* Board_h */
