#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

MainWindow::~MainWindow()
{
    delete ui;
}
