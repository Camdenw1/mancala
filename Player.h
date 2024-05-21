// Player.h

#ifndef Player_h
#define Player_h

#include "Side.h"
#include "Board.h"
#include <string>
#include <iostream>

class Player {
    public:
        // Constructor
        Player(std::string name);

        // Accessors
        std::string name() const;
        virtual bool isInteractive() const;
        virtual int chooseMove(const Board& b, Side s) const = 0;

        // Destructor
        virtual ~Player();

    private:
        string m_name;
};

class HumanPlayer : public Player {
    public:
        HumanPlayer(std::string name);
        virtual bool isInteractive() const;
        virtual int chooseMove(const Board& b, Side s) const;
};

class BadPlayer : public Player {
    public:
        BadPlayer(std::string name);
        virtual int chooseMove(const Board& b, Side s) const;
        //virtual ~BadPlayer() {};
};


class SmartPlayer: public Player {
    public:
        SmartPlayer(std::string name);
        virtual int chooseMove(const Board& b, Side s) const;
    private:
        int eval(const Board& b, Side s) const;
        void chooseMove(const Board& b, Side s, int& bestHole, int& value, int depth) const;
        bool attemptMove(Side s, int hole, Board &b, Side& endSide, int& endHole) const;
};


#endif /* Player_h */
