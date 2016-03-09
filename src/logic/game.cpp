/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: gane.h                                      *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

#include "game.h"
#include "board.h"

class Player;
class Board;

Game::Game(unsigned int boardSize, Player::PlayerType secondPlayerType)
{
	this->firstPlayer = new Player(Player::PERSON);
	this->secondPlayer = new Player(secondPlayerType);
	this->playerOnMove = this->firstPlayer; // ???? kdo bude první na tahu? nebo náhoda?
	
	// vytvoření hrací desky
	this->board = new Board(boardSize);	
	
	std::cout<<"DEBUG: Game(boardSize == "<<boardSize<<", secondPlayerType="<<secondPlayerType<<")"<<std::endl;
}

Game::Game(Player::PlayerType secondPlayerType)
{
	this->firstPlayer = new Player(Player::PERSON);
	this->secondPlayer = new Player(secondPlayerType);
	this->playerOnMove = this->firstPlayer; // ???? kdo bude první na tahu? nebo náhoda?
	
	// vytvoření hrací desky
	this->board = new Board();	
	
	std::cout<<"DEBUG: Game(secondPlayerType="<<secondPlayerType<<")"<<std::endl;
}