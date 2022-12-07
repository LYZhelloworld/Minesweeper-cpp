#include "pch.h"
#include "CppUnitTest.h"
#include "../Minesweeper/MineMap.h"
#include "../Minesweeper/MineMap.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Minesweeper::Test
{
    TEST_CLASS(MineMapTest)
    {
    public:
        TEST_METHOD(TestConstructor)
        {
            auto mineMap = Minesweeper::MineMap(10, 10, 10);
            
            auto map = mineMap.GetMineMap();
            Assert::AreEqual((std::size_t)10, map.size());
            Assert::AreEqual((std::size_t)10, map[0].size());
            Assert::IsFalse(mineMap.IsWinning());
        }

        TEST_METHOD(TestConstructorWithException)
        {
            auto func = []() { auto mineMap = Minesweeper::MineMap(10, 10, 101); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        TEST_METHOD(TestClick)
        {
            auto mineMap = Minesweeper::MineMap(5, 5, 10);
            mineMap.Click(Minesweeper::Position(0, 0));

            auto map = mineMap.GetMineMap();
            Assert::AreNotEqual(Minesweeper::MineMap::MINE, map[0][0]);

            auto grids = mineMap.GetGridStatus();
            Assert::IsTrue(Open == grids[0][0]);

            Assert::IsFalse(Over == mineMap.GetGameStatus());
            Assert::IsFalse(mineMap.IsWinning());
        }

        TEST_METHOD(TestClickWithOneSpace)
        {
            auto mineMap = Minesweeper::MineMap(5, 5, 24);
            mineMap.Click(Minesweeper::Position(0, 0));
            
            auto map = mineMap.GetMineMap();
            Assert::AreNotEqual(Minesweeper::MineMap::MINE, map[0][0]);
            
            auto grids = mineMap.GetGridStatus();
            Assert::IsTrue(Open == grids[0][0]);
            
            Assert::IsTrue(Over == mineMap.GetGameStatus());
            Assert::IsTrue(mineMap.IsWinning());
        }

        TEST_METHOD(TestClickWithAdjacentSpace)
        {
            auto mineMap = Minesweeper::MineMap(5, 5, 1);
            mineMap.Click(Minesweeper::Position(0, 0));

            auto map = mineMap.GetMineMap();
            auto grids = mineMap.GetGridStatus();

            for (auto x = 0; x < 5; x++)
            {
                for (auto y = 0; y < 5; y++)
                {
                    if (x == 0 && y == 0)
                    {
                        Assert::AreNotEqual(Minesweeper::MineMap::MINE, map[x][y]);
                        Assert::IsTrue(Open == grids[x][y]);
                    }
                    else
                    {
                        Assert::AreEqual(Minesweeper::MineMap::MINE, map[x][y]);
                        Assert::IsTrue(Closed == grids[x][y]);
                    }
                }
            }

            Assert::IsTrue(Over == mineMap.GetGameStatus());
            Assert::IsTrue(mineMap.IsWinning());
        }
    };
}