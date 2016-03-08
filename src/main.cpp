/* 
 * File:   main.cpp
 * Author: frawless
 *
 * Created on 8. březen 2016, 12:51
 */

#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

#include <regex>

using namespace std;

bool processString(string str) 
    {
        bool end = false;

        regex p("^s([1-7]{1})([1-7]{1})$");
        smatch match;
		
        
        // zobrazení hrací desky a volného kamene
        if ("p" == str) 
        {            
            cout<<"Hrací plocha:"<<endl;
            //labyrinth.showBoard();
            
            cout<<"Volný kámen:"<<endl;
            //labyrinth.showFreeCard();
            
        }
        // vytvoření nové hry
        else if ("n" == str)
        {
            cout<<"Vytvořena nová hra!"<<endl;
            //labyrinth.newGame();
        }
        // ukončení programu
        else if ("q" == str)
        {
            cout<<"Ukončuji aplikaci..."<<endl;
            return 0;
        }
        
        // posun kamenů
        else if (regex_search(str,match,p))
        {
            string R, C; 
            R = match.str(1);
            C = match.str(2);
            
            cout<<"Proveden posun kamenů"<<endl;
			cout<<"R = "<<R<<" -> C = "<<C<<endl;
            //labyrinth.shift(labyrinth.get(R, C));
        } 
        else
            cout<<"neexistující příkaz"<<endl;
             
        return end;
    }


/*
 * 
 */
int main(int argc, char** argv) {
	cout<<"C++ string"<<endl;
	string s;
	while(std::cin>>s){
		cout<<"Zadáno: "<<s<<endl;
		processString(s);	
	}
		
	
	return 0;
}

