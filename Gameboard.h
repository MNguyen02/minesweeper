#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Space.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <cstdlib>
#include <ctime>

class GameBoard {
    private:
        static constexpr int WIDTH = 30;
        static constexpr int HEIGHT = 16;
        static constexpr int MINES = 99;

        std::vector<std::vector<Space>> board;
        std::unordered_map<int, std::unordered_set<int>> mineMap; // Using a dictionary-like implementation to store bomb locations.


        void placeMines();
        void calculateAdjacency();
        int countAdjacentMines(int row, int col);

    public:
        GameBoard();
        void resetBoard();
        bool isMine(int row, int col);
        Space& getSpace(int row, int col);
};
#endif