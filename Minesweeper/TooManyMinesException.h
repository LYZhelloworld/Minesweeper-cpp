#pragma once
#include <exception>

namespace Minesweeper::MineMap
{
    /// <summary>
    /// The exception thrown when the mine count is greater than the map size.
    /// </summary>
    class TooManyMinesException :
        public std::exception
    {
    public:
        /// <summary>
        /// Initialises a new instance of the <see cref="TooManyMinesException"/> class.
        /// </summary>
        TooManyMinesException() noexcept;
    };
}

