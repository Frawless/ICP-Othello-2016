#include "qboard.h"
#include "qfield.h"

QBoard::QBoard(QWidget *parent, Game *game)
{
    this->game = game;
	this->board = new QWidget(parrent);
    this->layout = new QGridLayout();
    this->board->setLayout(this->layout);

    // pro každý sloupec
        for (int y = 0; y < 8; y++)
        {
            // pro každý řádek
            for (int x = 0; x < 8; x++)
            {
                QField * field = new QField(parrent);
                this->layout->addWidget(field->getField(),x,y);
				
            }
        }
}
