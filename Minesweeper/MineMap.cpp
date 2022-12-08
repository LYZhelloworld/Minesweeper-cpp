#include <algorithm>
#include <random>
#include <ranges>

#include "MineMap.h"
#include "PositionOutOfRangeException.h"
#include "TooManyMinesException.h"

namespace Minesweeper::MineMap
{
    constexpr auto POSITION_OUT_OF_RANGE_EXCEPTION = ("The position is out of range.");

    MineMap::MineMap(const std::size_t width, const std::size_t height, const int mineCount)
        : m_width(width), m_height(height), m_mineCount(mineCount)
    {
        if (mineCount > width * height)
        {
            throw TooManyMinesException();
        }

        m_mineMap.resize(width, std::vector<int>(height, 0));
        m_gridStatus.resize(width, std::vector<GridStatus>(height, GridStatus::Closed));

        m_gameStatus = NotStarted;
    }

    const std::vector<std::vector<MineMapValue>> MineMap::GetMineMap() const
    {
        return m_mineMap;
    }

    const std::vector<std::vector<GridStatus>> MineMap::GetGridStatus() const
    {
        return m_gridStatus;
    }

    void MineMap::Click(const Position pos)
    {
        if (m_gameStatus == Over)
        {
            return;
        }

        if (!IsValidPosition(pos))
        {
            throw PositionOutOfRangeException();
        }

        if (m_gameStatus == NotStarted)
        {
            GenerateMines(pos);
            m_gameStatus = Started;
        }

        const auto x = pos.first;
        const auto y = pos.second;

        if (m_gridStatus[x][y] != Closed)
        {
            return;
        }

        m_gridStatus[x][y] = Open;

        if (m_mineMap[x][y] == MineMap::MINE)
        {
            m_gameStatus = Over;
            return;
        }

        if (m_mineMap[x][y] == MineMap::EMPTY)
        {
            // Open adjacent grids.
            for (auto i = x - 1; i <= x + 1; ++i)
            {
                for (auto j = y - 1; j <= y + 1; ++j)
                {
                    if (i == x && j == y)
                    {
                        continue;
                    }

                    if (IsValidPosition({ i, j }) && m_gridStatus[i][j] == Closed)
                    {
                        Click({ i, j });
                    }
                }
            }
        }

        if (IsWinning())
        {
            m_gameStatus = Over;
        }
    }

    void MineMap::Chord(const Position pos)
    {
        if (m_gameStatus == Over || m_gameStatus == NotStarted)
        {
            return;
        }

        if (!IsValidPosition(pos))
        {
            throw PositionOutOfRangeException();
        }

        const auto x = pos.first;
        const auto y = pos.second;

        if (m_gridStatus[x][y] != Open)
        {
            return;
        }

        if (GetAdjacentFlags(pos) == m_mineMap[x][y])
        {
            // Open adjacent grids.
            for (auto i = x - 1; i <= x + 1; i++)
            {
                for (auto j = y - 1; j <= y + 1; j++)
                {
                    if (i == x && j == y)
                    {
                        continue;
                    }

                    auto pos = Position(i, j);
                    if (IsValidPosition(pos))
                    {
                        Click({ i, j });
                    }
                }
            }
        }
    }

    void MineMap::Flag(const Position pos)
    {
        if (m_gameStatus == Over)
        {
            return;
        }

        if (!IsValidPosition(pos))
        {
            throw PositionOutOfRangeException();
        }

        const auto x = pos.first;
        const auto y = pos.second;

        if (m_gridStatus[x][y] != Closed)
        {
            return;
        }

        m_gridStatus[x][y] = m_gridStatus[x][y] == Flagged ? Closed : Flagged;
    }

    const GameStatus MineMap::GetGameStatus() const noexcept
    {
        return m_gameStatus;
    }

    bool MineMap::IsWinning() const noexcept
    {
        for (auto x = 0; x < m_width; x++)
        {
            for (auto y = 0; y < m_height; y++)
            {
                if (m_gridStatus[x][y] == Open && m_mineMap[x][y] == MineMap::MINE)
                {
                    // Clicked grid with mine.
                    return false;
                }

                if (m_gridStatus[x][y] != Open && m_mineMap[x][y] != MineMap::MINE)
                {
                    // Still got closed empty grids or wrong flags.
                    return false;
                }
            }
        }

        return true;
    }

    void MineMap::GenerateMines(const Position clickedPos)
    {
        if (clickedPos.first >= m_width || clickedPos.second >= m_height)
        {
            throw PositionOutOfRangeException();
        }

        m_gameStatus = Started;

        // Generate usable positions.
        auto positions = std::vector<Position>();
        for (auto x = 0; x < m_width; x++)
        {
            for (auto y = 0; y < m_height; y++)
            {
                if (x == clickedPos.first && y == clickedPos.second)
                {
                    // Clicked grid will not have mine.
                    continue;
                }

                positions.push_back(Position(x, y));
            }
        }

        // Shuffle all usable positions.
        std::ranges::shuffle(positions, std::mt19937(std::random_device()()));

        // Pick the positions we need.
        std::ranges::for_each(positions | std::views::take(m_mineCount), [&](const Position& pos) {
            m_mineMap[pos.first][pos.second] = MineMap::MINE;
            });

        // Generate mine hints.
        std::ranges::for_each(std::views::iota(0, (int)m_width), [&](int x) {
            std::ranges::for_each(std::views::iota(0, (int)m_height), [&](int y) {
                if (m_mineMap[x][y] == MineMap::MINE)
                {
                    // This is a mine.
                    return;
                }

        m_mineMap[x][y] = GetAdjacentMineCount({ x, y });
                });
            });
    }

    int MineMap::GetAdjacentMineCount(const Position pos) const noexcept
    {
        auto count = 0;

        for (auto x = pos.first - 1; x <= pos.first + 1; x++)
        {
            for (auto y = pos.second - 1; y <= pos.second + 1; y++)
            {
                if (x == pos.first && y == pos.second)
                {
                    // This is the center grid.
                    continue;
                }

                if (IsValidPosition({ x, y }))
                {
                    count += m_mineMap[x][y] == MineMap::MINE ? 1 : 0;
                }
            }
        }

        return count;
    }

    int MineMap::GetAdjacentFlags(const Position pos) const noexcept
    {
        auto count = 0;

        for (auto x = pos.first - 1; x <= pos.first + 1; x++)
        {
            for (auto y = pos.second - 1; y <= pos.second + 1; y++)
            {
                if (x == pos.first && y == pos.second)
                {
                    // This is the center grid.
                    continue;
                }

                if (IsValidPosition({ x, y }))
                {
                    count += m_gridStatus[x][y] == Flagged ? 1 : 0;
                }
            }
        }

        return count;
    }

    bool MineMap::IsValidPosition(const Position pos) const noexcept
    {
        return pos.first >= 0 && pos.first < m_width&& pos.second >= 0 && pos.second < m_height;
    }
}