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