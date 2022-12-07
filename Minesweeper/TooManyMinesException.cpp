#include "TooManyMinesException.h"

namespace Minesweeper::MineMap
{
    TooManyMinesException::TooManyMinesException() noexcept
        : std::exception("The mine count is greater than the map size.")
    {
    }
}