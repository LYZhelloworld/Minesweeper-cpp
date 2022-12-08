#pragma once
#include <functional>
#include <string>
#include <vector>

namespace Minesweeper::Parsers
{
    /// <summary>
    /// The parser to parse user input.
    /// </summary>
    class Parser
    {
    public:
        Parser() = delete;
        ~Parser() = delete;
        Parser(Parser&) = delete;
        Parser(Parser&&) = delete;

        /// <summary>
        /// Parses input and executes.
        /// </summary>
        /// <param name="input">The input.</param>
        /// <returns>The action from the parsed result.</returns>
        static std::function<void(Minesweeper::MineMap::MineMap&)> ParseAndExecute(std::string input);
    };
}
