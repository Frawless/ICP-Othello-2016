/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: board.h                                     *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

/**
 * @file board.h
 * @brief Hlavičkový oubor obsahující třídu reprezentující hrací desku hry.
 * @author Staněk Petr <xstane34@stud.fit.vutbr.cz>
 * @author Stejskal Jakub <xstejs24@stud.fit.vutbr.cz>
 */

#ifndef BOARD_H
#define BOARD_H

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#include <sstream>

class Field;

using namespace std;

const vector<int> defaultBoardSizes {6, 8, 10, 12}; // vektor možných velikostí hrací desky (sám si to takto chtěl :D)

/**
 * @class Board
 * @brief Třída reprezentující hrací desku hry.
 */
class Board
{
	/**
	 * @brief Struktura souřadnic.
	 */
	struct Coords 
	{
		public: 
			int x; /**< x-ová souřadnice */
			int y; /**< y-ová souřadnice */

			template<class Archive>
			void serialize(Archive & ar, const unsigned int version)
			{
				(void)version;
				ar & x;
				ar & y;
			}
	};	

	public:
		// konstruktory
		/** konstruktor desky pro potřeby deserializace */
		Board(){}; 
		
		/**
		 * Konstruktor vytvářející novou hrací desku zadané velikosti.
		 * @param boardSize velikost hrací desky
		 */
		Board(int boardSize); /* vytvoří desku se zadanou velikostí */
		
		/**
		 * @brief Výčet směrů posunu kurzoru po hrací desce.
		 */
		enum MoveDirection
		{
			LEFT /**< vlevo */, 
			UP /**< nahorů */, 
			RIGHT /**< vpravo */, 
			DOWN /**< dolů */
		};
		
		// metody
		
		/**
		 * Zjistí, zda se zadaný bod nachází na desce.
		 * @param x x-ová souřadnice bodu
		 * @param y y-ová souřadnice bodu
		 * @return true, pokud se bod nachází na desce
		 */
		bool isOnBoard(int x, int y);
		
		/**
		 * Zjistí, zda zadaný bod leží v některém z rohl hrací desk.
		 * @param x x-ová souřadnice bodu
		 * @param y y-ová souřadnice bodu
		 * @return true, pokud bod leží v rohu desky
		 */
		bool isOnCorner(int x, int y);
		
		/**
		 * Vrátí velikost hrací desky
		 * @return velikost hrací desky
		 */
		int getBoardSize() {return boardSize;};
		
		/**
		 * Vrátí ukazatel na políčko zadané sořadnicemi.
		 * @param x x-ová souřadnice
		 * @param y y-ová souřadnice
		 * @return 
		 */
		Field * getField(int x, int y) {return this->boardVector[y-1][x-1];}; 
		
		/**
		 * Posune kurzor zadaným směrem
		 * @param direction směr posunu kurzoru
		 */
		void moveCursor(MoveDirection direction); 
		
		/**
		 * Vrátí souřadnice kurzoru.
		 * @return souřadnice kurzoru
		 */
		Coords *getCursor() {return &cursorCoords;}; 
		
		/**
		 * Smaže všechna zvýrazení položení kamene. 
		 */
		void clearHighlights();
		
		/**
		 * Nastaví aktuální hodnotu kurzoru.
		 * @param x x-ová souřadnice
		 * @param y y-ová souřadnice
		 */
		void setCursor(int x, int y) {if (isOnBoard(x, y)) {cursorCoords.x = x; cursorCoords.y = y;} else throw invalid_argument("Souřadnice kurzoru mimo desku.");};
		
	private:
		// pro potřeby serializace
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			(void)version;
			ar & boardSize;
			ar & boardVector;
			ar & cursorCoords;
		}
		int boardSize; /**< velikost hrací desky */
		vector<vector<Field*>> boardVector; /**< hrací deska */
		Coords cursorCoords; /**< souřadnice kurzoru */

		/**
		 * Inicializuje matici hrací desky.
		 */
		void initBoard();
		
		/**
		 * Umístí počáteční kameny na hrací desku.
		 */
		void initDisks(); /* inicializace počátečních kamenů */
			
};

#endif