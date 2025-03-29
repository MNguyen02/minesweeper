#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Space.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <cstdlib>
#include <ctime>

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

class Gameboard : public QWidget {
    Q_OBJECT

private:
    static constexpr int WIDTH = 30;
    static constexpr int HEIGHT = 16;
    static constexpr int MINES = 20;

    std::vector<std::vector<Space>> board;
    std::unordered_map<int, std::unordered_set<int>> mineMap; // Using a dictionary-like implementation to store bomb locations.
    QGridLayout* gridLayout;
    std::vector<std::vector<QPushButton*>> buttons;
    bool gameOver;
    bool firstClick;

    void placeMines();
    void calculateAdjacency();
    int countAdjacentMines(int row, int col);
    void createButtons();
    void updateButton(int row, int col);
    void checkWin();
    void handleButtonClick();
    void handleButtonRightClick();

    void handleGameOver(bool isWin);

public:
    Gameboard(QWidget* parent = nullptr);
    void resetBoard();
    bool isMine(int row, int col);
    Space& getSpace(int row, int col);
    void revealSpace(int row, int col);
    void flagSpace(int row, int col);
    void questionSpace(int row, int col);
};

#endif // GAMEBOARD_H
