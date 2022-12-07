#pragma once
#include <vector>

#include "MineMap.h"

namespace Minesweeper
{
    /// <summary>
    /// The utility class of output formats.
    /// </summary>
    class OutputFormatUtils
    {
    public:
        /// <summary>
        /// Prints game state.
        /// </summary>
        /// <param name="mineMap">The <see cref="MineMap"/> object.</param>
        static void PrintGameState(MineMap mineMap);

        /// <summary>
        /// Gets user input.
        /// </summary>
        /// <returns>The user input.</returns>
        static std::string GetUserInput();
    };
}
