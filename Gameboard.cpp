/*
 * Author: Martin Nguyen
 * Description: Implementation of Gameboard class for Minesweeper game
 * Date: 02/06/2025
 */

#include "Gameboard.h"
#include <QApplication>

/*
 * Constructor: Gameboard
 * Description: Initializes a new gameboard with default values
 * Parameters: parent - Parent widget (managed by Qt)
 */
Gameboard::Gameboard(QWidget *parent) : QWidget(parent), gameOver(false), firstClick(true)
{
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    setLayout(gridLayout);

    // Initialize the button grid
    buttons.resize(HEIGHT, std::vector<QPushButton *>(WIDTH));
    createButtons();

    resetBoard();
}

/*
 * Destructor: Gameboard
 * Description: Destroys the gameboard object (managed by Qt)
 */
Gameboard::~Gameboard()
{
}

/*
 * Function: resetBoard
 * Description: Resets the gameboard to its initial state
 */
void Gameboard::resetBoard()
{
    board.clear();
    board.resize(HEIGHT, std::vector<Space>(WIDTH));
    mineMap.clear();
    gameOver = false;
    firstClick = true;

    // Reset all buttons
    for (int row = 0; row < HEIGHT; ++row)
    {
        for (int col = 0; col < WIDTH; ++col)
        {
            buttons[row][col]->setText("");
            buttons[row][col]->setEnabled(true);
            buttons[row][col]->setStyleSheet("");
        }
    }
}

/*
 * Function: isMine
 * Description: Checks if a square has a mine
 * Parameters: row - The row of the square, col - The column of the square
 * Returns: true if the square has a mine, false otherwise
 */
bool Gameboard::isMine(int row, int col)
{
    return mineMap.find(row) != mineMap.end() &&
           mineMap[row].find(col) != mineMap[row].end();
}

/*
 * Function: getSpace
 * Description: Gets a reference to a space on the board
 * Parameters: row - The row of the square, col - The column of the square
 * Returns: A reference to the space at the given row and column
 */
Space &Gameboard::getSpace(int row, int col)
{
    return board[row][col];
}

/*
 * Function: revealSpace
 * Description: Reveals a space on the board, and recursively reveals all adjacent spaces if the space has no adjacent mines (flood fill)
 * Parameters: row - The row of the square, col - The column of the square
 */
void Gameboard::revealSpace(int row, int col)
{
    // Stay within the boundaries of the board
    if (row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH)
        return;

    // If space is already revealed, do nothing
    if (board[row][col].getIsRevealed())
        return;

    // Remove any flag if it's there
    if (board[row][col].getIsFlagged())
        board[row][col].setFlagged(false);

    // Show what's under this square
    board[row][col].setRevealed(true);
    updateButton(row, col);

    // If space is a mine, stop here
    if (isMine(row, col))
        return;

    // If no adjacent mines, reveal all adjacent spaces (flood fill)
    if (countAdjacentMines(row, col) == 0)
    {
        for (int dr = -1; dr <= 1; ++dr)
        {
            for (int dc = -1; dc <= 1; ++dc)
            {
                if (dr == 0 && dc == 0)
                    continue;                    // skip current square
                revealSpace(row + dr, col + dc); // reveal neighbors recursively
            }
        }
    }
}

/*
 * Function: flagSpace
 * Description: Puts a flag on a square (or removes it)
 * Parameters: row - The row of the square, col - The column of the square
 */
void Gameboard::flagSpace(int row, int col)
{
    if (board[row][col].getIsRevealed())
        return; // can't flag revealed squares!

    // Toggle the flag (if it's there, remove it; if it's not, add it)
    bool isCurrentlyFlagged = board[row][col].getIsFlagged();
    board[row][col].setFlagged(!isCurrentlyFlagged);
}

/*
 * Function: questionSpace
 * Description: Puts a question mark on a square (or removes it)
 * Parameters: row - The row of the square, col - The column of the square
 */
