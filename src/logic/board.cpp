/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: board.cpp                                   *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

/**
 * @file board.cpp
 * @brief Soubor obsahující třídu reprezentující hrací desku hry.
 * @author Staněk Petr <xstane34@stud.fit.vutbr.cz>
 * @author Stejskal Jakub <xstejs24@stud.fit.vutbr.cz>
 */

#include "board.h"
#include "game.h"

Board::Board(int boardSize)
{	
	this->boardSize = boardSize;	
	
	// inicializace matice desky
	this->initBoard();
	
	// umístění počátečních kamenů
	this->initDisks();

	// inicializace kurzoru (na rozumné místo, není připraven na umístění mimo desku)
	this->setCursor(this->boardSize/2+1, this->boardSize/2+2);
}

void Board::initBoard()
{
	// pro každý sloupec
	for (int x = 0; x < this->boardSize; x++) 
	{
		// vytvoření řádku v sloupci
		this->boardVector.push_back (vector<Field*>());
		
		// vygenerování buněk v řádku
		for (int y = 0; y < this->boardSize; y++)
			this->boardVector[x].push_back (new Field(x+1, y+1));
	}
}

void Board::initDisks()
{
	int x = this->boardSize/2;
	int y = this->boardSize/2;
	
	// umístění bílích kamenů
	this->getField(x+1, y+1)->setColor(FieldColor::WHITE);
	this->getField(x, y)->setColor(FieldColor::WHITE);
	
	// umístění černých kamenů
	this->getField(x+1, y)->setColor(FieldColor::BLACK);
	this->getField(x, y+1)->setColor(FieldColor::BLACK);	
}

void Board::clearHighlights()
{
	// pro každý řádek
	for (int y = 1; y <= this->boardSize; y++) 
	{
		// pro každý sloupec
		for (int x = 1; x <= this->boardSize; x++)
			this->getField(x, y)->clearHighlight(); // smazání zvýraznění
	}
}

void Board::moveCursor(MoveDirection d)
{	
	if (d == UP) // posun nahoru
	{
		if (this->getCursor()->y > 1) 
			this->getCursor()->y--; 
		
	}
	else if (d == DOWN) // posun dolů
	{
		if (this->getCursor()->y < this->boardSize) 
			this->getCursor()->y++; 
	}
	else if (d == LEFT) // posun vlevo
	{
		if (this->getCursor()->x > 1)
			this->getCursor()->x--; 
	}
	else if (d == RIGHT) // posun vpravo
	{
		if (this->getCursor()->x < this->boardSize)
			this->getCursor()->x++; 
	}
}

bool Board::isOnBoard(int x, int y)
{
	// pokud bod leží na desce
	return (x > 0 && x <= this->boardSize && y > 0 && y <= this->boardSize);
}

bool Board::isOnCorner(int x, int y)
{
	return (x == 1 and y == 1) || 
		   (x == this->getBoardSize() and y == 0) || 
		   (x == 0 and y == this->getBoardSize()) || 
		   (x == this->getBoardSize() and y == this->getBoardSize());
}