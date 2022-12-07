#include <iostream>

#include "MineMap.h"
#include "OutputFormatUtils.h"
#include "Parser.h"

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
}
