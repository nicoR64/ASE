#include "GameOfLife.h"
#include <iostream>

const std::vector<Position> GameOfLife::neighborPositionOffsets{
    {1, 0}, {0, -1}, {1, -1}, {1, 1},
    {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}
};

GameOfLife::GameOfLife(int boardWidth, int boardHeight)
    : boardWidth(boardWidth), boardHeight(boardHeight)
{
    activeBoard = getBlankBoard();
    nextGenerationBufferBoard = getBlankBoard();
}

bool GameOfLife::isAlive(Position position) const
{
    return activeBoard.at(position.x).at(position.y).isAlive;
}

void GameOfLife::setAlive(Position position){
    if(!isInBounds(position)){
        throw std::out_of_range("Given position is outside of board bounds.");
    }

    GameCell alive{true};
    activeBoard[position.x][position.y] = alive;
}

void GameOfLife::setAliveInBuffer(Position position)
{
    GameCell alive{true};
    nextGenerationBufferBoard[position.x][position.y] = alive;
}

void GameOfLife::step()
{
    for (int i{0}; i < boardWidth; i++)
    {
        for (int j{0}; j < boardHeight; j++)
        {
            Position centerCellPosition{i, j};
            if (willCellBeAliveNextGeneration(centerCellPosition))
            {
                setAliveInBuffer(centerCellPosition);
            }
        }
    }

    activeBoard.swap(nextGenerationBufferBoard);
    nextGenerationBufferBoard = getBlankBoard();
}

bool GameOfLife::willCellBeAliveNextGeneration(Position centerCellPosition) const
{
    std::vector<Position> neighbors{getNeighbors(centerCellPosition)};
    int aliveNeighborsCounter{0};
    for (Position neighbor : neighbors)
    {
        if (isInBounds(neighbor) && isAlive(neighbor))
        {
            aliveNeighborsCounter++;
        }
    }

    if (isAlive(centerCellPosition))
    {
        return aliveNeighborsCounter == 2 || aliveNeighborsCounter == 3;
    }
    else
    {
        return aliveNeighborsCounter == 3;
    }
}

bool GameOfLife::isInBounds(Position position) const
{
    return (position.x >= 0 && position.x < boardWidth) && (position.y >= 0 && position.y < boardHeight);
}

std::vector<std::vector<GameCell>> GameOfLife::getBlankBoard() const
{
    GameCell gameCell{false};
    std::vector<GameCell> gameCellRow(boardHeight, gameCell);
    std::vector<std::vector<GameCell>> preparedGameBoard(boardWidth, gameCellRow);
    return preparedGameBoard;
}

std::vector<Position> GameOfLife::getNeighbors(Position centerCellPosition) const
{
    std::vector<Position> neighbors{};
    for (Position neighborOffsetPosition : neighborPositionOffsets)
    {
        Position positionToCheck{neighborOffsetPosition + centerCellPosition};
        if (isInBounds(positionToCheck))
        {
            neighbors.push_back(positionToCheck);
        }
    }
    return neighbors;
}

void GameOfLife::printBoard() const
{
    for (int i{0}; i < boardWidth; i++)
    {
        for (int j{0}; j < boardHeight; j++)
        {
            if(activeBoard.at(i).at(j).isAlive){
                std::cout << "X";
            } else {
                std::cout << "_";
            }
        }
        std::cout << std::endl;
    }
    const int boardSeparatorLength = 40;
    std::cout << std::string(boardSeparatorLength, '-') << std::endl;
}
