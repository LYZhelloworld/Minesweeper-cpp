#include <algorithm>
#include <iostream>
#include <string>

#include "OutputFormatUtils.h"

namespace Minesweeper::Utils
{
    /// <summary>
    /// The character of a closed grid.
    /// </summary>
    const std::string CLOSED_GRID_MARK = "0";

    /// <summary>
    /// The character of an empty grid.
    /// </summary>
    const std::string EMPTY_GRID_MARK = " ";

    /// <summary>
    /// The character of a flag.
    /// </summary>
    const std::string FLAG_MARK = "X";

    /// <summary>
    /// The character of a mine.
    /// </summary>
    const std::string MINE_MARK = "*";

    void print_game_state(const Minesweeper::MineMap::MineMap mineMap)
    {
        std::cout << "Current game state:" << std::endl << std::endl;

        const auto map = mineMap.get_minemap();
        const auto gridStatus = mineMap.get_grid_status();

        // Print Y-axis.
        const auto width = map.size();
        const auto height = map[0].size();

        std::cout << " Y";
        for (auto y = 0; y < height; y++)
        {
            // Only print the last digit.
            std::cout << (y % 10);
        }
        std::cout << std::endl;
        std::cout << "X" << std::endl;

        for (auto x = 0; x < width; x++)
        {
            // Print X-axis.
            // Only print the last digit.
            std::cout << (x % 10) << " ";

            for (auto y = 0; y < height; y++)
            {
                switch (gridStatus[x][y])
                {
                case Minesweeper::MineMap::GridStatus::closed:
                    std::cout << CLOSED_GRID_MARK;
                    break;

                case Minesweeper::MineMap::GridStatus::open:
                    switch (map[x][y])
                    {
                    case Minesweeper::MineMap::MineMap::EMPTY:
                        std::cout << EMPTY_GRID_MARK;
                        break;
                    case Minesweeper::MineMap::MineMap::MINE:
                        std::cout << MINE_MARK;
                        break;
                    default:
                        std::cout << map[x][y];
                        break;
                    }

                    break;

                case Minesweeper::MineMap::GridStatus::flagged:
                    std::cout << FLAG_MARK;
                    break;
                }
            }
            std::cout << std::endl;
        }
    }

    std::string get_user_input()
    {
        std::cout << "Type \"help\", \"h\" or \"?\" to show available commands." << std::endl;
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);

        // Trim string.
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](auto c) {
            return !std::isspace(c);
            }));
        line.erase(std::find_if(line.rbegin(), line.rend(), [](auto c) {
            return !std::isspace(c);
            }).base(), line.end());

        // To lowercase.
        std::transform(line.begin(), line.end(), line.begin(), std::tolower);

        return line;
    }
}
