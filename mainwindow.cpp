/*
 * Author: Martin Nguyen
 * Description: MainWindow class for Minesweeper game implementation using Qt
 * Date: 02/06/2025
 */


#include "mainwindow.h"
#include "./ui_mainwindow.h"

/*
 * Constructor: MainWindow
 * Description: Constructor for MainWindow class
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Create and set up the game board
    gameBoard = new Gameboard(this);
    setCentralWidget(gameBoard);
    
    // Set window title and size
    setWindowTitle("Minesweeper");
    setFixedSize(900, 480); // 30x16 grid with 30x30 buttons
}

/*
* Destructor: MainWindow
* Description: Destructor for MainWindow class
*/
MainWindow::~MainWindow()
{
    delete ui;
}
