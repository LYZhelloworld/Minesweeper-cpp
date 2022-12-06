#pragma once
#include <vector>

#include "GameStatus.h"
#include "GridStatus.h"

namespace minesweeper
{
    /// <summary>
    /// The position type. The first value is X, and the second is Y.
    /// </summary>
    typedef std::pair<int, int> Position;

    /// <summary>
    /// The type of the value in the mine map.
    /// </summary>
    typedef unsigned int MineMapValue;

    /// <summary>
    /// The game state.
    /// </summary>
    class MineMap
    {
    public:
        /// <summary>
        /// The grid with a mine.
        /// </summary>
        static const MineMapValue MINE = 9;
    
        /// <summary>
        /// The grid with no adjacent mines.
        /// </summary>
        static const MineMapValue EMPTY = 0;

        /// <summary>
        /// Initialises a new instance of the <see cref="MineMap"/> class.
        /// </summary>
        /// <param name="width">The width of the map.</param>
        /// <param name="height">The height of the map.</param>
        /// <param name="mineCount">The count of mines.</param>
        MineMap(const std::size_t width, const std::size_t height, const unsigned int mineCount) throw(std::invalid_argument);

        /// <summary>
        /// Finalises the instance of the <see cref="MineMap"/> class.
        /// </summary>
        ~MineMap() noexcept;

        /// <summary>
        /// Clicks a grid.
        /// </summary>
        /// <param name="pos">The position where to click.</param>
        void Click(const Position pos) throw(std::invalid_argument);

        /// <summary>
        /// Chords a grid.
        /// </summary>
        /// <param name="pos">The position where to chord.</param>
        void Chord(const Position pos) throw(std::invalid_argument);

        /// <summary>
        /// Flags a grid.
        /// </summary>
        /// <param name="pos">The position where to flag.</param>
        void Flag(const Position pos) throw(std::invalid_argument);

        /// <summary>
        /// Gets the game status.
        /// </summary>
        /// <returns>The game status.</returns>
        GameStatus GetGameStatus() const noexcept;

        /// <summary>
        /// Checks if the player wins.
        /// </summary>
        /// <returns>Whether the player wins.</returns>
        bool IsWinning() const noexcept;
    private:
        /// <summary>
        /// The mine map.
        /// </summary>
        std::vector<std::vector<MineMapValue>> m_mineMap;

        /// <summary>
        /// The grid statuses.
        /// </summary>
        std::vector<std::vector<GridStatus>> m_gridStatus;

        /// <summary>
        /// The map width.
        /// </summary>
        std::size_t m_width;

        /// <summary>
        /// The map height.
        /// </summary>
        std::size_t m_height;

        /// <summary>
        /// The number of mines.
        /// </summary>
        unsigned int m_mineCount;

        /// <summary>
        /// The game status.
        /// </summary>
        GameStatus m_gameStatus;

        /// <summary>
        /// Fills the mine map with mines and hints.
        /// </summary>
        /// <param name="clickedPos">The position that the player clicks.</param>
        void GenerateMines(const Position clickedPos) throw(std::invalid_argument);

        /// <summary>
        /// Gets the count of the adjacent mines.
        /// </summary>
        /// <param name="pos">The position.</param>
        /// <returns>The number of adjacent mines.</returns>
        unsigned int GetAdjacentMineCount(const Position pos) const noexcept;

        /// <summary>
        /// Gets the count of the adjacent flags.
        /// </summary>
        /// <param name="pos">The position.</param>
        /// <returns>The number of adjacent flags.</returns>
        unsigned int GetAdjacentFlags(const Position pos) const noexcept;

        /// <summary>
        /// Checks if the position is valid.
        /// </summary>
        /// <param name="pos">The position.</param>
        /// <returns>Whether the position is valid.</returns>
        bool IsValidPosition(const Position pos) const noexcept;
    };
}
