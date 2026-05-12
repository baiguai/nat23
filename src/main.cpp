#include "main.h"

int main()
{
    if (Nat20::init() == 1)
    {
        return 1;
    }

    return Nat20::handleInput();
}

namespace Nat20
{
    bool DEBUG { false };
    std::string last_roll { "" };
    std::string config { ""};

    // Helpers
        void brk()
        {
            std::cout << '\n' << '\n';
        }



    // Core Functions
        int init()
        {
            std::string filename = "presets.conf";                                                                                                                                                                                                   
            std::filesystem::path file_path = std::filesystem::current_path() / filename;                                                                                                                                                            
            config = file_path;

            if (!std::filesystem::exists(file_path)) {
                std::ofstream ofile(file_path);

                if (!ofile)
                {
                    std::cerr << "Unable to create file." << std::endl;
                    return 1;
                }
            }

            return 0;
        }

        int handleInput()
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

                if (roll_string == "? rolls")
                {
                    showHelpRolls();
                    continue;
                }

                if (roll_string == "? presets")
                {
                    showHelpPresets();
                    continue;
                }

                const std::regex preset_run_pattern("^preset\\s+(\\d+)$");
                std::smatch run_matches;
                if (std::regex_search(roll_string, run_matches, preset_run_pattern)) {
                    int preset_number = std::stoi(run_matches[1].str());
                    runPreset(preset_number);
                    continue;
                }

                const std::regex preset_del_pattern("^delete\\s+(\\d+)$");
                std::smatch del_matches;
                if (std::regex_search(roll_string, del_matches, preset_del_pattern)) {
                    int preset_number = std::stoi(del_matches[1].str());
                    deletePreset(preset_number);
                    continue;
                }

                if (roll_string == "presets")
                {
                    readPresets();
                    continue;
                }

                if (roll_string == "save")
                {
                    savePreset();
                    continue;
                }

