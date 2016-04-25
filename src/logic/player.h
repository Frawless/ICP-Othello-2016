/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: player.h                                    *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

/**
 * @file player.h
 * @brief Hlavičkový soubor obsahující třídu reprezentující hráče hry.
 * @author Staněk Petr <xstane34@stud.fit.vutbr.cz>
 * @author Stejskal Jakub <xstejs24@stud.fit.vutbr.cz>
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
//25.4
#include <vector>


#include "field.h"
#include "types.h"

class Game;
class Field;

using namespace std;

/**
 * @class Player
 * @brief Třídu reprezentující hráče hry.
 */
class Player
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
		Player(){};
		/**
		 * Konstruktor vytvářející nového hráče se zadanou barvou, typem a algoritmem.
		 * @param game ukazatel na hru
		 * @param playerColor barva hráče (bílá nebo černá dle barvy jeho políčka)
		 * @param playerType typ hráče (člověk nebo počítač)
		 * @param playerAlgorithm algoritmus hráče (žádný, nebo algortimus 1 nebo 2 
		 */
		Player(Game *game, FieldColor playerColor, PlayerType playerType, PlayerAlgorithm playerAlgorithm);
		
		/**
		 * Konstruktor vytvářející nového hráče se zadanou barvou, typem.
		 * @param game ukazatel na hru
		 * @param playerColor barva hráče (bílá nebo černá dle barvy jeho políčka)
		 * @param playerType typ hráče (člověk nebo počítač)
		 */
		Player(Game *game, FieldColor playerColor, PlayerType playerType);
		/**
		 * Vrátí barvu hráče (shodnou s barvou políčka)
		 * @return barva hráče
		 */		
		FieldColor getColor() {return playerColor;};
		
		/**
		 * Vrátí počet zbývajících kamenů hráče.
		 * @return počet kamenů
		 */		
		int getAvalaibleStones() {return avalaibleStones;};
		
		/**
		 * Vrátí počet získaných kamenů hráčem.
		 * @return počet kamenů
		 */		
		int getOwnedDisks() {return ownedStones;};
		
		/**
		 * Nastaví počet
		 * @param x
		 */		
		void setAvalaibleStones(int x) {avalaibleStones = x;};
		
		/**
		 * Sníží počet dostupných kamenů. 
		 */		
		void decrementAvalaibleStones() {avalaibleStones--;};
		
		/**
		 * Nastaví počet kamenů získaných hráčem.
		 * @param x počet kamenů
		 */		
		void setOwnedStones(int x) {ownedStones = x;};
		
		/**
		 * Vrátí typ hráče.
		 * @return typ hráče
		 */		
		PlayerType getPlayerType() {return playerType;};
		
		/**
		 * Zformátuje (obarví) zadaný řetězec barvou hráče.
		 * @param text formátovaný text
		 * @return zformátovaný řetězec
		 */		
		string formatPlayer(string text){ return this->playerColor == FieldColor::BLACK ? "\033[41m"+text+"\033[0m" : "\033[43m"+text+"\033[0m";};
		
		/**
		 * Nastaví souřadnici posledního položení kamene.
		 * @param x x-ová souřadnice
		 * @param y y-ová souřadnice
		 */		
		void setLastMove(int x, int y){lastMove.x = x; lastMove.y = y;};
		
		/**
		 * Vrátí souřadnici posledního položení kamene.
		 * @return souřadnice posledního položení kamene
		 */
		Coords getLastMove(){return lastMove;};		

		/**
		 * Provede tah algoritmem počítače (algoritmus 1).
		 */
		void proccessMoveAIv1();
		
		/**
		 * Provede tah algoritmem počítače (algoritmus 2).
		 */
		void proccessMoveAIv2();
		
		/**
		 * Zjistí ohodnocení výhodnosti kroku.
		 * @param dx x-ová souřadnice směru vyhodnocování
		 * @param dy y-ová souřadnice směru vyhodnocování
		 * @return číslo vyjadřující výhodnost kroku
		 */
		int getMoveHeurestic(int dx, int dy);

		/**
		 * Umístí kámen na zadané políčko a obarví jej barvou hráče.
		 * @param x x-ová souřadnice políčka
		 * @param y y-ová souřadnice políčka
		 */
		void putDisk(int x, int y);
		
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			(void)version;
			ar & playerType;
			ar & playerColor;
			ar & avalaibleStones;
			ar & ownedStones;
			ar & playerAlgorithm;
			ar & game;
			ar & lastMove;
		}
		PlayerType playerType; /**< typ hráče */
		FieldColor playerColor; /**< barva hráče */
		int avalaibleStones; /**< počet zbývajících kamenů */ 
		int ownedStones; /**< počet získaných kamenů */
		PlayerAlgorithm playerAlgorithm; /**< algoritmus hráče */
		Game* game; /**< ukazatel na hru */
		Coords lastMove; /**< souřadnice místa posledního položeného kamene */
};

#endif