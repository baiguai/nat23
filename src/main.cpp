#include "main.h"

int main()
{
    return Nat20::doRoll();
}

namespace Nat20
{
    // Helpers
        void brk()
        {
            std::cout << '\n' << '\n';
        }



    // Core Functions
        int doRoll()
        {
            std::string roll_string;

            while (true)
            {
                std::cout << "Roll:" << '\n';
                std::getline(std::cin, roll_string);

                if (roll_string == "q")
                {
                    break;
                }

                if (roll_string == "?" || roll_string == "")
                {
                    showHelp();
                    continue;
                }

                parseRoll(roll_string);
            }

            return 0;
        }

        void showHelp()
        {
            std::cout << "Example: 2*(2)4d6"; brk();
        }

        void parseRoll(std::string rollstring)
        {
            std::cout << "Cool! You rolled some dice! -- " << rollstring << " --"; brk();

            int times { 1 };
            int best_of { 0 };
            int dice_num { 1 };
            int dice_sides { 1 };

            try
            {
                times = std::stoi(getSplit(rollstring, "*", 0, "1"));
                rollstring = getSplit(rollstring, "*", 1, rollstring);

                if (getSplit(rollstring, "(", 0, "NA") != "NA" && getSplit(rollstring, ")", 0, "NA") != "NA")
                {
                    std::string tmp_best = getSplit(rollstring, "(", 1, "");
                    tmp_best = getSplit(tmp_best, ")", 0, "");
                    best_of = std::stoi(tmp_best);
                    rollstring = getSplit(rollstring, ")", 1, rollstring);
                }

                dice_num = std::stoi(getSplit(rollstring, "d", 0, "0"));
                dice_sides = std::stoi(getSplit(rollstring, "d", 1, "0"));

                if (dice_num < 1 || dice_sides < 2)
                {
                    showHelp();
                    return;
                }
            }
            catch (const std::invalid_argument& e)
            {
                showHelp();
                return;
            }

            std::cout << "Number of times: " << times << '\n' << "Number of dice: " << dice_num << '\n' << "Number of sides: " << dice_sides << '\n' << "Best of: " << best_of; brk();
        }


    // Dice Methods
        std::string getSplit(std::string rollstring, std::string delimiter, int position, std::string defvalue)
        {
            if (rollstring.find(delimiter) == std::string::npos)
            {
                return defvalue;
            }

            if (position == 0)
            {
                return rollstring.substr(0, rollstring.find(delimiter));
            }
            if (position == 1)
            {
                return rollstring.substr(rollstring.find(delimiter)+1);
            }

            return "";
        }
}
