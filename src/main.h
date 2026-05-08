#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "Random.h"
#include <cstddef>
#include <stdexcept>

namespace Nat20
{
    void brk();

    int doRoll();
    void showHelp();
    void parseRoll(std::string rollstring);

    std::string getSplit(std::string rollstring, std::string delimiter, int position, std::string defvalue);
}

#endif