void Gameboard::questionSpace(int row, int col)
{
    if (board[row][col].getIsRevealed())
        return; // can't question revealed squares!

    // Toggle the question mark
    bool isCurrentlyQuestion = board[row][col].getIsQuestion();
    board[row][col].setIsQuestion(!isCurrentlyQuestion);
}

/*
 * Function: createButtons
 * Description: Creates the buttons for the gameboard
 */
void Gameboard::createButtons()
{
    for (int row = 0; row < HEIGHT; ++row)
    {
        for (int col = 0; col < WIDTH; ++col)
        {
            QPushButton *button = new QPushButton(this);
            button->setFixedSize(30, 30);
            button->setProperty("row", row);
            button->setProperty("col", col);

            connect(button, &QPushButton::clicked, this, &Gameboard::handleButtonClick);
            connect(button, &QPushButton::customContextMenuRequested, this, &Gameboard::handleButtonRightClick);
            button->setContextMenuPolicy(Qt::CustomContextMenu);

            gridLayout->addWidget(button, row, col);
            buttons[row][col] = button;
        }
    }
}

/*
 * Function: placeMines
 * Description: Places all the mines randomly on the board, only after the first click
 */
void Gameboard::placeMines()
{
    std::srand(std::time(0)); // Use a random seed by using the current time
    mineMap.clear();          // Reset the mine map

    int minesPlaced = 0;
    while (minesPlaced < MINES)
    {
        // Pick random spots for mines
        int row = std::rand() % HEIGHT;
        int col = std::rand() % WIDTH;

        // Only place a mine if there isn't one there already
        if (mineMap.find(row) == mineMap.end() || mineMap[row].find(col) == mineMap[row].end())
        {
            mineMap[row].insert(col); // Insert the mine into the mine map
            board[row][col].setMine(true);
            ++minesPlaced;
        }
    }
}

/*
 * Function: calculateAdjacency
 * Description: Calculates the number of adjacent mines for each square on the board
 */
void Gameboard::calculateAdjacency()
{
    for (int row = 0; row < HEIGHT; ++row)
    {
        for (int col = 0; col < WIDTH; ++col)
        {
            // Skip mines - they don't need numbers!
            if (!board[row][col].getIsMine())
            {
                int count = countAdjacentMines(row, col);
                board[row][col].setAdjacentMines(count);
            }
        }
    }
}

/*
 * Function: countAdjacentMines
 * Description: Counts the number of adjacent mines for a given square
 * Parameters: row - The row of the square, col - The column of the square
 * Returns: The number of adjacent mines
 */
int Gameboard::countAdjacentMines(int row, int col)
{
    int count = 0;
    // Check all 8 squares around this one
    for (int dr = -1; dr <= 1; ++dr)
    {
        for (int dc = -1; dc <= 1; ++dc)
        {
            if (dr == 0 && dc == 0)
                continue; // skip the square itself

            // Look at each neighbor
            int newRow = row + dr;
            int newCol = col + dc;

            // Make sure we're still on the board
            if (newRow >= 0 && newRow < HEIGHT && newCol >= 0 && newCol < WIDTH)
            {
                // If there's a mine there, count it!
                if (mineMap.find(newRow) != mineMap.end() &&
                    mineMap[newRow].find(newCol) != mineMap[newRow].end())
                {
                    count++;
                }
            }
        }
    }
    return count;
}

/*
 * Function: updateButton
 * Description: Updates how a button looks based on what it is (number, mine, flag, etc)
 * Parameters: row - The row of the square, col - The column of the square
 */
