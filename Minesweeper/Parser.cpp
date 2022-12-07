#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>

#include "MineMap.h"
#include "Parser.h"

namespace Minesweeper::Parsers
{
    typedef Minesweeper::MineMap::MineMap MineMap;
    typedef Minesweeper::MineMap::Position Position;

    std::function<void(MineMap&)> Parser::ParseAndExecute(std::string input)
    {
        std::vector<std::string> tokensWithEmpty = Split(input, ' ');
        std::vector<std::string> tokens;
        std::copy_if(tokensWithEmpty.begin(), tokensWithEmpty.end(), std::back_inserter(tokens), [](std::string s) {
            return !s.empty();
            });

        if (tokens.size() < 1)
        {
            return [](MineMap& _) {
                PrintIllegalArgument();
            };
        }

        std::for_each(tokens.begin(), tokens.end(), [](std::string str) {
            std::transform(str.begin(), str.end(), str.begin(), std::tolower);
            });
        const auto& cmd = tokens[0];

        if (cmd == "new" || cmd == "n")
        {
            if (tokens.size() != 4)
            {
                return [](MineMap& _) {
                    PrintIllegalArgument();
                };
            }

            try
            {
                return [&tokens](MineMap& mineMap) {
                    mineMap = MineMap(std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]));
                };
            }
            catch (std::invalid_argument)
            {
                return [](MineMap& _) {
                    PrintIllegalArgument();
                };
            }
        }
        else if (cmd == "click" || cmd == "c")
        {
            if (tokens.size() != 3)
            {
                return [](MineMap& _) {
                    PrintIllegalArgument();
                };
            }

            try
            {
                return [&tokens](MineMap& mineMap) {
                    mineMap.Click(Position(std::stoi(tokens[1]), std::stoi(tokens[2])));
                };
            }
            catch (std::invalid_argument)
            {
                return [](MineMap& _) {
                    PrintIllegalArgument();
                };
            }
        }
        else if (cmd == "flag" || cmd == "f")
        {
            if (tokens.size() != 3)
            {
                return [](MineMap& _) {
                    PrintIllegalArgument();
                };
            }

            try
            {
                return [&tokens](MineMap& mineMap) {
                    mineMap.Flag(Position(std::stoi(tokens[1]), std::stoi(tokens[2])));
                };
            }
            catch (std::invalid_argument)
            {
                return [](MineMap& _) {
                    PrintIllegalArgument();
                };
            }
        }
        else if (cmd == "chord" || cmd == "h")
        {
            if (tokens.size() != 3)
            {
                return [](MineMap& _) {
                    PrintIllegalArgument();
                };
            }

            try
            {
                return [&tokens](MineMap& mineMap) {
                    mineMap.Chord(Position(std::stoi(tokens[1]), std::stoi(tokens[2])));
                };
            }
            catch (std::invalid_argument)
            {
                return [](MineMap& _) {
                    PrintIllegalArgument();
                };
            }
        }
        else if (cmd == "help" || cmd == "h" || cmd == "?")
        {
            return [](MineMap& _) {
                std::cout << "{new|n} width height : Start new game." << std::endl
                    << "{click|c} x y : Click a grid." << std::endl
                    << "{chord|h} x y : Check if adjacent square can be opened automatically." << std::endl
                    << "{flag|f} x y : Mark a square as mine with flag (X)." << std::endl
                    << "{help|h|?} : Show this help." << std::endl
                    << "{exit|quit|q} : Exit.";
            };
        }
        else if (cmd == "exit" || cmd == "quit" || cmd == "q")
        {
            return [](MineMap& _) {
                exit(0);
            };
        }
        else
        {
            return [](MineMap& _) {
                PrintIllegalArgument();
            };
        }
    }

    std::vector<std::string> Parser::Split(std::string str, char delim)
    {
        std::vector<std::string> result;
        std::for_each(str.begin(), str.end(), [&result, &delim](char c)
            {
                if (c == delim)
                {
                    result.push_back(std::string());
                }
                else
                {
                    result.back().push_back(c);
                }
            });
        return result;
    }

    void Parser::PrintIllegalArgument()
    {
        std::cout << "Illegal argument." << std::endl;
    }
}
