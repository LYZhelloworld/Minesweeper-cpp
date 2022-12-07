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
        NotStarted,

        /// <summary>
        /// The game has started.
        /// </summary>
        Started,

        /// <summary>
        /// The game is over.
        /// </summary>
        Over,
    };
}
