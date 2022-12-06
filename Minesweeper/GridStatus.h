#pragma once

namespace minesweeper
{
    /// <summary>
    /// The grid status.
    /// </summary>
    enum GridStatus
    {
        /// <summary>
        /// Closed grid.
        /// </summary>
        Closed,

        /// <summary>
        /// Open grid.
        /// </summary>
        Open,

        /// <summary>
        /// Flagged grid.
        /// </summary>
        Flagged,
    };
}