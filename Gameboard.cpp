#include "Gameboard.h"

Gameboard::Gameboard() {
    board.resize(HEIGHT, std::vector<Space>(WIDTH));
    resetBoard();
}

void Gameboard::resetBoard() {
    placeMines();
    calculateAdjacency();
}

void Gameboard::placeMines() {
    std::srand(std::time(0)); // Use the time as a random seed
    mineMap.clear(); // Clear the minemap.

    int minesPlaced = 0;
    while (minesPlaced < MINES) {
        int row = std::rand() % HEIGHT;
        int col = std::rand() % WIDTH;
        
        // Check if the row is already in the minemap, or if the position already contains a mine.
        if (mineMap.find(row) == mineMap.end() || mineMap[row].find(col) == mineMap[row].end()) { 
            mineMap[row].insert(col); // Insert a mine if there isn't a mine already.
            board[row][col].setMine(true); // Mark the mine on the board.
            ++minesPlaced; // Increment the counter.
        }
    }
}

void Gameboard::calculateAdjacency() {
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            // if the current space is not a mine, calculate adjacent mines.
            if (!board[row][col].getIsMine()) {
                int count = countAdjacentMines(row, col);
                board[row][col].setAdjacentMines(count);
            }
        }
    }
}

int Gameboard::countAdjacentMines(int row, int col) {
    int count = 0;

    // Using relative offsets, we can check positions around the space.
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            // Skip the current cell itself, doesn't contribute to the count.
            if (dr == 0 && dc == 0) continue;
            
            // Using the relative offset, we can determine the index of the position to check.
            int newRow = row + dr;
            int newCol = col + dc;

            // Check if the neighbor is within bounds and contains a mine
            if (newRow >= 0 && newRow < HEIGHT && newCol >= 0 && newCol < WIDTH) {
                // Check if the position is a mine.
                if (mineMap.find(newRow) != mineMap.end() && mineMap[newRow].find(newCol) != mineMap[newRow].end()) {
                    count++;
                }
            }
        }
    }
    return count;
}

void Gameboard::revealSpace(int row, int col) {
    // Check that the position is within bounds.
    if (row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH) return;

    // If already revealed, do nothing
    if (board[row][col].getIsRevealed()) {
        return;
    }

    // If flagged, you must remove the flag, and then reveal it.
    if (board[row][col].getIsFlagged()) {
        board[row][col].setFlagged(false);
        buttons[row][col]->setText("");  // Clear the flag visually
        buttons[row][col]->setStyleSheet("background-color: lightgray;");
    }
}

bool Gameboard::isMine(int row, int col) {
    return mineMap.find(row) != mineMap.end() && mineMap[row].find(col) != mineMap[row].end();
}




