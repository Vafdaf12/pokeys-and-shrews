#include "GameTest.h"
#include "lair/Lair.h"

#include <iostream>

void GameTest::execute() { testLair(); }
void GameTest::testLair() {
    const char* MAP = "#####"
                      "#### "
                      "#####"
                      " #  #"
                      " ####";
    Lair lair(5, 5);
    for (int i = 0; i < 25; i++) {
        if (MAP[i] == ' ') continue;
        int x = i % 5;
        int y = i / 5;
        lair.addTile(x, y);
    }
    std::cout << "--- INITIAL ---" << std::endl;
    std::cout << lair.toString() << std::endl;

    std::cout << "--- remove(1,1) ---" << std::endl;
    lair.removeTile(1, 1);
    std::cout << lair.toString() << std::endl;

    std::cout << "--- fortify(0,0) ---" << std::endl;
    lair.fortifyTile(0, 0);
    std::cout << lair.toString() << std::endl;
}