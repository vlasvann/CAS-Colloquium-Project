#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Computer Algebra System");
    resize(800, 600);
}

MainWindow::~MainWindow()
{
}
