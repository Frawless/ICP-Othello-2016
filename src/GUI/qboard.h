#ifndef BOARD_H
#define BOARD_H

#include <QGridLayout>

class QBoard
{
public:
    QBoard(QWidget *parent, Game *game);
    QWidget *getBoard() {return board;};

private:
    QWidget *board;
    QGridLayout *layout;
	Game *game;
};

#endif // BOARD_H
