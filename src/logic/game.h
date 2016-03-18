/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: game.h		                                 *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

/**
 * @file game.h
 * @brief Hlavičkový soubor obsahující třídu představující hlavní logiku aplikace. 
 * @author Staněk Petr <xstane34@stud.fit.vutbr.cz>
 * @author Stejskal Jakub <xstejs24@stud.fit.vutbr.cz>
 */

#ifndef GAME_H
#define GAME_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/filesystem.hpp>

#include <map>
#include <ctime>

#include "player.h"
#include "board.h"

class Player;
class Board;

using namespace std;

/**
 * @class Game
 * @brief Třída reprezentující hlavní logiku hry.
 * Implementuje algoritmy, které umožní o vyhodnotit hru a nastavit její nový stav
 * po položení kamene a také správu historie.
 */
class Game
{
	/**
	 * @brief Struktura souřadnic.
	 */
	typedef struct Coords 
	{
		public: 
			int x; /**< x-ová souřadnice */
			int y; /**< y-ová souřadnice */
		private:
			template<class Archive>
			void serialize(Archive & ar, const unsigned int version)
			{
				(void)version;
				ar & x;
				ar & y;
			}
	} Coords;
	
	public:
		static const int DEFAULT_BOARD_SIZE = 8; /**< defaultní velikost desky */
		
		// konstruktory
		/** konstruktor spouštějící hru s nedefinovanými atributy pro potřeby deserializace */
		Game(){}; 
		/**
		* Konstruktor spouštějící novou se zadanou velikostí desky, zvoleným typem 
		* protihráče a jeho případným algortimem (u hráče typu počítač).
		* @param boardSize velikost hrací desky
		* @param secondPlayerType typ hráče (člověk nebo počítač)
		* @param playerAlgorithm algoritmus hráče (žádný, nebo algortimus 1 nebo 2 
		* v případě počítače)
		*/
		Game(int boardSize, Player::PlayerType secondPlayerType, Player::PlayerAlgorithm playerAlgorithm);
		
		// datové typy
		/**
		 * @brief Datový typ multimapy se seznamem uložených her.
		 */
		typedef multimap<time_t, boost::filesystem::path, greater<time_t>> TGamesList;
		
		// metody
		/**
		 * Vrátí ukazatel na desku.
		 * @return ukazatel na desku
		 */
		Board *getBoard() {return board;}; 
		
		/**
		 * Vrátí ukazatel na hráče na tahu
		 * @return ukazatel na hráče na tahu
		 */
		Player *getPlayerOnMove() {return playerOnMove;};
		
		/**
		 * Ukazatel na 1. horáče.
		 * @return ukazatel na 1. hráče
		 */
		Player *getFirstPlayer() {return firstPlayer;};
		
		/**
		 * Ukazatel na 1. horáče.
		 * @return ukazatel na 1. hráče
		 */
		Player *getSecondPlayer() {return secondPlayer;};
		
		/**
		 * Vrátí ukazatel na protihráče.
		 * @return azatel na protihráče
		 */
		Player* getOponent(); 
		
		/**
		 * Uvede dalšího hráče na tah.
		 */
		void swapPlayers();
		
		/**
		 * Vrátí ukazatel na hráče, který je v okamžiku zavolání metodu výtězem.
		 * @return ukazatel na vítěze
		 */
		Player* getWinner();
		
		/**
		 * Zjistí, zda je možný jakýkoliv tah a aktualizuje počet získaných kamenů hračů.
		 * @return true, pokud je možný jakýkoliv tah
		 */
		bool getMoves();
		
		/**
		 * Zjistí, zda je možné provést ze zadaného políčka tah.
		 * @param x x-ová souřadnice výchozího bodu
		 * @param y y-ová souřadnice výchozího bodu
		 * @return true, pokud je možné provést tah
		 */
		bool existsBoundedStone(int x, int y);
		
		/**
		 * Prove tah z políčka umístěného pod kurzorem dle pravidel hry.
		 * @param onlyHighlight pokud true, provede pouze zvýraznění políček získaných
		 * případným tahem
		 * @return true, pokud byl tah mohl být proveden
		 */
		bool processMove(bool onlyHighlight);
		
		/**
		 * Vrátí všechny políčka/kameny, jejiž barva je potřeba změnit.
		 * @param x x-ová souřadnice výchozího bodu
		 * @param y y-ová souřadnice výchozího bodu
		 * @return vektor ukazatelů na políčka
		 */
		vector<Field*> getAllBoundedStones(int x, int y);
		
		/**
		 * Uloží rozehranou hru do souboru pod zadaným názvem.
		 * @param name název souboru ukládané hry
		 */
		void save(string name);
		
		/**
		 * Vrátí ukazatel na uloženou hru zadanou cestou.
		 * @param path cesta k souboru se hrou
		 * @return ukazatel na hru
		 */
		static Game* getSavedGame(string path);
		
		/**
		 * Vrátí mapu všech uložených her.
		 * @note automaticky maže nejstarší 11. až n-tou hru
		 * @return mapa her
		 */	
		static TGamesList getSavedGames();
		
		/**
		 * Uloží aktuální stav hry pro potřeby historie (undo/redo).
		 */
		void saveHistory(); 
		
		/**
		 * Uvede hru o krok zpět, dokud existuje uložená historie.
		 * @return true, pokud není historie vyčerpána
		 */
		bool undoHistory(); 
		
		/**
		 * Obnoví vrácenou hru zpět, dokud existuej uložená historie.
		 * @return true, pokud není historie vyčerpána 
		 */
		bool redoHistory(); 
		
		void getScore(); // nastaví aktuální scóre po provedení tahu
		
	private:
		// pro potřeby serializace
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			(void)version;
			ar & firstPlayer;
			ar & secondPlayer;
			ar & playerAlgorithm;
			ar & playerOnMove;
			ar & board;
		}
		
		// metody
		
		/**
		 * Provede tah počítačem podle zvoleného algoritmu.
		 * @note metoda sama testuje, zdali je hráčem na tahu počítač
		 */
		void processAIMove();
		
		/**
		 * Zjistí, zda je možné provést tah alespoň jedním hráčem.
		 * @return true, pokud je možné provést tah
		 */
		bool isAnyMovePossible();
		
		/**
		 * Vrátí cesty, kterými je možné z bodu [x, y] provést tah.
		 * @param x x-ová souřadnice výchozího bodu
		 * @param y y-ová souřadnice výchozího bodu
		 * @return vektor cest
		 */
		vector<Coords> getPossibleWays(int x, int y);
		
		/**
		 * Vrátí políčka, jejichž barva bude změněna během tahu.
		 * @param x x-ová souřadnice výchozího bodu
		 * @param y y-ová souřadnice výchozího bodu
		 * @param dx x-ová souřadnice směru vyhodnocování
		 * @param dy y-ová souřadnice směru vyhodnocování
		 * @return vektor ukazatelů na políčka
		 */
		vector<Field*> getBoundedStones(int x, int y, int dx, int dy);
		
		// atributy
		Player *firstPlayer; /**< ukazatel na prvního hráče */
		Player *secondPlayer; /**< ukazatel na druhého hráče */
		Player::PlayerAlgorithm playerAlgorithm; /* algoritmus hráče */
		Player *playerOnMove; /**< ukazatel na aktuálního hráče na tahu */
		Board *board; /**< vygenerovaná hrací plocha */
		vector<string> undo; /**< vektor kroků hry */
		vector<string> redo; /**< vektor vrácených kroků hry */
};

#endif

