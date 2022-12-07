#pragma once
#include <vector>

#include "MineMap.h"

namespace Minesweeper::Utils
{
    /// <summary>
    /// The utility class of output formats.
    /// </summary>
    class OutputFormatUtils
    {
    public:
        OutputFormatUtils() = delete;
        ~OutputFormatUtils() = delete;
        OutputFormatUtils(OutputFormatUtils&) = delete;
        OutputFormatUtils(OutputFormatUtils&&) = delete;

        /// <summary>
        /// Prints game state.
        /// </summary>
        /// <param name="mineMap">The <see cref="MineMap"/> object.</param>
        static void PrintGameState(const Minesweeper::MineMap::MineMap mineMap);

        /// <summary>
        /// Gets user input.
        /// </summary>
        /// <returns>The user input.</returns>
        static std::string GetUserInput();
    };
}
