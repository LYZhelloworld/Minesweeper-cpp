#include <algorithm>
#include <random>
#include <ranges>

#include "MineMap.h"

namespace Minesweeper::MineMap
{
    MineMap::MineMap(const std::size_t width, const std::size_t height, const int mineCount)
        : m_width(width), m_height(height), m_mineCount(mineCount)
    {
        if (mineCount > width * height)
        {
            throw TooManyMinesException();
        }

        m_mineMap.resize(width, std::vector<int>(height, 0));
        m_gridStatus.resize(width, std::vector<GridStatus>(height, GridStatus::closed));

        m_gameStatus = not_started;
    }

    const std::vector<std::vector<MineMapValue>> MineMap::get_minemap() const
    {
        return m_mineMap;
    }

    const std::vector<std::vector<GridStatus>> MineMap::get_grid_status() const
    {
        return m_gridStatus;
    }

    void MineMap::click(const Position pos)
    {
        if (m_gameStatus == over)
        {
            return;
        }

        if (!is_valid_position(pos))
        {
            throw PositionOutOfRangeException();
        }

        if (m_gameStatus == not_started)
        {
            generate_mines(pos);
            m_gameStatus = started;
        }

        const auto x = pos.first;
        const auto y = pos.second;

        if (m_gridStatus[x][y] != closed)
        {
            return;
        }

        m_gridStatus[x][y] = open;

        if (m_mineMap[x][y] == MineMap::MINE)
        {
            m_gameStatus = over;
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

                    if (is_valid_position({ i, j }) && m_gridStatus[i][j] == closed)
                    {
                        click({ i, j });
                    }
                }
            }
        }

        if (is_winning())
        {
            m_gameStatus = over;
        }
    }

    void MineMap::chord(const Position pos)
    {
        if (m_gameStatus == over || m_gameStatus == not_started)
        {
            return;
        }

        if (!is_valid_position(pos))
        {
            throw PositionOutOfRangeException();
        }

        const auto x = pos.first;
        const auto y = pos.second;

        if (m_gridStatus[x][y] != open)
        {
            return;
        }

        if (get_adjacent_flags(pos) == m_mineMap[x][y])
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
                    if (is_valid_position(pos))
                    {
                        click({ i, j });
                    }
                }
            }
        }
    }

    void MineMap::flag(const Position pos)
    {
        if (m_gameStatus == over)
        {
            return;
        }

        if (!is_valid_position(pos))
        {
            throw PositionOutOfRangeException();
        }

        const auto x = pos.first;
        const auto y = pos.second;

        if (m_gridStatus[x][y] != closed)
        {
            return;
        }

        m_gridStatus[x][y] = m_gridStatus[x][y] == flagged ? closed : flagged;
    }

    const GameStatus MineMap::get_game_status() const noexcept
    {
        return m_gameStatus;
    }

    bool MineMap::is_winning() const noexcept
    {
        for (auto x = 0; x < m_width; x++)
        {
            for (auto y = 0; y < m_height; y++)
            {
                if (m_gridStatus[x][y] == open && m_mineMap[x][y] == MineMap::MINE)
                {
                    // Clicked grid with mine.
                    return false;
                }

                if (m_gridStatus[x][y] != open && m_mineMap[x][y] != MineMap::MINE)
                {
                    // Still got closed empty grids or wrong flags.
                    return false;
                }
            }
        }

        return true;
    }

    void MineMap::generate_mines(const Position clickedPos)
    {
        if (clickedPos.first >= m_width || clickedPos.second >= m_height)
        {
            throw PositionOutOfRangeException();
        }

        m_gameStatus = started;

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
        std::ranges::for_each(positions | std::views::take(m_mineCount), [&](const auto& pos) {
            m_mineMap[pos.first][pos.second] = MineMap::MINE;
            });

        // Generate mine hints.
        for (auto x = 0; x < m_width; x++)
        {
            for (auto y = 0; y < m_height; y++)
            {
                if (m_mineMap[x][y] == MineMap::MINE)
                {
                    // This is a mine.
                    continue;
                }

                m_mineMap[x][y] = get_adjacent_mine_count({ x, y });
            }
        }
    }

    int MineMap::get_adjacent_mine_count(const Position pos) const noexcept
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

                if (is_valid_position({ x, y }))
                {
                    count += m_mineMap[x][y] == MineMap::MINE ? 1 : 0;
                }
            }
        }

        return count;
    }

    int MineMap::get_adjacent_flags(const Position pos) const noexcept
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

                if (is_valid_position({ x, y }))
                {
                    count += m_gridStatus[x][y] == flagged ? 1 : 0;
                }
            }
        }

        return count;
    }

    bool MineMap::is_valid_position(const Position pos) const noexcept
    {
        return pos.first >= 0 && pos.first < m_width&& pos.second >= 0 && pos.second < m_height;
    }
}