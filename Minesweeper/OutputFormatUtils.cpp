#include <algorithm>
#include <iostream>
#include <ranges>
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
        auto trimmed_input = std::string_view(line) | std::views::drop_while(std::isspace) | std::views::reverse | std::views::drop_while(std::isspace) | std::views::reverse;

        return std::string(trimmed_input.begin(), trimmed_input.end());
    }
}
