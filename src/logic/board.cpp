/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: board.cpp                                   *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

#include <iostream>

#include "board.h"

const int boardDefaultSize = 8;

Board::Board()
{
	std::cout<<"DEBUG: Board(boardSize == "<<boardDefaultSize<<")"<<std::endl;
	this->boardSize = boardDefaultSize;
}

Board::Board(int boardSize)
{
	std::cout<<"DEBUG: Board(boardSize == "<<boardSize<<")"<<std::endl;
	this->boardSize = boardSize;
}



