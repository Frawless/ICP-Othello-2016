/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: types.h	                                 *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

/**
 * @file types.h
 * @brief Hlavičkový soubor obsahující definované typy - výčty typů hráčů a algoritmů.
 * @author Staněk Petr <xstane34@stud.fit.vutbr.cz>
 * @author Stejskal Jakub <xstejs24@stud.fit.vutbr.cz>
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * @brief Výčet typů hráčů.
 */
enum PlayerType
{
	PERSON /**< člověk */, 
	COMPUTER /**< počítač (tj. algoritmus) */
};

/**
 * @brief Výčet možných algoritmů.
 */
enum PlayerAlgorithm
{
	ALG1 /**< první algoritmus */,
	ALG2/**< druhý algoritmus */, 
	ALG_NONE /**< algoritmus nezvolen */
};

/**
 * @brief Výčet možných barev hráčů a políček.
 */
enum FieldColor
{
	BLACK /**< černá */, 
	WHITE /**< bílá */, 
	EMPTY /**< žádná barva */
};

#endif /* TYPES_H */

