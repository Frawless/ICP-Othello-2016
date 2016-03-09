/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: board.h                                     *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board
{
	public:
		Board();
		Board(int boardSize); // ??? ošetřit velikost boarDsize
		int getBoardSize() {return boardSize;}

	private:
		int boardSize; /* velikost hrací desky */
		
};

#endif