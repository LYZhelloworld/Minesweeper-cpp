#include <algorithm>
#include <stdexcept>

#include "MineMap.h"

namespace minesweeper
{
    constexpr auto POSITION_OUT_OF_RANGE_EXCEPTION = ("The position is out of range.");

    MineMap::MineMap(const std::size_t width, const std::size_t height, const unsigned int mineCount)
        : m_width(width), m_height(height), m_mineCount(mineCount)
    {
        if (mineCount > width * height)
        {
            throw std::invalid_argument("The mine count is greater than the map size.");
        }

        this->m_mineMap.resize(width, std::vector<unsigned int>(height, 0));
        this->m_gridStatus.resize(width, std::vector<GridStatus>(height, GridStatus::Closed));

        this->m_gameStatus = NotStarted;
    }

    MineMap::~MineMap() noexcept
    {
    }

    void MineMap::Click(const Position pos) throw(std::invalid_argument)
    {
        if (this->m_gameStatus == Over)
        {
            return;
        }

        if (!this->IsValidPosition(pos))
        {
            throw std::invalid_argument(POSITION_OUT_OF_RANGE_EXCEPTION);
        }

        if (this->m_gameStatus == NotStarted)
        {
            this->GenerateMines(pos);
            this->m_gameStatus = Started;
        }

        const auto x = pos.first;
        const auto y = pos.second;

        if (this->m_gridStatus[x][y] != Closed)
        {
            return;
        }

        this->m_gridStatus[x][y] = Open;

        if (this->m_mineMap[x][y] == MineMap::MINE)
        {
            this->m_gameStatus = Over;
            return;
        }

        if (this->m_mineMap[x][y] == MineMap::EMPTY)
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

                    if (this->IsValidPosition({ i, j }) && this->m_gridStatus[i][j] == Closed)
                    {
                        this->Click({ i, j });
                    }
                }
            }
        }
    }

    void MineMap::Chord(const Position pos) throw(std::invalid_argument)
    {
        if (this->m_gameStatus == Over || this->m_gameStatus == NotStarted)
        {
            return;
        }

        if (!this->IsValidPosition(pos))
        {
            throw std::invalid_argument(POSITION_OUT_OF_RANGE_EXCEPTION);
        }

        const auto x = pos.first;
        const auto y = pos.second;

        if (this->m_gridStatus[x][y] != Open)
        {
            return;
        }

        if (this->GetAdjacentFlags(pos) == this->m_mineMap[x][y])
        {
            // Open adjacent grids.
            for (auto i = 0; i < this->m_width; i++)
            {
                for (auto j = 0; j < this->m_height; j++)
                {
                    this->Click({ i, j });
                }
            }
        }
    }

    void MineMap::Flag(const Position pos) throw(std::invalid_argument)
    {
        if (this->m_gameStatus == Over)
        {
            return;
        }

        if (!this->IsValidPosition(pos))
        {
            throw std::invalid_argument(POSITION_OUT_OF_RANGE_EXCEPTION);
        }

        const auto x = pos.first;
        const auto y = pos.second;

        if (this->m_gridStatus[x][y] != Closed)
        {
            return;
        }

        this->m_gridStatus[x][y] = this->m_gridStatus[x][y] == Flagged ? Closed : Flagged;
    }

    void MineMap::GenerateMines(const Position clickedPos) throw(std::invalid_argument)
    {
        if (clickedPos.first >= this->m_width || clickedPos.second >= this->m_height)
        {
            throw std::invalid_argument(POSITION_OUT_OF_RANGE_EXCEPTION);
        }

        this->m_gameStatus = Started;

        // Generate usable positions.
        auto usablePositions = std::vector<Position>();
        for (auto x = 0; x < this->m_width; x++)
        {
            for (auto y = 0; y < this->m_height; y++)
            {
                if (x == clickedPos.first && y == clickedPos.second)
                {
                    // Clicked grid will not have mine.
                    continue;
                }

                usablePositions.push_back(Position(x, y));
            }
        }

        // Shuffle all usable positions.
        std::random_shuffle(usablePositions.begin(), usablePositions.end());

        // Pick the positions we need.
        for (auto i = 0; i < this->m_mineCount; i++)
        {
            auto& pos = usablePositions[i];
            this->m_mineMap[pos.first][pos.second] = MineMap::MINE;
        }

        // Generate mine hints.
        for (auto x = 0; x < this->m_width; x++)
        {
            for (auto y = 0; y < this->m_height; y++)
            {
                if (this->m_mineMap[x][y] == MineMap::MINE)
                {
                    // This is a mine.
                    continue;
                }

                this->m_mineMap[x][y] = this->GetAdjacentMineCount({ x, y });
            }
        }
    }
    
    unsigned int MineMap::GetAdjacentMineCount(const Position pos) const noexcept
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

                if (this->IsValidPosition({ x, y }))
                {
                    count += this->m_mineMap[x][y] == MineMap::MINE ? 1 : 0;
                }
            }
        }

        return count;
    }
    
    unsigned int MineMap::GetAdjacentFlags(const Position pos) const noexcept
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

                if (this->IsValidPosition({ x, y }))
                {
                    count += this->m_gridStatus[x][y] == Flagged ? 1 : 0;
                }
            }
        }

        return count;
    }

    bool MineMap::IsValidPosition(const Position pos) const noexcept
    {
        return pos.first >= 0 && pos.first < this->m_width && pos.second >= 0 && pos.second < this->m_height;
    }
}