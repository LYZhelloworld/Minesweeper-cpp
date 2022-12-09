#pragma once
#include <functional>
#include <string>

namespace Minesweeper::Parsers
{
    /// <summary>
    /// The type of the callback function.
    /// </summary>
    using Callback = std::function<void(Minesweeper::MineMap::MineMap&)>;

    /// <summary>
    /// Parses input and executes.
    /// </summary>
    /// <param name="input">The input.</param>
    /// <returns>The action from the parsed result.</returns>
    Callback parse(std::string input);
}
