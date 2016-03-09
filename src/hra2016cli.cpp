/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: hra2016cli.cpp                              *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

#include "hra2016cli.h"
#include "logic/player.h"
#include "logic/game.h"

class Game;


hra2016cli::hra2016cli()
{
	this->gameState = NONE;
	start();
}

bool hra2016cli::processInput(string input) 
{ 
	bool end = false;
	const char* response = input.c_str();
	boost::cmatch what; 
	
	if(this->gameState == hra2016cli::RUNNING)
	{
		if(boost::regex_match(response, what, boost::regex ("([a-z]) ([0-9]{1,2})")))	// tah na místo 
		{ 
			cout<<"Položení kamene na souřadnice"<<endl;
			cout<<what[1]<<"-"<<what[2]<<endl; 
		}
		else if(boost::regex_match(response, what, boost::regex ("s")))	// uložení hry
		{ 
			cout<<"Uložení hry"<<endl; 
		}	
		else if(boost::regex_match(response, what, boost::regex ("<")))	// krok vzad
		{ 
			cout<<"Krok vzad"<<endl; 
		}
		else if(boost::regex_match(response, what, boost::regex (">")))	// krok vpřed
		{ 
			cout<<"Krok vpřed"<<endl; 
		}	
		else if(boost::regex_match(response, what, boost::regex ("q")))	// konec hry
		{ 
			cout<<"Konec hry"<<endl; 
			this->gameState = hra2016cli::NONE;
		}	
	}
	
	if(boost::regex_match(response, what, boost::regex ("n (p|c)")))	// nová hra
	{ 
		this->gameState = hra2016cli::RUNNING;
		
		// spuštění hry se zadanými parametry
		Game *game = new Game(string(what[1]) == "p" ? Player::PERSON : Player::COMPUTER);
		
		cout<<"Nová hra o velikosti pole: "<<game->getBoard()->getBoardSize()<<", druhý hráč:"<<what[1]<<endl; // ??? pc nebo person?
		
	}  
	else if(boost::regex_match(response, what, boost::regex ("n ([0-9]*) (p|c)")))	// nová hra
	{ 
		this->gameState = hra2016cli::RUNNING;
		
		// spuštění hry se zadanými parametry
		
		Game *game = new Game(stoi(string(what[1])), string(what[2]) == "p" ? Player::PERSON : Player::COMPUTER);	
		cout<<"Nová hra o velikosti pole:"<<game->getBoard()->getBoardSize()<<", druhý hráč:"<<what[2]<<endl;

	}	
	else if(boost::regex_match(response, what, boost::regex ("h")))	//	nápověda
	{ 
		cout<<"Vypíše nápovědu"<<endl; 
	}  	 
	else if(boost::regex_match(response, what, boost::regex ("l")))	// nahrání hry hry
	{ 
		cout<<"Nahrání hry"<<endl; 
		this->gameState = hra2016cli::RUNNING;
	}
	else if(boost::regex_match(response, what, boost::regex ("exit")))	// konec programu
	{ 
		cout<<"Konec programu"<<endl; 
		end = true;
	}	
	else{
		 cout<<"Neznámý příkaz! Pro nápovědu zadejte písmeno 'h'"<<endl; 	   
	}
	
	return end;
}

void hra2016cli::start(){
	bool end = false;
	string input;
	
	cout<<"Spuštěna hra Othello! Ovládejte pomocí CLI. Pro nápovědu zadejte h."<<endl;
	
	while(!end){	
		cout<<"Prompt>";
		getline(cin,input);
		cout<<"Zadáno: "<<input<<endl;	
		end = processInput(input);
	}	
}

/*
 * 
 */
int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	new hra2016cli();
	
	return 0;
}
