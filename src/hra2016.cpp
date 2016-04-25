#include "hra2016.h"


#include <QtGui>
#include <QApplication>
#include <QMainWindow>

#include "GUI/qfield.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QMainWindow *window = new QMainWindow();
    window->setWindowTitle(QString::fromUtf8("QGridLayout Add Item"));
    window->resize(400, 400);
	
//	Game * game = new Game(8, PlayerType::PERSON, PlayerAlgorithm::ALG_NONE);


//    QBoard *board = new QBoard(window, game);
	QField *field = new QField(window);
	(void)field;

//    window->setCentralWidget(board->getBoard());

    window->show();
    return app.exec();
	return 0;
	
}
