/* 
 * File:   main.cpp
 * Author: frawless
 *
 * Created on 8. březen 2016, 12:51
 */

#include "hra2016cli.h"


//using namespace std;
using namespace boost;

hra2016cli::hra2016cli()
{
	this->gameState = NONE;
	start();
}

bool hra2016cli::processInput(std::string input) 
{ 
	bool end = false;
	const char* response = input.c_str();
	cmatch what; 
	
	if(this->gameState = hra2016cli::RUNNING)
	{
		if(regex_match(response, what, regex ("([a-z]) ([0-9]{1,2})")))	// tah na místo 
		{ 
			std::cout<<"Položení kamene na souřadnice"<<std::endl;
			std::cout<<what[1]<<"-"<<what[2]<<std::endl; 
		}
		else if(regex_match(response, what, regex ("s")))	// uložení hry
		{ 
			std::cout<<"Uložení hry"<<std::endl; 
		}	
		else if(regex_match(response, what, regex ("<")))	// krok vzad
		{ 
			std::cout<<"Krok vzad"<<std::endl; 
		}
		else if(regex_match(response, what, regex (">")))	// krok vpřed
		{ 
			std::cout<<"Krok vpřed"<<std::endl; 
		}	
		else if(regex_match(response, what, regex ("q")))	// konec hry
		{ 
			std::cout<<"Konec hry"<<std::endl; 
			this->gameState = hra2016cli::NONE;
		}	
	}
	
	if(regex_match(response, what, regex ("n (p|c)")))	// nová hra
	{ 
		std::cout<<"Nová hra o velikosti pole: 8"<<std::endl; 
		this->gameState = hra2016cli::RUNNING;
	}  
	else if(regex_match(response, what, regex ("n ([0-9]*) (p|c)")))	// nová hra
	{ 
		std::cout<<"Nová hra o velikosti pole:"<<what[1]<<std::endl;
		this->gameState = hra2016cli::RUNNING;
	}	
	else if(regex_match(response, what, regex ("h")))	//	nápověda
	{ 
		std::cout<<"Vypíše nápovědu"<<std::endl; 
	}  	 
	else if(regex_match(response, what, regex ("l")))	// nahrání hry hry
	{ 
		std::cout<<"Nahrání hry"<<std::endl; 
		this->gameState = hra2016cli::RUNNING;
	}
	else if(regex_match(response, what, regex ("exit")))	// konec programu
	{ 
		std::cout<<"Konec programu"<<std::endl; 
		end = true;
	}	
	else{
		 std::cout<<"Neznámý příkaz! Pro nápovědu zadejte písmeno 'h'"<<std::endl; 	   
	}
	
	return end;
}

void hra2016cli::start(){
	bool end = false;
	std::string input;
	
	while(!end){	
		std::cout<<"Prompt>";
		std::getline(std::cin,input);
		std::cout<<"Zadáno: "<<input<<std::endl;	
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
