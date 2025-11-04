#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("C:/Users/tomil/Downloads/icon1.jpg"));
    MainWindow window;
    window.show();

    return app.exec();
}
