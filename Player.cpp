// Player.cpp

#include "Player.h"
using namespace std;

//BASE CLASS
Player::Player(std::string name) :m_name(name) {}

Player::~Player() {}

std::string Player::name() const {
    return m_name;
}

bool Player::isInteractive() const {
    return false;
}



// Human Player Implementation
HumanPlayer::HumanPlayer(std::string name) :Player(name) {}

bool HumanPlayer::isInteractive() const {
    return true;
}

int HumanPlayer::chooseMove(const Board &b, Side s) const {
    int hole;
    do {
        cout << "Select a hole, " << name() << ": ";
        cin >> hole;
        if (hole <= 0 || hole > b.holes()) {
            cout << "The hole number must be from 1 to " + to_string(b.holes()) + "." << endl;
        }
        else if (b.beans(s, hole) == 0) {
            cout << "There are no beans in that hole." << endl;
        }
    }
    while (hole <= 0 || hole > b.holes() || b.beans(s, hole) <= 0);
    return hole;
}




// Bad Player Implementation
BadPlayer::BadPlayer(std::string name) :Player(name) {}


int BadPlayer::chooseMove(const Board &b, Side s) const {
    // this bad player just chooses the first valid move based on what is the closest hole that is not empty
    for (int i = 1; i <= b.holes(); i++) {
        if (b.beans(s, i) > 0) {
            cout << name() << " chooses hole " << i << endl;
            return i;
        }
    }
    return -1;
}


// Smart Player Implementation
SmartPlayer::SmartPlayer(std::string name) :Player(name) {}

int SmartPlayer::chooseMove(const Board &b, Side s) const {
    int bestHole, value;
    int depth = 5;
    chooseMove(b, s, bestHole, value, depth);
    cout << name() << " chooses hole " << bestHole << endl;
    return bestHole;
}

void SmartPlayer::chooseMove(const Board& b, Side s, int& bestHole, int& value, int depth) const{
    Side otherSide;
    if(s == NORTH){
        otherSide = SOUTH;
    }else{
        otherSide = NORTH;
    }
    // if no move exists
    if(b.beansInPlay(s) == 0){
        bestHole = -1;
        value = eval(b,SOUTH);
        return;
    }
    // if the criterion says we should not search below this node
    if(depth <= 0){
        bestHole = -1;
        value = eval(b,SOUTH);
        return;
    }
    int f = 1;
    for(int i = 1; i <= b.holes(); i++){
        if(b.beans(s,i) == 0){
            f++;
            continue;
        }
        if(b.beans(s,i) > 0){ // there is a move
            // make the move and do the recursion
            Board temp(b);
            Side endSide;
            int endHole;
            int val;
            int h;
            if(attemptMove(s, i, temp, endSide, endHole)){
                chooseMove(temp, otherSide, h, val, depth-1);
            }else{
                chooseMove(temp, endSide, h, val, depth);
            }
            // unmake the move
            
            // if its the best change bestHole to i
            if(f == i){
                value = val;
                bestHole = i;
            }
            if(s == NORTH){
                // North wants small eval scores
                if(val < value){
                    value = val;
                    bestHole = i;
                }
            }else{
                // South wants large eval scores
                if(val > value){
                    value = val;
                    bestHole = i;
                }
            }
        }
    }
    return;
}

int SmartPlayer::eval(const Board& b, Side s) const { //evaluate for SOUTH
    Side otherSide;
    if(s == NORTH){
        otherSide = SOUTH;
    }else{
        otherSide = NORTH;
    }
    
    int beansFor = b.beansInPlay(s);
    int beansAgainst = b.beansInPlay(otherSide);
    int potFor = b.beans(s, 0);
    int potAgainst = b.beans(otherSide, 0);
    
    // if pot is more than half totalBeans return big number
    // if opponent has that return big negative number
    if(potFor > b.totalBeans()/2){
        return 1000000;
    }else if((potAgainst > b.totalBeans()/2)){
        return -1000000;
    }
    
    if (beansFor == 0 || beansAgainst == 0) {
        if (beansFor + potFor > beansAgainst - potAgainst) {
            return 1000000; // large positive number because good for side s
        }
        else if (beansFor + potFor < beansAgainst - potAgainst) {
            return -1000000; // large negative number because bad for side s
        }
        else { //draw
            return 0;
        }
    }
    return beansFor + (potFor*4) - beansAgainst - (potAgainst*4);
}


bool SmartPlayer::attemptMove(Side s, int hole, Board &b, Side& endSide, int& endHole) const {
    if (b.sow(s, hole, endSide, endHole)) {
        // if endHole is 0 the turn is not over
        if (endHole == 0) {
            return false;
        }else if (endSide == s) {
            // account for capture
            if (b.beans(s, endHole) == 1 && b.beans(opponent(s), endHole) > 0) {
                b.moveToPot(opponent(s), endHole, s);
                b.moveToPot(s, endHole, s);
            }
        }
        return true;
    }
    return false; // should not get here
}
