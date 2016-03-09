/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: hra2016cli.cpp                              *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/


#ifndef HRA2016CLI_H
#define	HRA2016CLI_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/regex.hpp>


class hra2016cli
{
	public:
		hra2016cli();
		enum Type{RUNNING,NONE};
		
		
	private:
		void start();
		bool processInput(std::string input);
		Type gameState;
};

#endif