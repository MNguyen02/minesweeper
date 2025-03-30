/*
 * Author: Martin Nguyen
 * Description: MainWindow class for Minesweeper game implementation using Qt
 * Date: 02/06/2025
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt libraries
#include <QMainWindow>

// Gameboard class
#include "Gameboard.h"

// Qt namespace
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor and destructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // Instance variables
    Ui::MainWindow *ui;
    Gameboard* gameBoard;
};
#endif // MAINWINDOW_H
