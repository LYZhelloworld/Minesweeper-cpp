#include "CppUnitTest.h"
#include "../Minesweeper/MineMap.h"
#include "../Minesweeper/MineMap.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Minesweeper::MineMap::Test
{
    typedef Minesweeper::MineMap::Position Position;
    typedef Minesweeper::MineMap::MineMap MineMap;

    TEST_CLASS(MineMapTest)
    {
    public:
        TEST_METHOD(TestConstructor)
        {
            auto mineMap = MineMap(10, 10, 10);
            
            auto map = mineMap.GetMineMap();
            Assert::AreEqual((std::size_t)10, map.size());
            Assert::AreEqual((std::size_t)10, map[0].size());
            Assert::IsFalse(mineMap.IsWinning());
        }

        TEST_METHOD(TestConstructorWithException)
        {
            auto func = []() { auto mineMap = MineMap(10, 10, 101); };
            Assert::ExpectException<TooManyMinesException>(func);
        }

        TEST_METHOD(TestClick)
        {
            auto mineMap = MineMap(5, 5, 10);
            mineMap.Click(Position(0, 0));

            auto map = mineMap.GetMineMap();
            Assert::AreNotEqual(MineMap::MINE, map[0][0]);

            auto grids = mineMap.GetGridStatus();
            Assert::IsTrue(Open == grids[0][0]);

            Assert::IsFalse(Over == mineMap.GetGameStatus());
            Assert::IsFalse(mineMap.IsWinning());
        }

        TEST_METHOD(TestClickWithOneSpace)
        {
            auto mineMap = MineMap(5, 5, 24);
            mineMap.Click(Position(0, 0));
            
            auto map = mineMap.GetMineMap();
            Assert::AreNotEqual(MineMap::MINE, map[0][0]);
            
            auto grids = mineMap.GetGridStatus();
            Assert::IsTrue(Open == grids[0][0]);
            
            Assert::IsTrue(Over == mineMap.GetGameStatus());
            Assert::IsTrue(mineMap.IsWinning());
        }

        TEST_METHOD(TestClickWithAdjacentSpace)
        {
            auto mineMap = MineMap(5, 5, 0);
            mineMap.Click(Position(0, 0));

            auto map = mineMap.GetMineMap();
            auto grids = mineMap.GetGridStatus();

            Assert::IsTrue(Over == mineMap.GetGameStatus());
            Assert::IsTrue(mineMap.IsWinning());
        }
    };
}