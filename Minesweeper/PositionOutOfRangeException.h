#pragma once
#include <exception>

namespace Minesweeper::MineMap
{
    /// <summary>
    /// The exception thrown when the position is out of the map.
    /// </summary>
    class PositionOutOfRangeException :
        public std::exception
    {
    public:
        /// <summary>
        /// Initialises a new instance of the <see cref="PositionOutOfRangeException"/> class.
        /// </summary>
        PositionOutOfRangeException() noexcept;
    };
}


