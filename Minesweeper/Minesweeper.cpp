#include <iostream>
#include <stdexcept>

#include "MineMap.h"
#include "OutputFormatUtils.h"
#include "Parser.h"
#include "PositionOutOfRangeException.h"
#include "TooManyMinesException.h"

typedef Minesweeper::MineMap::MineMap MineMap;
typedef Minesweeper::MineMap::GameStatus GameStatus;
typedef Minesweeper::Parsers::Parser Parser;
typedef Minesweeper::Utils::OutputFormatUtils OutputFormatUtils;

int main()
{
    std::cout << "===== MINESWEEPER =====" << std::endl;

    MineMap game = MineMap(10, 10, 10);
    OutputFormatUtils::PrintGameState(game);
    
    for (;;)
    {
        auto input = OutputFormatUtils::GetUserInput();
        auto action = Parser::ParseAndExecute(input);
        try
        {
            action(game);

            if (game.GetGameStatus() == GameStatus::Over)
            {
                if (game.IsWinning())
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
        catch (Minesweeper::MineMap::TooManyMinesException e)
        {
            std::cout << e.what() << std::endl;
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
