#include "PositionOutOfRangeException.h"

namespace Minesweeper::MineMap
{
    PositionOutOfRangeException::PositionOutOfRangeException() noexcept
        : std::exception("The position is out of range.")
    {
    }
}