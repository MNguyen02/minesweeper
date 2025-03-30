/*
 * Author: Martin Nguyen
 * Description: Gameboard class for Minesweeper game implementation using Qt
 * Date: 02/06/2025
 */


#ifndef GAMEBOARD_H
#define GAMEBOARD_H

// System/standard libraries
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <cstdlib>
#include <ctime>

// Qt libraries
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

#include "Space.h"

class Gameboard : public QWidget {
    Q_OBJECT

public:
    // Constructor and destructor
    Gameboard(QWidget* parent = nullptr);
    virtual ~Gameboard();

    // Public functions
    void resetBoard();
    bool isMine(int row, int col);
    Space& getSpace(int row, int col);
    void revealSpace(int row, int col);
    void flagSpace(int row, int col);
    void questionSpace(int row, int col);

private:
    // Constant declarations
    static constexpr int WIDTH = 30;
    static constexpr int HEIGHT = 16;
    static constexpr int MINES = 20;

    // Instance variables
    std::vector<std::vector<Space>> board;
    std::unordered_map<int, std::unordered_set<int>> mineMap; // Using a dictionary-like implementation to store bomb locations.
    QGridLayout* gridLayout;
    std::vector<std::vector<QPushButton*>> buttons;
    bool gameOver;
    bool firstClick;

    // Private functions
    void createButtons();
    void placeMines();
    void calculateAdjacency();
    int countAdjacentMines(int row, int col);
    void updateButton(int row, int col);
    void checkWin();
    void handleButtonClick();
    void handleButtonRightClick();
    void handleGameOver(bool isWin);


};

#endif // GAMEBOARD_H
