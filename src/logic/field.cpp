/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: field.cpp                                   *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

/**
 * @file field.cpp
 * @brief Soubor obsahující třídu reprezentující políčko hrací desky.
 * @author Staněk Petr <xstane34@stud.fit.vutbr.cz>
 * @author Stejskal Jakub <xstejs24@stud.fit.vutbr.cz>
 */

#include "field.h"

Field::Field(int x, int y)
{
	// nastavení souřadnic
	this->setCoords(x, y);
	// nastavení počáteční barvy
	setColor(FieldColor::EMPTY);
	
	// vymazání (inicializace) zvýraznění políček získatelných možným tahem
	this->clearHighlight();
	
}

