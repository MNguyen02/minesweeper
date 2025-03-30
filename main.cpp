/*
 * Author: Martin Nguyen
 * Description: Main file for Minesweeper game implementation using Qt
 * Date: 02/06/2025
 */


#include "mainwindow.h"
#include <QApplication>

/*
 * Function: main
 * Description: Main function for Minesweeper game implementation using Qt
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