                parseRoll(roll_string);
            }

            return 0;
        }

        void showHelp()
        {
            std::string help_txt { "" };

            help_txt += "For rolls help use: ? rolls";
            help_txt += "\n";
            help_txt += "For presets help use: ? presets";
            help_txt += "\n\n\n";


            std::cout << help_txt; brk();
        }

        void showHelpRolls()
        {
            std::string help_txt { "" };

            help_txt += "Basic Roll --  ";
            help_txt += "This is the only required element, it specifies how many dice to roll, and how many faces those dice have (must be more than 1).\n";
            help_txt += "<dice count>d<face count>\n\n";
            help_txt += "Example:\n";
            help_txt += "2d6\n";
            help_txt += "1d100";
            help_txt += "\n\n\n";
            help_txt += "Multiple Rolls --  ";
            help_txt += "If this is present, the basic roll is repeated the specified amount of times.\n";
            help_txt += "<roll count>*<basic roll>\n\n";
            help_txt += "Example:\n";
            help_txt += "2*3d6\n";
            help_txt += "4*1d8";
            help_txt += "\n\n\n";
            help_txt += "Best n of n --  ";
            help_txt += "If present, the total will only take the best n values out of the total rolls specified in the basic roll.\n";
            help_txt += "(<best of count>)<basic roll>\n\n";
            help_txt += "Example:\n";
            help_txt += "(2)4d6\n";
            help_txt += "2*(3)4d8";
            help_txt += "\n\n\n";
            help_txt += "Advantage --  ";
            help_txt += "If this is present, the advantage amount is added to the total.\n";
            help_txt += "<basic roll>+<advantage>\n\n";
            help_txt += "Example:\n";
            help_txt += "3d6+2\n";
            help_txt += "2*(2)3d4+1";
            help_txt += "\n\n\n";
            help_txt += "Penalty --  ";
            help_txt += "If this is present, the penalty amount is removed from the total.\n";
            help_txt += "<basic roll>-<penalty>\n\n";
            help_txt += "Example:\n";
            help_txt += "3d20-2\n";
            help_txt += "3*(2)4d6-2";
            help_txt += "\n\n\n";
            help_txt += "Quit the application\n";
            help_txt += "q";
            help_txt += "\n\n\n";


            std::cout << help_txt; brk();
        }

        void showHelpPresets()
        {
            std::string help_txt { "" };

            help_txt += "List Presets:\n";
            help_txt += "presets\n";
            help_txt += "Lists the saved presets.\n\n";
            help_txt += "save\n";
            help_txt += "Saves the last run roll as a preset.\n\n";
            help_txt += "preset <number>\n";
            help_txt += "Runs the specified preset roll.\n\n";
            help_txt += "delete <number>\n";
            help_txt += "Deletes the specified preset.";

            std::cout << help_txt; brk();
        }

        void parseRoll(std::string rollstring)
        {
            if (DEBUG)
            {
                std::cout << "Cool! You rolled some dice! -- " << rollstring << " --"; brk();
            }

            int times { 1 };
            int best_of { 0 };
            int dice_num { 1 };
            int dice_sides { 1 };
            int advantage { 0 };
            int penalty { 0 };

            last_roll = rollstring;

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

                if (getSplit(rollstring, "+", 0, "NA") != "NA")
                {
                    advantage = std::stoi(getSplit(rollstring, "+", 1, "0"));
                    rollstring = getSplit(rollstring, "+", 0, rollstring);
                }

                if (getSplit(rollstring, "-", 0, "NA") != "NA")
                {
                    penalty = std::stoi(getSplit(rollstring, "-", 1, "0"));
                    rollstring = getSplit(rollstring, "-", 0, rollstring);
                }

                dice_num = std::stoi(getSplit(rollstring, "d", 0, "0"));
                dice_sides = std::stoi(getSplit(rollstring, "d", 1, "0"));

                if (dice_num < 1 || dice_sides < 2)
                {
                    last_roll = "";
                    showHelp();
                    return;
                }
            }
            catch (const std::invalid_argument& e)
            {
                last_roll = "";
                showHelp();
                return;
            }

            if (DEBUG)
            {
                std::cout << "Number of times: " << times << '\n' << "Number of dice: " << dice_num << '\n' << "Number of sides: " << dice_sides << '\n' << "Best of: " << best_of << '\n' << "Advantage: " << advantage << '\n' << "Penalty: " << penalty; brk();
            }

            doRolls(times, best_of, dice_num, dice_sides, advantage, penalty);
        }

        void doRolls(int times, int best_of, int dice_num, int dice_sides, int advantage, int penalty)
        {
            int total { 0 };
            std::list<int> rolls;
            std::string adv { "" };
            std::string pen { "" };

            if (advantage != 0)
            {
                adv = "(+" + std::to_string(advantage) + ") ";
            }
            if (penalty != 0)
            {
                pen = "(-" + std::to_string(penalty) + ") ";
            }

            for (int t{ 0 }; t < times; t++)
            {
                total = 0;
                std::cout << "Roll number " << (t+1) << ":\n";
                std::list<int> roll;
                for (int r{ 0 }; r < dice_num; r++)
                {
                    roll.push_back(doRoll(dice_sides));
                }
                
                for (int itm : roll)
                {
                    std::cout << itm << '\n';
                }

                // handle best of
                roll.sort(std::greater<int>());

                if (best_of > 0 && best_of < dice_num)
                {
                    std::cout << "Best " << best_of << ": ";
                    int count = 0;
                    for (int itm : roll)
                    {
                        if (count < best_of)
                        {
                            total += itm;
                            std::cout << itm;
                            if (count < best_of - 1) std::cout << ", ";
                        }
                        count++;
                    }
                    std::cout << '\n';
                }
                else
                {
                    // No best_of filtering, sum all as before
                    for (int itm : roll)
                        total += itm;
                }

                total = total + advantage;
                total = total - penalty;

                std::cout << "Total: " << adv << pen << total << "\n\n";
            }

            brk();
        }

        int doRoll(int dice_sides)
        {
            return Random::get(1, dice_sides);
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


    // Presets Methods
        void readPresets()
        {
            std::cout << '\n';

            std::ifstream input_file(config);
            std::string line { "" };
            int presetIndex { 1 };

            if (!input_file.is_open()) {
                std::cerr << "Unable to open file." << '\n';
                return;
            }

            while (std::getline(input_file, line)) {
                if (line != "")
                {
                    std::cout << presetIndex << ": " << line << '\n';
                    ++presetIndex;
                }
            }

            if (presetIndex == 1)
            {
                std::cout << "There are no presets saved." << '\n';
            }

            input_file.close(); 

            std::cout << '\n';
        }

        void savePreset()
        {
            if (last_roll == "")
            {
                std::cout << "No previous roll to save." << '\n';
                return;
            }

            std::ifstream input_file(config);

            if (input_file.is_open())
            {
                std::string line;

                while (std::getline(input_file, line))
                {
                    if (line == last_roll)
                    {
                        std::cout << "The preset already exists."; brk();
                        input_file.close();
                        return;
                    }
                }
            }

            std::ofstream output_file(config, std::ios::app);

            if (output_file.is_open())
            {
                output_file << last_roll << '\n';
                output_file.close();                                                                                                                                                                                                             
                std::cout << "Preset saved." << '\n';
            }
            else
            {                                                                                                                                                                                                                             
                std::cerr << "Unable to open configuration file for writing." << '\n';
            }                                                                                                                                                                                                                                    
        }

        void runPreset(int presetNum)
        {
            std::ifstream input_file(config);
            int row {0};

            if (input_file.is_open())
            {
                std::string line;

                while (std::getline(input_file, line))
                {
                    if (row == (presetNum - 1))
                    {
                        if (line == "")
                        {
                            continue;
                        }

                        std::cout << "Running preset: " << line << "\n\n";
                        parseRoll(line);
                        break;
                    }

                    ++row;
                }
            }
        }

        void deletePreset(int presetNum)
        {
            std::ifstream input_file(config);
            int row {0};
            std::string contents { "" };

            if (input_file.is_open())
            {
                std::string line;

                while (std::getline(input_file, line))
                {
                    if (row != (presetNum - 1))
                    {
                        if (contents != "")
                        {
                            contents = contents + '\n';
                        }
                        contents = contents + line;
                    }

                    ++row;
                }
            }

            std::ofstream output_file(config, std::ios::trunc);

            if (output_file.is_open())
            {
                output_file << contents << '\n';
                output_file.close();                                                                                                                                                                                                             
                std::cout << "Preset deleted."; brk();
            }
            else
            {                                                                                                                                                                                                                             
                std::cerr << "Unable to open configuration file for writing." << '\n';
            }                                                                                                                                                                                                                                    
        }
}
