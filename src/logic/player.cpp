/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: player.cpp                                  *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

/**
 * @file player.cpp
 * @brief Soubor obsahující třídu reprezentující hráče hry.
 * @author Staněk Petr <xstane34@stud.fit.vutbr.cz>
 * @author Stejskal Jakub <xstejs24@stud.fit.vutbr.cz>
 */

#include "player.h"
#include "game.h"

const int MAX_HEURESTIC = 20; /**< minimální heuristika algoritmu */
const int MIN_HEURESTIC = -8; /**<  maximální heuristika algoritmu */

Player::Player(Game *game, FieldColor playerColor, PlayerType playerType, PlayerAlgorithm playerAlgorithm)
{
	cout << "Hráč: "<<playerColor<<" s algoritmem:" << playerAlgorithm<<endl;
	this->playerColor = playerColor;
	this->playerType = playerType;
	this->game = game;
	this->lastMove.x = MIN_HEURESTIC;
	this->lastMove.y = MIN_HEURESTIC;
	
	this->playerAlgorithm = playerAlgorithm;
	cout <<"break"<<endl;
	this->setAvalaibleStones(game->getBoard()->getBoardSize()*game->getBoard()->getBoardSize()/2-2);
	this->setOwnedStones(2);
	
}

Player::Player(Game *game, FieldColor playerColor, PlayerType playerType): Player(game, playerColor, playerType, ALG_NONE){}

void Player::putDisk(int x, int y)
{
	this->game->getBoard()->getField(x, y)->setColor(this->playerColor);
}



void Player::proccessMoveAIv1()
{
//	cout<<"Hraje počítač"<<endl;
	vector<Field*> boundedStones; // políčka ovlivněná tahem
	vector<Field*> bestStonesMove;
	FieldColor pc = game->getPlayerOnMove()->getColor();
	vector<Field*>::iterator iterSingleField;
	
	unsigned int sizeOfBiggestMove = 0; 
	
	// pro každý sloupec
	for (int x = 1; x <= this->game->getBoard()->getBoardSize(); x++) 
	{
		// pro každý řádek
		for (int y = 1; y <= this->game->getBoard()->getBoardSize(); y++)
		{
			// pokud je políčko prázdné
			if(this->game->getBoard()->getField(x,y)->getColor() == FieldColor::EMPTY)
			{
				// pokud je možné z daného políčka provést tah
				if(this->game->existsBoundedStone(x,y))
				{
					// získání políček ovlivněných tahem
					boundedStones = this->game->getAllBoundedStones(x,y);
					if(boundedStones.size() > sizeOfBiggestMove)
					{
						bestStonesMove = boundedStones;
						sizeOfBiggestMove = boundedStones.size();
					}					
				}				
			}
		}
	}	

	if(bestStonesMove.size() > 0)
	{
		this->game->getPlayerOnMove()->setLastMove((*bestStonesMove.begin())->getCoords()->y,(*bestStonesMove.begin())->getCoords()->x);
		//cout<<"Počítač "<<this->game->getPlayerOnMove()->formatPlayer("  ")<<" vložil kámen na: "<<this->game->getPlayerOnMove()->formatPlayer("["+to_string((*bestStonesMove.begin())->getCoords()->x)+":"+to_string((*bestStonesMove.begin())->getCoords()->y)+"]")<<endl;
		for(iterSingleField = bestStonesMove.begin(); iterSingleField != bestStonesMove.end(); iterSingleField++)
			(*iterSingleField)->setColor(pc);
		this->game->getPlayerOnMove()->setAvalaibleStones(this->game->getPlayerOnMove()->getAvalaibleStones()-1);
			
	}
}

