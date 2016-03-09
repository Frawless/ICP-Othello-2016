/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: player.cpp                                  *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

#include "player.h"

Player::Player(Player::PlayerType playerType)
{
	std::cout<<"DEBUG: Player(playerType == "<<playerType<<")"<<std::endl;
	this->playerType = playerType;
}