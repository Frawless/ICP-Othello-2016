/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: field.h                                     *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

/**
 * @file field.h
 * @brief Hlavičkový soubor obsahující třídu reprezentující políčko hrací desky.
 * @author Staněk Petr <xstane34@stud.fit.vutbr.cz>
 * @author Stejskal Jakub <xstejs24@stud.fit.vutbr.cz>
 */

#ifndef FIELD_H
#define FIELD_H

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;

/**
 * @class Field
 * @brief Třída reprezentující políčko hrací desky.
 */
class Field
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
		/**
		 * Konstruktor vytvářející nové dílčí políčko hrací desky.
		 * @param x x-ová souřadnice políčka
		 * @param y y-ová souřadnice políčka
		 */
		Field(int x, int y);
		
		/** konstruktor vytvářející nové dílčí políčko hrací desky pro potřeby
		  * deserializace */
		Field() {};
		
		/**
		 * @brief Výčet možných barev hráčů.
		 */
		enum FieldColor
		{
			BLACK /**< černá */, 
			WHITE /**< bílá */, 
			EMPTY /**< žádná barva */
		};
		
		// metody
		/**
		 * Vrátí souřadnice aktuálního políčka.
		 * @return ukazatel na strukturu se souřadnicemi
		 */
		Coords *getCoords() {return &coords;};
		
		/**
		 * Nastaví souřadnice kurzoru.
		 * @param x x-ová souřadnice kurzoru
		 * @param y y-ová souřadnice kurzoru
		 */
		void setCoords(int x, int y) {this->coords.x = x; this->coords.y = y;};
		
		/**
		 * Nastavení zvýraznění políček. 
		 */
		void setHighlight() {this->highlight = true;}; 
		
		/**
		 * Smazání zvýraznění označení všech políček.
		 */
		void clearHighlight() {this->highlight = false;}; 
		
		/**
		 * Nastaví barvu políčka zadanou parametrem.
		 * @param fieldColor barva políčka
		 */
		void setColor(FieldColor fieldColor) {this->fieldColor = fieldColor;};
		
		/**
		 * Vrátí barvu políčka.
		 * @return 
		 */
		FieldColor getColor() {return this->fieldColor;};
		
		/**
		 * Zjistí, zda je políčko zvýrazněno.
		 * @return 
		 */
		bool isHighlight() {return this->highlight;}; 
	
	private:
		// pro potřeby serializace
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			(void)version;
			ar & coords;
			ar & fieldColor;
			ar & highlight;
		}
		
		// atributy
		Coords coords; /**< souřadnice políčka */
		FieldColor fieldColor; /**< barva políčka */
		bool highlight; /**< zvýraznění políčka */	
};

#endif
