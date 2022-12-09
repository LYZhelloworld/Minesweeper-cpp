#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <string>

#include "MineMap.h"
#include "OutputFormatUtils.h"
#include "Parser.h"

namespace Minesweeper::Parsers
{
    Callback parse(std::string input)
    {
        auto tokens_view = std::string_view(input)
            | std::views::split(std::string_view(" "))
            | std::views::transform([](auto range) { return std::string_view(range.begin(), range.end()); })
            | std::views::filter([](auto str) { return !str.empty(); });

        std::vector<std::string_view> tokens;
        for (auto token : tokens_view)
        {
            tokens.push_back(token);
        }

        if (tokens.size() < 1)
        {
            return [](auto& mineMap) {
                Minesweeper::Utils::print_game_state(mineMap);
            };
        }

        const auto& cmd = tokens[0];
        auto iequals = [](const std::string_view lhs, const std::string_view rhs) -> bool
        {
            return std::ranges::equal(lhs | std::views::transform(std::tolower), rhs | std::views::transform(std::tolower));
        };

        if (iequals(cmd, "new") || iequals(cmd, "n"))
        {
            if (tokens.size() != 4)
            {
                return [](auto& _) {
                    throw std::invalid_argument("Invalid argument.");
                };
            }

            auto [width, height, mineCount] = std::tuple{ std::stoi(tokens[1].data()), std::stoi(tokens[2].data()), std::stoi(tokens[3].data()) };

            return [width, height, mineCount](auto& mineMap) {
                mineMap = { width, height, mineCount };
                Minesweeper::Utils::print_game_state(mineMap);
            };
        }
        else if (iequals(cmd, "click") || iequals(cmd, "c"))
        {
            if (tokens.size() != 3)
            {
                return [](auto& _) {
                    throw std::invalid_argument("Invalid argument.");
                };
            }

            auto [x, y] = std::tuple{ std::stoi(tokens[1].data()), std::stoi(tokens[2].data()) };

            return [x, y](auto& mineMap) {
                mineMap.click({ x, y });
                Minesweeper::Utils::print_game_state(mineMap);
            };
        }
        else if (iequals(cmd, "flag") || iequals(cmd, "f"))
        {
            if (tokens.size() != 3)
            {
                return [](auto& _) {
                    throw std::invalid_argument("Invalid argument.");
                };
            }

            auto [x, y] = std::tuple{ std::stoi(tokens[1].data()), std::stoi(tokens[2].data()) };

            return [x, y](auto& mineMap) {
                mineMap.flag({ x, y });
                Minesweeper::Utils::print_game_state(mineMap);
            };
        }
        else if (iequals(cmd, "chord") || iequals(cmd, "x"))
        {
            if (tokens.size() != 3)
            {
                return [](auto& _) {
                    throw std::invalid_argument("Invalid argument.");
                };
            }

            auto [x, y] = std::tuple{ std::stoi(tokens[1].data()), std::stoi(tokens[2].data()) };

            return [x, y](auto& mineMap) {
                mineMap.chord({ x, y });
                Minesweeper::Utils::print_game_state(mineMap);
            };
        }
        else if (iequals(cmd, "help") || iequals(cmd, "h") || iequals(cmd, "?"))
        {
            return [](auto& _) {
                std::cout << "{new|n} width height : Start new game." << std::endl
                    << "{click|c} x y : Click a grid." << std::endl
                    << "{chord|x} x y : Check if adjacent square can be opened automatically." << std::endl
                    << "{flag|f} x y : Mark a square as mine with flag (X)." << std::endl
                    << "{help|h|?} : Show this help." << std::endl
                    << "{exit|quit|q} : Exit.";
            };
        }
        else if (iequals(cmd, "exit") || iequals(cmd, "quit") || iequals(cmd, "q"))
        {
            return [](auto& _) {
                exit(0);
            };
        }
        else
        {
            return [](auto& _) {
                throw std::invalid_argument("Invalid argument.");
            };
        }
    }
}
