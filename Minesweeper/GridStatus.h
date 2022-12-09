#pragma once

namespace Minesweeper::MineMap
{
    /// <summary>
    /// The grid status.
    /// </summary>
    enum GridStatus
    {
        /// <summary>
        /// Closed grid.
        /// </summary>
        closed,

        /// <summary>
        /// Open grid.
        /// </summary>
        open,

        /// <summary>
        /// Flagged grid.
        /// </summary>
        flagged,
    };
}