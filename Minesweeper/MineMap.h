#pragma once
#include <vector>

#include "GameStatus.h"
#include "GridStatus.h"

namespace Minesweeper::MineMap
{
    /// <summary>
    /// The position type. The first value is X, and the second is Y.
    /// </summary>
    typedef std::pair<int, int> Position;

    /// <summary>
    /// The type of the value in the mine map.
    /// </summary>
    typedef int MineMapValue;

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
        MineMap(const std::size_t width, const std::size_t height, const int mineCount);

        /// <summary>
        /// Gets mine map.
        /// </summary>
        /// <returns>The mine map.</returns>
        const std::vector<std::vector<MineMapValue>> get_minemap() const;

        /// <summary>
        /// Gets grid statuses.
        /// </summary>
        /// <returns>The grid statuses.</returns>
        const std::vector<std::vector<GridStatus>> get_grid_status() const;

        /// <summary>
        /// Clicks a grid.
        /// </summary>
        /// <param name="pos">The position where to click.</param>
        void click(const Position pos);

        /// <summary>
        /// Chords a grid.
        /// </summary>
        /// <param name="pos">The position where to chord.</param>
        void chord(const Position pos);

        /// <summary>
        /// Flags a grid.
        /// </summary>
        /// <param name="pos">The position where to flag.</param>
        void flag(const Position pos);

        /// <summary>
        /// Gets the game status.
        /// </summary>
        /// <returns>The game status.</returns>
        const GameStatus get_game_status() const noexcept;

        /// <summary>
        /// Checks if the player wins.
        /// </summary>
        /// <returns>Whether the player wins.</returns>
        bool is_winning() const noexcept;
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
        int m_mineCount;

        /// <summary>
        /// The game status.
        /// </summary>
        GameStatus m_gameStatus;

        /// <summary>
        /// Fills the mine map with mines and hints.
        /// </summary>
        /// <param name="clickedPos">The position that the player clicks.</param>
        void generate_mines(const Position clickedPos);

        /// <summary>
        /// Gets the count of the adjacent mines.
        /// </summary>
        /// <param name="pos">The position.</param>
        /// <returns>The number of adjacent mines.</returns>
        int get_adjacent_mine_count(const Position pos) const noexcept;

        /// <summary>
        /// Gets the count of the adjacent flags.
        /// </summary>
        /// <param name="pos">The position.</param>
        /// <returns>The number of adjacent flags.</returns>
        int get_adjacent_flags(const Position pos) const noexcept;

        /// <summary>
        /// Checks if the position is valid.
        /// </summary>
        /// <param name="pos">The position.</param>
        /// <returns>Whether the position is valid.</returns>
        bool is_valid_position(const Position pos) const noexcept;
    };

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
        TooManyMinesException() noexcept
            : std::exception("The mine count is greater than the map size.")
        {}
    };

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
        PositionOutOfRangeException() noexcept
            : std::exception("The position is out of range.")
        {}
    };
}
