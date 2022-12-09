#pragma once
#include "MineMap.h"

namespace Minesweeper::Utils
{
    /// <summary>
    /// Prints game state.
    /// </summary>
    /// <param name="mineMap">The <see cref="MineMap"/> object.</param>
    void print_game_state(const Minesweeper::MineMap::MineMap mineMap);

    /// <summary>
    /// Gets user input.
    /// </summary>
    /// <returns>The user input.</returns>
    std::string get_user_input();
}
