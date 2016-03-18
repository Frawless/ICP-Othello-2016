#ifndef BOARD_H
#define BOARD_H

#include <QGridLayout>

class QBoard
{
public:
    QBoard(QWidget *parent);
    QWidget *getBoard() {return board;};

private:
    QWidget *board;
    QGridLayout *layout;
};

#endif // BOARD_H
