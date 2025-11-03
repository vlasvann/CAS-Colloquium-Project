#include <QApplication>
#include <QMainWindow>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QMainWindow window;
    QLabel *label = new QLabel("Computer Algebra System");
    label->setAlignment(Qt::AlignCenter);
    
    window.setCentralWidget(label);
    window.setWindowTitle("Computer Algebra System");
    window.resize(400, 300);
    window.show();
    
    return app.exec();
}
