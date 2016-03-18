#ifndef BOARD_H
#define BOARD_H

#include "../logic/board.h"
#include "../logic/game.h"

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
