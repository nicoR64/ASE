#include "GameOfLife.h"
#include "gtest/gtest.h"

TEST(GameOfLifeTest, test_InitializeGameBoard)
{
    int boardHeight{20};
    int boardWidth{20};
    GameOfLife game{boardWidth, boardHeight};

    int expectedDeadCellCounter{boardHeight * boardWidth};
    int deadCellCounter = 0;

    for (int i = 0; i < boardWidth; i++)
    {
        for (int j = 0; j < boardHeight; j++)
        {
            Position cellPosition{i, j};
            if (!game.isAlive(cellPosition))
            {
                deadCellCounter++;
            }
        }
    }

    EXPECT_EQ(expectedDeadCellCounter, deadCellCounter);
};

TEST(GameOfLifeTest, test_SetAliveCellOutsideOfBoard)
{
    int boardHeight{200};
    int boardWidth{200};
    GameOfLife game{boardWidth, boardHeight};
    
    Position outsideCell{205, 205};

    EXPECT_THROW(game.setAlive(outsideCell), std::out_of_range);
}

TEST(GameOfLifeTest, test_SetAliveCell)
{
    int boardHeight{200};
    int boardWidth{200};
    GameOfLife game{boardWidth, boardHeight};
    
    Position aliveCell{24, 67};
    bool alive{true};

    game.setAlive(aliveCell);

    EXPECT_EQ(alive, game.isAlive(aliveCell));

};

TEST(GameOfLifeTest, test_ShouldCellBeAliveUnderpopulated)
{
    int boardHeight{3};
    int boardWidth{3};
    GameOfLife game{boardWidth, boardHeight};

    Position centerPosition{1, 1};
    game.setAlive(centerPosition);

    game.printBoard();
    game.step();
    game.printBoard();

    EXPECT_FALSE(game.isAlive(centerPosition));
}


TEST(GameOfLifeTest, test_ShouldCellBeAliveOverpopulated)
{
    int boardHeight{3};
    int boardWidth{3};
    GameOfLife game{boardWidth, boardHeight};

    Position centerPosition{1, 1};
    game.setAlive(centerPosition);

    Position topLeftPosition{0, 0};
    Position topRightPosition{0, 2};
    Position bottomLeftPosition{2, 0};
    Position bottomRightPosition{2, 2};
    game.setAlive(topLeftPosition);
    game.setAlive(topRightPosition);
    game.setAlive(bottomLeftPosition);
    game.setAlive(bottomRightPosition);

    game.printBoard();
    game.step();
    game.printBoard();

    EXPECT_FALSE(game.isAlive(centerPosition));
}

TEST(GameOfLifeTest, test_ShouldCellBeAliveStable)
{
    int boardHeight{3};
    int boardWidth{3};
    GameOfLife game{boardWidth, boardHeight};

    Position centerPosition{1, 1};
    game.setAlive(centerPosition);

    Position topLeftPosition{0, 0};
    Position topRightPosition{0, 2};
    game.setAlive(topLeftPosition);
    game.setAlive(topRightPosition);

    game.printBoard();
    game.step();
    game.printBoard();

    EXPECT_TRUE(game.isAlive(centerPosition));
}

TEST(GameOfLifeTest, test_ShouldCellBeAliveBirth)
{
    int boardHeight{3};
    int boardWidth{3};
    GameOfLife game{boardWidth, boardHeight};

    Position centerPosition{1, 1};

    Position topLeftPosition{0, 0};
    Position topRightPosition{0, 2};
    Position bottomLeftPosition{2, 0};
    game.setAlive(topLeftPosition);
    game.setAlive(topRightPosition);
    game.setAlive(bottomLeftPosition);

    game.printBoard();
    game.step();
    game.printBoard();

    EXPECT_TRUE(game.isAlive(centerPosition));
}

TEST(GameOfLifeTest, test_ShouldCellBeAliveBirthWithEdges)
{
    int boardHeight{3};
    int boardWidth{3};
    GameOfLife game{boardWidth, boardHeight};

    Position centerPosition{0, 0};

    Position middleRightPosition{1, 0};
    Position bottomLeftPosition{1, 1};
    Position bottomMiddlePosition{0, 1};
    game.setAlive(middleRightPosition);
    game.setAlive(bottomLeftPosition);
    game.setAlive(bottomMiddlePosition);

    game.printBoard();
    game.step();
    game.printBoard();

    EXPECT_TRUE(game.isAlive(centerPosition));
}
