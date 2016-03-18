/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: hra2016cli.h                                *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

/**
 * @file hra2016cli.h
 * @brief Hlavičkový soubor obsahující hlavní třídu aplikace ovládanou pomocí příkazové
 * řádky (CLI).
 * @author Staněk Petr <xstane34@stud.fit.vutbr.cz>
 * @author Stejskal Jakub <xstejs24@stud.fit.vutbr.cz>
 */

#ifndef HRA2016CLI_H
#define	HRA2016CLI_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "logic/game.h"

class Game;
class Board;

using namespace std;

/**
 * @class hra2016cli
 * @brief Hlavní třída aplikace ovládané pomocí příkazové řádky (CLI).
 * Implementuje příkazovou řádku, zpracování příkazů a vykreslování hry v textové
 * podobě. 
 */
class hra2016cli
{
	public:
		/**
		* Konstruktor spouštějící aplikaci hry ovládanou pomocí příkazové řádky.
		*/
		hra2016cli();
		
		/**
		 * Spustí příkazový řádek pro ovládání hry a běží v cyklu, dokud není ukončeno
		 * zadávání znaků (příkaz exit).
		 */
		void startCLI();
		
		/**
		 * Umožňuje definovat testy pro otestování hry. Slouží pro účely testování.
		 */
		void testGame(); /* otestuje hru provedením předem definovaných kroků */
	
	private: 
		// pro potřeby serializace
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			(void)version;
			ar & tmpBoardSize;
			ar & tmpPlayerType;
			ar & game;
			ar & state;
		}
		
		// enumerace
		/**
		 * @brief Výčet stavů běhu programu sloužící pro zajištění chování CLI.
		 */
		enum ProgramState
		{
			RUNNING /**< běží v normálním režimu zadávání bez podnabídky */, 
			ASKING_FOR_ALGORITHM /**< vyžaduje zvolení algoritmu */, 
			LOADING_GAME /**<  vyžaduje zvolení uložené hry */, 
			SAVING_GAME /**<  vyžaduje zadání názvu ukládané hry */, 
			NONE /**<  program neběží */
		};
		
		// atributy
		ProgramState state; /**< stav běhu programu */
		Game *game; /**< ukazatel na běžící hru */
		int tmpBoardSize; /**< pomocná proměnná s velikostí desky */
		Player::PlayerType tmpPlayerType; /**< pomocná proměnná s typem protihráče */
		
		// metody
		/**
		 * Na základě zadaného příkazu vyvolá k němu přidruženou akci.
		 * @param command příkaz
		 * @return true, pokud je vyžádáno zrušení zadávání znaků (ukončení aplikace
		 * příkazem exit)
		 */
		bool processCommand(string command);
		
		/**
		* Spustí novou se zadanou velikostí desky, zvoleným typem protihráče a jeho 
		* případným algortimem (u hráče typu počítač).
		* @param boardSize velikost hrací desky
		* @param playerType typ hráče (člověk nebo počítač)
		* @param playerAlgorithm algoritmus hráče (žádný, nebo algortimus 1 nebo 2 
		* v případě počítače)
		*/
		void newGame(int boardSize, Player::PlayerType playerType, Player::PlayerAlgorithm playerAlgorithm);
		
		/**
		 * Posuno kurzor označující uvažované políčko zadaným směrem.
		 * @param direction směr posunu políčka
		 */
		void moveCursor(Board::MoveDirection direction); 
		
		/**
		 * Umístí kámen na místo aktuální polohy kurzoru a provede tah k tomuto políčku.
		 */
		void putDisk(); 
		
		/**
		* Ukončí běžící hru.
		*/
		void quitGame();
		
		/**
		 * Provede aktualizaci datového prostoru hry vzhledem k aktuální poloze kurzoru,
		 * což bude mít za následek zvýraznění těch políček, které budou získány položením
		 * kamene na toto místo. Dále je zobrazena/aktualizována hrací deska a stav hry.
		 */
		void revalidate();
		
		/**
		* Zobrazí aktuální stav hry (hráče na tahu, počet zbývajících kamenů a skóre).
		*/
		void showState();
		
		/**
		* Zobrazí hrací desku hry.
		*/
		void showBoard();
		
		/**
		 * Zobrazí výherce hry. 
		 * @note Metoda je volána v případě zjištěného konce hry.
		 */
		void showResults();
		
		/**
		 * Zobrazí textovou nápovědu programu.
		 */
		void showHelp(); 
};

#endif