// Game.h

#ifndef Game_h
#define Game_h

#include "Board.h"
class Player;

class Game {
public:
    // Constructor
    Game(const Board& b, Player* south, Player* north);
    // Accessors
    void display() const;
    void status(bool& over, bool& hasWinner, Side& winner) const;
    // Mutators
    bool move(Side s);
    void play();
    int beans(Side s, int hole) const;

private:
    Board m_b;
    Player* m_south;
    Player* m_north;
    Side turn;
};

#endif /* Game_h */
