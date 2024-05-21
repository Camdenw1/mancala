// Game.cpp

#include "Game.h"
#include "Player.h"
#include "Board.h"

Game::Game(const Board& b, Player* south, Player* north) : m_b(b), m_south(south), m_north(north), turn(SOUTH){
}

void Game::display() const {
    // print out North name
    cout << "     " + m_north->name() << endl;
    
    // print out North holes
    cout << "   ";
    for (int i = 1; i <= m_b.holes(); i++) {
        cout << " " + to_string(m_b.beans(NORTH, i)) + " ";
    }
    cout << endl;

    // print out North and South pots
    cout << "  " + to_string(m_b.beans(NORTH, POT));
    for (int i = 1; i <= m_b.holes(); i++) {
        cout << "   ";
    }
    cout << to_string(m_b.beans(SOUTH, POT)) + " " << endl;

    // print out South holes
    cout << "   ";
    for (int i = 1; i <= m_b.holes(); i++) {
        cout << " " + to_string(m_b.beans(SOUTH, i)) + " ";
    }
    cout << endl;

    // print out South name
    cout << "     " + m_south->name() << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const {
    Side otherSide;
    if(turn == NORTH){
        otherSide = SOUTH;
    }else{
        otherSide = NORTH;
    }
    
    over = true;
    
    // check if it's over
    for(int i = 1; i <= m_b.holes(); i++){
        if(m_b.beansInPlay(turn) > 0){
            over = false;
            return;
        }
    }
    
    for(int i = 1; i <= m_b.holes(); i++){
        if(m_b.beansInPlay(otherSide) > 0){
            over = false;
            return;
        }
    }
    
    // this code is irrelevant
    int totalOppo = 0;
    for(int i = 1; i <= m_b.holes(); i++){
        totalOppo += m_b.beans(otherSide, i);
    }
    // end of irrelevant portion
    
    // if turn's pot is bigger turn is the winner
    // if else then not turn is the winner
    // else it is a tie
    if(m_b.beans(turn,POT) > m_b.beans(otherSide,POT) + totalOppo){
        hasWinner = true;
        winner = turn;
    }else if(m_b.beans(turn,POT) < m_b.beans(otherSide,POT) + totalOppo){
        hasWinner = true;
        winner = otherSide;
    }else{
        hasWinner = false;
    }
    return;
}

bool Game::move(Side s) {
    // create otherSide to keep track of opponent side
    Side otherSide;
    if(s == NORTH){
        otherSide = SOUTH;
    }else{
        otherSide = NORTH;
    }
    
    // check if there is a possible move
    // if none, end the game
    if(m_b.beansInPlay(s) <= 0){
        // sweep opponents beans into his pot
        for(int i = 1; i <= m_b.holes(); i++){
            m_b.setBeans(otherSide, POT, m_b.beans(otherSide,i)+ m_b.beans(otherSide,POT));
            m_b.setBeans(otherSide, i, 0);
        }
        if(s == NORTH){
            cout << m_north->name() << " has no beans left to sow." << endl;
            cout << "Sweeping remaining beans into " << m_south->name() << "'s pot." << endl;
        }else{
            cout << m_south->name() << " has no beans left to sow." << endl;
            cout << "Sweeping remaining beans into " << m_north->name() << "'s pot." << endl;
        }
        display();
        return false;
    }
    
    // choose what move to make
    int hole;
    Side endSide = s;
    int endHole;
    
    do{
        // decide what move to make
        if(s == SOUTH){
            hole = m_south->chooseMove(m_b, SOUTH);
        }else{
            hole = m_north->chooseMove(m_b, NORTH);
        }
        // do the move
        m_b.sow(s, hole, endSide, endHole);
        
        // include captures
        if(endHole != POT && m_b.beans(otherSide, endHole) > 0 &&  m_b.beans(s, endHole) == 1 && endSide == s){
            m_b.setBeans(s, POT, m_b.beans(otherSide, endHole)+m_b.beans(s,POT)+1);
            m_b.setBeans(s, endHole, 0);
            m_b.setBeans(otherSide, endHole, 0);
            if(turn == NORTH){
                turn = SOUTH;
            }else{
                turn = NORTH;
            }
            display();
            return true;
        }
        // end captures
        
        // If no more valid moves, clean slate
        if(endHole == POT && m_b.beansInPlay(s) == 0){
            for(int i = 1; i <= m_b.holes(); i++){
                m_b.setBeans(otherSide, POT, m_b.beans(otherSide,i)+ m_b.beans(otherSide,POT));
                m_b.setBeans(otherSide, i, 0);
            }
        }
        // display after partial move is complete
        display();
        // do again if ended in pot
    }while(endHole == POT && m_b.beansInPlay(s) > 0);
    
    
    // switch turns
    if(turn == NORTH){
        turn = SOUTH;
    }else{
        turn = NORTH;
    }
    return true;
}

void Game::play() {
    bool over;
    bool hasWinner;
    Side winner;
    display();
    do{
        move(turn);
        // display();
        if (!m_south->isInteractive() && !m_north->isInteractive()) {
                    cout << "Press ENTER to continue.";
                    cin.ignore(10000, '\n');
                }
        status(over, hasWinner, winner);
    }while(!over);
    if(hasWinner){
        if(winner == NORTH){
            cout << "The winner is " + m_north->name() << endl;
        }else{
            cout << "The winner is " + m_south->name() << endl;
        }
    }else{
        cout << "It's a tie!" << endl;
    }
    return;
}

int Game::beans(Side s, int hole) const {
    return m_b.beans(s, hole);
}

