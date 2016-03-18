#include <board.h>

#include <QtGui>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QMainWindow *window = new QMainWindow();
    window->setWindowTitle(QString::fromUtf8("QGridLayout Add Item"));
    window->resize(400, 400);

    QBoard *board = new QBoard(window);

    window->setCentralWidget(board->getBoard());

    window->show();
    return app.exec();
}