void Player::proccessMoveAIv2()
{
	// vektor ukazatelů políček ovlivněných tahem
	vector<Field*> boundedStones;
	
	// získání barvy hráče na tahu
	FieldColor pc = this->game->getPlayerOnMove()->getColor();	
	
	int maxHeurestic = MIN_HEURESTIC; 
	int heuresticTMP = MIN_HEURESTIC;
	
	// pro každý sloupec
	for (int x = 1; x <= this->game->getBoard()->getBoardSize(); x++) 
	{
		// pro každý řádek
		for (int y = 1; y <= this->game->getBoard()->getBoardSize(); y++)
		{
			// pokud je políčko prázdné
			if(this->game->getBoard()->getField(x,y)->getColor() == FieldColor::EMPTY)
			{
				// pokud je možné z daného políčka provést tah
				if(this->game->existsBoundedStone(x,y))
				{
					// vyhodnocení výhodnosti tahu
					heuresticTMP = getMoveHeurestic(x,y);
					
					// pokud je větší než maximální heuristika
					if(heuresticTMP > maxHeurestic)
					{
						maxHeurestic = heuresticTMP;
						boundedStones = this->game->getAllBoundedStones(x,y); // políčka ovlivněná tahem
					}
				}					
			}	
		}			
	}	
	
	// pokud byl proveden tah
	if(boundedStones.size() > 0)
	{
		this->game->getPlayerOnMove()->setLastMove((*boundedStones.begin())->getCoords()->y,(*boundedStones.begin())->getCoords()->x);
		//cout<<"Počítač "<<this->game->getPlayerOnMove()->formatPlayer("  ")<<" vložil kámen na: "<<this->game->getPlayerOnMove()->formatPlayer("["+to_string((*boundedStones.begin())->getCoords()->x)+":"+to_string((*boundedStones.begin())->getCoords()->y)+"]")<<endl;
		// vybarvení dotčených políček
		for(vector<Field*>::iterator it = boundedStones.begin(); it != boundedStones.end(); it++)
			(*it)->setColor(pc);
		
		// po provedení tahu snížení počtu dostupných kamenů
		this->game->getPlayerOnMove()->decrementAvalaibleStones();
	}
}

int Player::getMoveHeurestic(int dx, int dy)
{
	int heurestic = 0; // hodnota heuristiky
	vector<Field*> boundedStones; // vektor ukazatelů políček ovlivněných tahem
	
	// souřadnice okolí bodu
	Coords array[8] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
	
	// simulace hrací desky
	vector<vector<int> > copyBoard(this->game->getBoard()->getBoardSize(), vector<int>(this->game->getBoard()->getBoardSize()));
	
	// pro každý sloupec
	for (int x = 0; x < this->game->getBoard()->getBoardSize(); x++) 
	{
		// pro každý řádek
		for (int y = 0; y < this->game->getBoard()->getBoardSize(); y++)
		{
			copyBoard[x][y] = this->game->getBoard()->getField(x+1,y+1)->getColor();
		}
	}	
	
	// získání políček ovlivněných tahem
	boundedStones = game->getAllBoundedStones(dx,dy);
	
	// procházení políček ovlivněných tahem a obarvení je barvou hráče na tahu
	for(vector<Field*>::iterator it = boundedStones.begin(); it != boundedStones.end(); it++)
	{
		copyBoard[(*it)->getCoords()->x-1][(*it)->getCoords()->y-1] = this->game->getPlayerOnMove()->getColor();
	}

	// procházení okolí bodu a zjištění okolí
	for(int i = 0; i < 8; i++)
	{
		if(this->game->getBoard()->isOnBoard(dx+array[i].x, dy+array[i].y))
		{
			// prázdné políčko
			if(copyBoard[dx-1+array[i].x][dx-1+array[i].y] == FieldColor::EMPTY)
				heurestic += 1;
			// políčko obsazené hráčem na tahu
			else if(copyBoard[dx-1+array[i].x][dx-1+array[i].y] == this->game->getPlayerOnMove()->getColor())
				heurestic += 1;
			// políčko obsazené protihráčem
			else if(copyBoard[dx-1+array[i].x][dx-1+array[i].y] == this->game->getOponent()->getColor())
				heurestic -= 1;
			// políčko v rohu desky
			else if(this->game->getBoard()->isOnCorner(dx,dy))
				heurestic = MAX_HEURESTIC;
		}
	}	
	// 8-4 ->  3-0 <-> 0-3 ->3-8
	return heurestic+2*boundedStones.size();
}