void Gameboard::updateButton(int row, int col)
{
    QPushButton *button = buttons[row][col];
    Space &space = board[row][col];

    if (space.getIsRevealed())
    {
        button->setEnabled(false); // can't click revealed squares
        if (isMine(row, col))
        {
            button->setText("💣"); // show the mine if mine is clicked.
        }
        else
        {
            int adjacentMines = countAdjacentMines(row, col);
            button->setText(""); // Blank the square by default.
            if (adjacentMines > 0)
            {
                button->setText(QString::number(adjacentMines));
                // Make each number a different color, shows danger level of the square.
                QString color;
                switch (adjacentMines)
                {
                case 1:
                    color = "blue";
                    break;
                case 2:
                    color = "green";
                    break;
                case 3:
                    color = "red";
                    break;
                case 4:
                    color = "darkblue";
                    break;
                case 5:
                    color = "darkred";
                    break;
                case 6:
                    color = "teal";
                    break;
                case 7:
                    color = "black";
                    break;
                case 8:
                    color = "gray";
                    break;
                }
                button->setStyleSheet("color: " + color + ";");
            }
        }
    }
    else if (space.getIsFlagged())
    {
        button->setText("🚩"); // show flag
    }
    else if (space.getIsQuestion())
    {
        button->setText("❓"); // show question mark
    }
    else
    {
        button->setText(""); // Blank the square by default.
    }
}

/*
 * Function: checkWin
 * Description: Checks if game is won- we win if all non-mine squares are revealed
 */
void Gameboard::checkWin()
{
    bool allNonMinesRevealed = true;
    for (int row = 0; row < HEIGHT; ++row)
    {
        for (int col = 0; col < WIDTH; ++col)
        {
            // If safe square is still unrevealed, we haven't won yet
            if (!isMine(row, col) && !board[row][col].getIsRevealed())
            {
                allNonMinesRevealed = false;
                break;
            }
        }
        if (!allNonMinesRevealed)
            break;
    }

    // If everything except mines is revealed, game is won.
    if (allNonMinesRevealed)
    {
        gameOver = true;
        handleGameOver(true);
    }
}

/*
 * Function: handleButtonClick
 * Description: Handles the click event for a button
 */
void Gameboard::handleButtonClick()
{
    if (gameOver)
        return;

    QPushButton *button = qobject_cast<QPushButton *>(sender());
    int row = button->property("row").toInt();
    int col = button->property("col").toInt();

    // If first click, place mines and calculate adjacency
    if (firstClick)
    {
        placeMines();
        calculateAdjacency();
        firstClick = false;
    }

    if (isMine(row, col))
    {
        gameOver = true;
        // Reveal all mines
        for (int r = 0; r < HEIGHT; ++r)
        {
            for (int c = 0; c < WIDTH; ++c)
            {
                if (isMine(r, c))
                {
                    buttons[r][c]->setText("💣");
                }
            }
        }

        handleGameOver(false);
    }
    else
    {
        revealSpace(row, col);
        checkWin();
    }
}

/*
 * Function: handleButtonRightClick
 * Description: Handles the right-click event for a button
 */
void Gameboard::handleButtonRightClick()
{
    if (gameOver)
        return; // can't do anything if game's done

    // Figure out which button got right-clicked
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    int row = button->property("row").toInt();
    int col = button->property("col").toInt();

    // Only work with unrevealed squares (can't flag a number!)
    if (!board[row][col].getIsRevealed())
    {
        // This cycles through: empty -> flag -> question -> empty
        if (board[row][col].getIsFlagged())
        {
            board[row][col].setFlagged(false);
            questionSpace(row, col); // make it a question mark
        }
        else if (board[row][col].getIsQuestion())
        {
            board[row][col].setIsQuestion(false);
            board[row][col].setFlagged(false); // back to empty
        }
        else
        {
            flagSpace(row, col); // make it a flag
        }
        updateButton(row, col); // show the changes
    }
}

/*
 * Function: handleGameOver
 * Description: Shows the game over screen - works for both winning and losing
 */
void Gameboard::handleGameOver(bool isWin)
{
    gameOver = true;
    // Different message for winning vs losing
    QString message = isWin ? "Congratulations! You won!" : "Game Over! You hit a mine!";
    QMessageBox msgBox;
    msgBox.setWindowTitle(isWin ? "Victory!" : "Game Over");
    msgBox.setText(message);
    // Give options to reset or quit
    msgBox.setStandardButtons(QMessageBox::Reset | QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Reset);

    int ret = msgBox.exec();

    if (ret == QMessageBox::Reset)
    {
        resetBoard(); // they want to play again.
    }
    else
    {
        QApplication::quit(); // they're done playing, quit the game.
    }
}
