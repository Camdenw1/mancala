#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doPlayerTests()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    //SmartPlayer sp("Lisa");
    //assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 1  ||  n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
    //n = sp.chooseMove(b, SOUTH);
    //assert(n == 1  ||  n == 3);
    cout << "Passed all Player tests" << endl;
}

void doBoardTests()
{
    Board b(3, 2);
    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
                    b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
    b.setBeans(SOUTH, 1, 1);
    b.moveToPot(SOUTH, 2, SOUTH);
    assert(b.beans(SOUTH, 1) == 1  &&
           b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
   b.beansInPlay(SOUTH) == 3);
    assert(b.beansInPlay(NORTH) == 6 && b.beans(NORTH, POT) == 0);
    // cout << b.totalBeans() << endl;
    assert(b.totalBeans() == 11);
    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
                b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
        b.beansInPlay(SOUTH) == 3);
    Side es;
    int eh;
    b.sow(SOUTH, 3, es, eh);
    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
                b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
        b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
    cout << "Passed all Board tests" << endl;
}

void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
    g.display();
      //    Homer
      //   0  1  2
      // 0         0
      //   2  0  0
      //    Bart
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(g.beans(SOUTH, POT) == 0);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   0  1  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(NORTH);
      //   1  0  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   1  0  0
      // 0         3
      //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

    g.move(NORTH);
      //   0  0  0
      // 1         4
      //   0  0  0
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
    cout << "Passed all Game tests" << endl;
}


int main()
{
    Board b1 = Board(2,2);
    b1.setBeans(SOUTH, 1, 1);
    assert(b1.beans(SOUTH, 2) == 2);
    assert(b1.beans(NORTH, 1) == 2);
    assert(b1.beans(SOUTH, 1) == 1);
    Board b2(b1);
    assert(b2.beans(SOUTH, 2) == 2);
    assert(b2.beans(NORTH, 1) == 2);
    assert(b2.beans(SOUTH, 1) == 1);

    Board t1 = Board(3,2);
    assert(t1.beans(NORTH,1) == 2); // beans at a North hole
    assert(t1.beans(SOUTH,1) == 2); // beans at a South hole
    assert(t1.beans(SOUTH,4) == -1); // beans at out of bounds
    assert(t1.beans(SOUTH,-1) == -1); // beans at out of bounds
    assert(t1.beans(NORTH,0) == 0); // beans at North pot
    assert(t1.beans(SOUTH,0) == 0); // beans at South pot
    assert(t1.holes() == 3); // holes
    assert(t1.beansInPlay(NORTH) == 6); // beansInPlay for North
    assert(t1.beansInPlay(SOUTH) == 6); // beansInPlay for South
    assert(t1.totalBeans() == 12); // totalBeans
    assert(!t1.moveToPot(NORTH, 0, NORTH)); // move to pot at pot
    assert(!t1.moveToPot(NORTH, 4, NORTH)); // move to pot out of bounds
    assert(!t1.moveToPot(NORTH, -1, NORTH)); // move to pot out of bounds
    assert(t1.moveToPot(SOUTH, 3, SOUTH)); // move to pot
    assert(t1.beans(SOUTH,0) == 2); // beans at South pot
    assert(t1.beans(SOUTH,3) == 0); // beans at a South hole
    assert(t1.totalBeans() == 12); // totalBeans
    assert(!t1.setBeans(SOUTH, 4, 2)); // setBeans out of bounds
    assert(!t1.setBeans(SOUTH, -1, 2)); // setBeans out of bounds
    assert(!t1.setBeans(SOUTH, 3, -1)); // setBeans negative beans
    assert(t1.setBeans(SOUTH, 3, 2)); // setBeans
    assert(t1.beans(SOUTH,3) == 2); // checking setBeans
    assert(t1.totalBeans() == 14); // checking setBeans
    Side endSide;
    int endHole;
    assert(!t1.sow(NORTH, -1, endSide, endHole)); // sow out of bounds
    assert(!t1.sow(NORTH, 4, endSide, endHole)); // sow out of bounds
    assert(t1.sow(NORTH, 1, endSide, endHole)); // sow
    assert(t1.beans(NORTH,0) == 1); // beans at North pot
    assert(t1.beans(NORTH,1) == 0); // beans at a North hole
    assert(t1.beans(SOUTH,1) == 3); // beans at a South hole

    // human player. Check name and isInteractive
    HumanPlayer hp("Bob");
    assert(hp.name() == "Bob"  &&  hp.isInteractive());
    // smart player. Check name and isInteractive
    SmartPlayer sp("Camden");
    assert(sp.name() == "Camden"  &&  !sp.isInteractive());
    // bad player. Check name and isInteractive
    BadPlayer bp("Sally");
    assert(bp.name() == "Sally"  &&  !bp.isInteractive());
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    b.setBeans(SOUTH, 1, 0);
    // make sure they all choose valid
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 3);
    n = sp.chooseMove(b, SOUTH);
    assert(n == 3);

    // A lot of the given test code does a good job at testing

    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board bg(3, 0);
    bg.setBeans(SOUTH, 1, 2);
    bg.setBeans(NORTH, 2, 1);
    bg.setBeans(NORTH, 3, 2);
    Game g(bg, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
    // tests display()
    g.display();
      //    Homer
      //   0  1  2
      // 0         0
      //   2  0  0
      //    Bart
    g.status(over, hasWinner, winner); // tests status when not over
    assert(!over && g.beans(NORTH, POT) == 0 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(g.beans(SOUTH, POT) == 0);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

    // tests capture and playing the correct move

    g.move(SOUTH);
      //   0  1  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    // tests NORTH playing correct move

    g.move(NORTH);
      //   1  0  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);


    g.move(SOUTH);
      //   1  0  0
      // 0         3
      //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

    // tests end game and makes sure that it sweeps all opponent beans into opponent pot

    g.move(NORTH);
      //   0  0  0
      // 1         4
      //   0  0  0

    // tests status for when there is a winner
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    // tests winner to make sure it is right
    assert(hasWinner && winner == SOUTH);
    cout << "Passed all Game tests" << endl;

    cout << "All tests passed! Good job Camden! Keep it up playa!" << endl;
//    doBoardTests();
//    doPlayerTests();
//    doGameTests();


    HumanPlayer thp("Marge");
    BadPlayer tbp("Homer");
    Board tb(3, 2);
    Game tg(tb, &thp, &tbp);
    tg.play();

    BadPlayer tbp1("Bart");
    SmartPlayer tbp2("Homer");
    Board b0(4, 2);
    Game tg1(b0, &tbp1, &tbp2);
    tg1.play();
    
    
}
