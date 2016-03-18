#include "hra2016.h"
#include "logic/board.h"

#include <QtGui>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char* argv[])
{
	Game * game = new Game(8, Player::PERSON, Player::ALG_NONE);
    QApplication app(argc, argv);
    QMainWindow *window = new QMainWindow();
    window->setWindowTitle(QString::fromUtf8("QGridLayout Add Item"));
    window->resize(400, 400);

//    QBoard *board = new QBoard(window);
//
//    window->setCentralWidget(board->getBoard());

    window->show();
    return app.exec();
	return 0;
	
}
