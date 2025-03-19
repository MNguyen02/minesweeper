#include "GameBoard.h"

GameBoard::GameBoard() {
    board.resize(HEIGHT, std::vector<Space>(WIDTH));
    resetBoard;
}

void GameBoard::resetBoard() {
    placeMines();
    calculateAdjacency();
}

void GameBoard::placeMines() {
    int minesPlaced = 0;
    while minesPlaced < 99 {
        int row = std::rand() % HEIGHT;
        int col = std::rand() % WIDTH;

        if(mineMap.find(row) != mineMap.end && mineMap[row].find(col) != mineMap.end) {
            mineMap.insert(row)
        }
    }
}