#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "Random.h"
#include <cstddef>
#include <stdexcept>
#include <list>

namespace Nat20
{
    void brk();

    int handleInput();
    void showHelp();
    void parseRoll(std::string rollstring);
    void doRolls(int times, int best_of, int dice_num, int dice_sides, int advantage, int penalty);
    int doRoll(int dice_sides);

    std::string getSplit(std::string rollstring, std::string delimiter, int position, std::string defvalue);
}

#endif
