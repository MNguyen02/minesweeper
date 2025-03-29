#include "Gameboard.h"
#include <QApplication>

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

void Gameboard::handleButtonClick()
{
    if (gameOver)
        return;

    QPushButton *button = qobject_cast<QPushButton *>(sender());
    int row = button->property("row").toInt();
    int col = button->property("col").toInt();

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

void Gameboard::handleButtonRightClick()
{
    if (gameOver)
        return;

    QPushButton *button = qobject_cast<QPushButton *>(sender());
    int row = button->property("row").toInt();
    int col = button->property("col").toInt();

    if (!board[row][col].getIsRevealed())
    {
        if (board[row][col].getIsFlagged())
        {
            board[row][col].setFlagged(false);
            questionSpace(row, col);
        }
        else if (board[row][col].getIsQuestion())
        {
            board[row][col].setIsQuestion(false);
            board[row][col].setFlagged(false);
        }
        else
        {
            flagSpace(row, col);
        }
        updateButton(row, col);
    }
}

void Gameboard::handleGameOver(bool isWin)
{
    gameOver = true;
    QString message = isWin ? "Congratulations! You won!" : "Game Over! You hit a mine!";
    QMessageBox msgBox;
    msgBox.setWindowTitle(isWin ? "Victory!" : "Game Over");
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Reset | QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Reset);

    int ret = msgBox.exec();

    if (ret == QMessageBox::Reset)
    {
        resetBoard();
    }
    else
    {
        QApplication::quit();
    }
}

void Gameboard::updateButton(int row, int col)
{
    QPushButton *button = buttons[row][col];
    Space &space = board[row][col];

    if (space.getIsRevealed())
    {
        button->setEnabled(false);
        if (isMine(row, col))
        {
            button->setText("💣");
        }
        else
        {
            int adjacentMines = countAdjacentMines(row, col);
            button->setText("");
            if (adjacentMines > 0)
            {
                button->setText(QString::number(adjacentMines));
                // Set different colors for different numbers
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
        button->setText("🚩");
    }
    else if (space.getIsQuestion())
    {
        button->setText("❓");
    }
    else
    {
        button->setText("");
    }
}

void Gameboard::checkWin()
{
    bool allNonMinesRevealed = true;
    for (int row = 0; row < HEIGHT; ++row)
    {
        for (int col = 0; col < WIDTH; ++col)
        {
            if (!isMine(row, col) && !board[row][col].getIsRevealed())
            {
                allNonMinesRevealed = false;
                break;
            }
        }
        if (!allNonMinesRevealed)
            break;
    }

    if (allNonMinesRevealed)
    {
        gameOver = true;
        handleGameOver(true);
    }
}

void Gameboard::placeMines()
{
    std::srand(std::time(0)); // Use the time as a random seed
    mineMap.clear();          // Clear the minemap.

    int minesPlaced = 0;
    while (minesPlaced < MINES)
    {
        int row = std::rand() % HEIGHT;
        int col = std::rand() % WIDTH;

        // Check if the row is already in the minemap, or if the position already contains a mine.
        if (mineMap.find(row) == mineMap.end() || mineMap[row].find(col) == mineMap[row].end())
        {
            mineMap[row].insert(col);      // Insert a mine if there isn't a mine already.
            board[row][col].setMine(true); // Mark the mine on the board.
            ++minesPlaced;                 // Increment the counter.
        }
    }
}

void Gameboard::calculateAdjacency()
{
    for (int row = 0; row < HEIGHT; ++row)
    {
        for (int col = 0; col < WIDTH; ++col)
        {
            // if the current space is not a mine, calculate adjacent mines.
            if (!board[row][col].getIsMine())
            {
                int count = countAdjacentMines(row, col);
                board[row][col].setAdjacentMines(count);
            }
        }
    }
}

int Gameboard::countAdjacentMines(int row, int col)
{
    int count = 0;

    // Using relative offsets, we can check positions around the space.
    for (int dr = -1; dr <= 1; ++dr)
    {
        for (int dc = -1; dc <= 1; ++dc)
        {
            // Skip the current cell itself, doesn't contribute to the count.
            if (dr == 0 && dc == 0)
                continue;

            // Using the relative offset, we can determine the index of the position to check.
            int newRow = row + dr;
            int newCol = col + dc;

            // Check if the neighbor is within bounds and contains a mine
            if (newRow >= 0 && newRow < HEIGHT && newCol >= 0 && newCol < WIDTH)
            {
                // Check if the position is a mine.
                if (mineMap.find(newRow) != mineMap.end() && mineMap[newRow].find(newCol) != mineMap[newRow].end())
                {
                    count++;
                }
            }
        }
    }
    return count;
}

void Gameboard::revealSpace(int row, int col)
{
    // Check that the position is within bounds.
    if (row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH)
        return;

    // If already revealed, do nothing
    if (board[row][col].getIsRevealed())
    {
        return;
    }

    // If flagged, you must remove the flag, and then reveal it.
    if (board[row][col].getIsFlagged())
    {
        board[row][col].setFlagged(false);
    }

    // Reveal the current space.
    board[row][col].setRevealed(true);
    updateButton(row, col); // Update the button's appearance

    // If it's a mine, stop here
    if (isMine(row, col))
    {
        return;
    }

    // If there are no adjacent mines, recursively reveal neighbours
    if (countAdjacentMines(row, col) == 0)
    {
        for (int dr = -1; dr <= 1; ++dr)
        {
            for (int dc = -1; dc <= 1; ++dc)
            {
                if (dr == 0 && dc == 0)
                    continue;                    // Skip the current cell
                revealSpace(row + dr, col + dc); // Recursively reveal neighbouring cells
            }
        }
    }
}

void Gameboard::flagSpace(int row, int col)
{
    if (board[row][col].getIsRevealed())
        return; // Can't flag revealed spaces

    bool isCurrentlyFlagged = board[row][col].getIsFlagged();
    board[row][col].setFlagged(!isCurrentlyFlagged); // Toggle the flag
}

void Gameboard::questionSpace(int row, int col)
{
    if (board[row][col].getIsRevealed())
        return; // Can't question revealed spaces

    bool isCurrentlyQuestion = board[row][col].getIsQuestion();
    board[row][col].setIsQuestion(!isCurrentlyQuestion); // Toggle the question
}

bool Gameboard::isMine(int row, int col)
{
    return mineMap.find(row) != mineMap.end() && mineMap[row].find(col) != mineMap[row].end();
}
