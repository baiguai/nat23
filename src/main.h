#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include "Random.h"
#include <cstddef>
#include <stdexcept>
#include <list>

namespace Nat20
{
    void brk();

    int init();
    int handleInput();
    void showHelp();
    void showHelpRolls();
    void showHelpPresets();
    void parseRoll(std::string rollstring);
    void doRolls(int times, int best_of, int dice_num, int dice_sides, int advantage, int penalty);
    int doRoll(int dice_sides);

    void readPresets();
    void savePreset();
    void runPreset(int presetNum);
    void deletePreset(int presetNum);

    std::string getSplit(std::string rollstring, std::string delimiter, int position, std::string defvalue);
}

#endif
