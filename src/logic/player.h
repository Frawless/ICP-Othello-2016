/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: player.h                                    *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

using namespace std;

class Player
{
	public:
		enum PlayerType{PERSON, COMPUTER}; /* výčet typů hráčů */
		Player(Player::PlayerType playerType);
		
	private:
		PlayerType playerType; /* typ hráče */
};

#endif