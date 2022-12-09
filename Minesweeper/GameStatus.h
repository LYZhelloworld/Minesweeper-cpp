#pragma once

namespace Minesweeper::MineMap
{
    /// <summary>
    /// The game status enum.
    /// </summary>
    enum GameStatus
    {
        /// <summary>
        /// The game has not started.
        /// </summary>
        not_started,

        /// <summary>
        /// The game has started.
        /// </summary>
        started,

        /// <summary>
        /// The game is over.
        /// </summary>
        over,
    };
}
