/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: game.h		                                 *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"

using namespace std;

class Board;
class Player;

class Game
{
	public:
		Game(unsigned int boardSize, Player::PlayerType secondPlayerType);
		Game(Player::PlayerType secondPlayerType);
		Board *getBoard() {return board;}
		Player *getPlayerOnMove() {return playerOnMove;}
	private:
		Player *firstPlayer; /* první hráč */
		Player *secondPlayer; /* druhý hráč */
		Player *playerOnMove; /* aktuální hráč na tahu */
		Board *board; /* vygenerovaná hrací plocha */
		
		void swapPlayers(); /* přepne aktuálního hráče na tahu */
		
};

#endif

