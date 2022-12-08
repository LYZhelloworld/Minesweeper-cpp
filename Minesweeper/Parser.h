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
    private:
        /// <summary>
        /// Splits a <see cref="std::string"/> into a <see cref="std::vector"/> of <see cref="std::string"/>s.
        /// </summary>
        /// <param name="str">The <see cref="std::string"/> to split.</param>
        /// <param name="delim">The delimiter.</param>
        /// <returns>The <see cref="std::vector"/> of <see cref="std::string"/>s.</returns>
        static std::vector<std::string> Split(const std::string str, const char delim);
    };
}
