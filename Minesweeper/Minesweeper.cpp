#include <iostream>
#include <stdexcept>

#include "MineMap.h"
#include "OutputFormatUtils.h"
#include "Parser.h"

int main()
{
    std::cout << "===== MINESWEEPER =====" << std::endl;

    auto game = Minesweeper::MineMap::MineMap(10, 10, 10);
    Minesweeper::Utils::print_game_state(game);

    for (;;)
    {
        auto input = Minesweeper::Utils::get_user_input();
        try
        {
            auto action = Minesweeper::Parsers::parse(input);

            try
            {
                action(game);

                if (game.get_game_status() == Minesweeper::MineMap::GameStatus::over)
                {
                    if (game.is_winning())
                    {
                        std::cout << "===== YOU WIN =====" << std::endl;
                    }
                    else
                    {
                        std::cout << "===== YOU LOSE =====" << std::endl;
                    }
                }
            }
            catch (Minesweeper::MineMap::PositionOutOfRangeException& e)
            {
                std::cout << e.what() << std::endl;
            }
            catch (Minesweeper::MineMap::TooManyMinesException& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        catch (std::invalid_argument&)
        {
            std::cout << "Invalid argument." << std::endl;
        }
        catch (std::out_of_range&)
        {
            std::cout << "Out of range." << std::endl;
        }

    }
}
