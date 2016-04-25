/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: game.cpp                                      *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

/**
 * @file game.cpp
 * @brief Soubor obsahující třídu představující hlavní logiku aplikace. 
 * @author Staněk Petr <xstane34@stud.fit.vutbr.cz>
 * @author Stejskal Jakub <xstejs24@stud.fit.vutbr.cz>
 */

#include "game.h"

Game::Game(int boardSize, PlayerType secondPlayerType, PlayerAlgorithm playerAlgorithm)
{
	// vytvoření hrací desky
	this->board = new Board(boardSize);	
	
	// inicializace hráčů
	this->firstPlayer = new Player(this,  FieldColor::BLACK, PlayerType::PERSON);
	this->secondPlayer = new Player(this, FieldColor::WHITE, secondPlayerType, playerAlgorithm);
	this->playerAlgorithm = playerAlgorithm;
	
	// inicializace hráče na tahu (napevno první - vždy člověk)
	this->playerOnMove = this->firstPlayer;
}

bool Game::processMove(bool onlyHighlight)
{
	bool end = false; // příznak !!! čeho - to příznak si sem dal ty, je to návratová hodnota, aby se to nevracelo rovnou kvůli ovření dalších tahů jsem to takudělal
	
	// získání souřadnic kurzoru
	int x = this->getBoard()->getCursor()->x;
	int y = this->getBoard()->getCursor()->y;
	
	// vymazání předchozího zvýraznění možného tahu
	this->getBoard()->clearHighlights(); 
	
	// pokud není možné provést jakýkoliv tah
	if(!this->isAnyMovePossible())
		return end;
	else
		end = true;
	
	// provedení tahu počítačem (je-li počítač)
	this->processAIMove(); 
	
	// pokud hráč na tahu k nemá dispozici kameny
	if(this->playerOnMove->getAvalaibleStones() == 0)
	{		
		// pokud ani aktuální protihráč nemá dispozici kameny
		if(this->getOponent()->getAvalaibleStones() == 0)
		{
			end = false;
		}
		// pokud aktuální protihráč má dispozici kameny
		else
		{
			this->swapPlayers(); // další hráč jde na tah
			this->processAIMove(); // provedení tahu počítačem (je-li počítač)
			end = true;
		}
	}
	// pokud je možné z daného políčka táhnout a políčko je prázdné, pak je možné provést tah
	else if(this->existsBoundedStone(x,y) && this->board->getField(x,y)->getColor() == FieldColor::EMPTY)
	{
		// získání všech políček ovlivněných tahem
		vector<Field*> boundedFields = getAllBoundedStones(x, y);
		
		// získání barvy hráče na tahu
		FieldColor pc = this->getPlayerOnMove()->getColor();

		// pouze zvýraznit možný tah, netáhnout
		if (onlyHighlight)
		{
			// nastavit zvýraznění políček ovlivněných tahem
			for(vector<Field*>::iterator it = boundedFields.begin(); it != boundedFields.end(); it++)
				(*it)->setHighlight();
		}
		// provést tah
		else
		{
			// uložení posledního tahu
			this->playerOnMove->setLastMove(x,y);
						
			// umístění dalších kamenů na odpovídající přilehlá přivlastněná políčka
			for(vector<Field*>::iterator it = boundedFields.begin(); it != boundedFields.end(); it++)
				(*it)->setColor(pc);
			
			// snížení počtu dostupných kamenů hráče (právě jeden položil)
			this->playerOnMove->decrementAvalaibleStones();
			
			this->swapPlayers(); // další hráč jde na tah
			// !!!SAVE
			this->saveHistory();			
			this->processAIMove(); // provedení tahu počítačem (je-li počítač)
			// !!!SAVE
			if(this->getSecondPlayer()->getPlayerType() == PlayerType::COMPUTER)
				this->saveHistory();
		}		
	}
	this->getScore();
	return end;
}

vector<Game::Coords> Game::getPossibleWays(int x, int y)
{
	vector<Coords> possibleWaysVector; // vektor možných cest tahu
	
	// souřadnice okolí bodu
	Coords array[8] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
	
	// procházení okolí bodu a zjišťování, zda je na desce
	for(int i = 0; i < 8; i++)
	{
		// tah je možný pokud barva sousedícího políčka je odlišná, než hráče na tahu (!!! ano)
		if(this->getBoard()->isOnBoard(x+array[i].x, y+array[i].y) && this->getBoard()->getField(x+array[i].x, y+array[i].y)->getColor() == this->getOponent()->getColor())
			possibleWaysVector.push_back(array[i]);		
	}
	return possibleWaysVector;
}

vector<Field*> Game::getBoundedStones(int x, int y, int dx, int dy)
{
	vector<Field *> boundedStones; // vektor políček ovlivněných tahem
	
	// pokud políčko není prázdné -> vrať prázdný vektor
	if(!(this->getBoard()->getField(x,y)->getColor() == FieldColor::EMPTY))
		return boundedStones;
	
	// vložení políčka pod kuzorem do vektoru
	boundedStones.push_back(this->getBoard()->getField(x, y));	

	x += dx;
	y += dy;
	
	// dokud políčko leží na desce a má barvu protihráče
	while(this->getBoard()->isOnBoard(x,y) && this->getBoard()->getField(x,y)->getColor() == this->getOponent()->getColor())
	{
		boundedStones.push_back(this->getBoard()->getField(x,y));	
		x += dx;
		y += dy;		
	}
	
	// pokud políčko leží na desce a má barvu hráče na tahu
	if(this->getBoard()->isOnBoard(x,y) && this->getBoard()->getField(x,y)->getColor() == this->playerOnMove->getColor())	
		boundedStones.push_back(this->getBoard()->getField(x,y));
	else
		boundedStones.clear();

	return boundedStones;
}

bool Game::existsBoundedStone(int x, int y)
{
	vector<Coords> possibleWays = this->getPossibleWays(x,y);
	
	// postupné procházení směrů 
	for(vector<Coords>::iterator it = possibleWays.begin(); it != possibleWays.end(); it++)
	{
		if(getBoundedStones(x, y, (*it).x, (*it).y).size() > 0)
			return true;
	}
	return false;
}

vector<Field*> Game::getAllBoundedStones(int x, int y)
{
	vector<Field*> allBoundedStones; /// vector polí, které se budou obarvovat ve všech směrech z bodu
	vector<Field*> boundedStones; /// vector polí, které se budou obarvovat v jednom směru

	vector<Coords> possibleWays = this->getPossibleWays(x,y);
	
	// postupné procházení směrů z daného bodu a vyhledávání políček, která se budou obarvovat
	for(vector<Coords>::iterator it = possibleWays.begin(); it != possibleWays.end(); it++)
	{
		boundedStones = getBoundedStones(x, y, (*it).x, (*it).y);
		allBoundedStones.reserve(allBoundedStones.size() + distance(boundedStones.begin(),boundedStones.end()));
		allBoundedStones.insert(allBoundedStones.end(), boundedStones.begin(), boundedStones.end());
	}
	return allBoundedStones;
}

void Game::swapPlayers()
{
	// uložení protihráče na místo hráče na tahu
	this->playerOnMove = this->getOponent();	
}

void Game::processAIMove()
{
	// pokud hráč na tahu je počítač
	if(this->playerOnMove->getPlayerType() == PlayerType::COMPUTER)
	{
		// pokud je zvolen první algoritmus
		if(this->playerAlgorithm == PlayerAlgorithm::ALG1)
			this->firstPlayer->proccessMoveAIv1();
		
		// pokud je zvolen první druhý
		else 
			this->firstPlayer->proccessMoveAIv2();
		
		this->swapPlayers(); // další hráč jde na tah
	}	
}

Player* Game::getOponent()
{
	if(this->playerOnMove->getColor() == this->firstPlayer->getColor())
		return this->secondPlayer;
	else
		return this->firstPlayer;
}

bool Game::getMoves()
{
	bool isAnyMovePossible = false; // pokud je nějaké políčko prázdné a je možné z něj provést nějaký tah

	// pro každý sloupec
	for (int x = 1; x <= this->getBoard()->getBoardSize(); x++) 
	{
		// pro každý řádek
		for (int y = 1; y <= this->getBoard()->getBoardSize(); y++)
		{
			// pokud je políčko prázdné
			if(this->getBoard()->getField(x,y)->getColor() == FieldColor::EMPTY)
			{
				// pokud je možné z políčka provést nějaký tah
				if(this->existsBoundedStone(x,y))
					isAnyMovePossible = true;							
			}
		}
	}
	return isAnyMovePossible;
}

bool Game::isAnyMovePossible()
{
	// pokud hráč na tahu k nemá dispozici kameny
	if(this->playerOnMove->getAvalaibleStones() != 0)
	{
		// pokud je možný nějaký tah
		if(!this->getMoves())
		{
			this->swapPlayers(); // další hráč jde na tah
			
			// pokud ani druhý hráč na nemá dispozici kameny
			if(this->playerOnMove->getAvalaibleStones() == 0 || !this->getMoves())
			{
				return false;
			}
			this->swapPlayers();
		}	
		return true;
	}
	else
	{
		this->swapPlayers(); // další hráč jde na tah	
		// pokud ani druhý hráč na nemá dispozici kameny
		if(this->playerOnMove->getAvalaibleStones() == 0 || !this->getMoves())
		{
			return false;
		}
		this->swapPlayers();
		return true;
	}
}

Player* Game::getWinner()
{
	// pokud první hráč má více kamenů než druhý
	if(this->getFirstPlayer()->getOwnedDisks() > this->getSecondPlayer()->getOwnedDisks()) 		
		return this->getFirstPlayer();
	else
		return this->getSecondPlayer();
}

void Game::saveHistory()
{	
	cout<<"Uložení historie"<<endl;
	if(this->firstPlayer->getAvalaibleStones() == 30)
	{
		
	}
	// uložení stavu hry
    {
		stringstream ssGame; // stream s uloženou hrou
		boost::archive::text_oarchive oa(ssGame);
        oa << this->firstPlayer << this->secondPlayer << this->playerAlgorithm << this->playerOnMove << this->board;
		
		if(this->firstPlayer->getAvalaibleStones() == 30)
		{
			this->initState = ssGame.str();
		}		
		else
		{
			// vložení do undo
			this->undo.push_back(ssGame.str());
			cout<<"Size of undo "<<this->undo.size()<<endl;
			this->redo.clear();			
		}
		
    }	
}

bool Game::undoHistory()
{
	cout << "<undo>" << endl;
	// pokud nejsou žadné kroky undo nebo je pouze uchován počáteční stav hry
	if (this->undo.empty())
		return false;
    		
//	// pokud nebyl ještě proveden žádný krok
//	if (this->redo.empty() && this->undo.size() > 1) 
//	{
//		// !!! tady bude nejspíš trošku roblém, bude se asi mazat něco co nemá, ráno dodělám, teď tu usínám, o půl 9 byh tu měl být
//		// přeskočení počátečního stavu hry
//		this->redo.push_back(this->undo.back());
//		this->undo.pop_back();
//	}
	
	{	
		stringstream ssGame; // stream s uloženou hrou
		if(this->undo.size() == 1)
		{
			ssGame << this->initState;
		}
		else
		{
			ssGame << this->undo.back(); // načtení stavu hry
		}

		boost::archive::text_iarchive ia(ssGame);
		ia >> this->firstPlayer >> this->secondPlayer >> this->playerAlgorithm >> this->playerOnMove >> this->board;
		// přesunout do redo
		this->redo.push_back(this->undo.back());
		this->undo.pop_back();
    }
		cout << "barva políčka 4/6: "<<this->getBoard()->getField(4,6)->getColor()<<endl;
		cout << "barva políčka 4/6: "<<this->getBoard()->getField(5,6)->getColor()<<endl;
	cout << "<undo2>" << endl;
	cout << "<undo> size: "<<this->undo.size() << endl;
	cout << "<redo> size: "<<this->redo.size() << endl;	
	for (int x = 1; x <= this->getBoard()->getBoardSize(); x++) 
	{
		// pro každý řádek
		for (int y = 1; y <= this->getBoard()->getBoardSize(); y++)
		{
			cout<<this->getBoard()->getField(y,x)->getColor()<<" ";
		}
		cout<<endl;
	}	
	return true;
}

bool Game::redoHistory()
{
	cout << "<redo>" << endl;
	// pokud nejsou žadné kroky redo
	if (this->redo.empty())
		return false;
    		
//	// pokud byly provedeny všechny kroky
//	if (this->undo.empty())
//	{
//		// přeskočení počátečního stavu programu
//		this->undo.push_back(this->redo.back());
//		this->redo.pop_back();
//	}
	
	{	
		stringstream ssGame; // stream s uloženou hrou
		ssGame << this->redo.back(); // načtení stavu hry
		boost::archive::text_iarchive ia(ssGame);
		ia >> this->firstPlayer >> this->secondPlayer >> this->playerAlgorithm >> this->playerOnMove >> this->board;
		
		// přesunout do undo
		this->undo.push_back(this->redo.back());
		this->redo.pop_back();
    }
	cout << "barva políčka 4/6: "<<this->getBoard()->getField(4,6)->getColor()<<endl;
	cout << "barva políčka 4/6: "<<this->getBoard()->getField(5,6)->getColor()<<endl;
	cout << "<redo2>" << endl;
	cout << "<undo> size: "<<this->undo.size() << endl;
	cout << "<redo> size: "<<this->redo.size() << endl;	
	for (int x = 1; x <= this->getBoard()->getBoardSize(); x++) 
	{
		// pro každý řádek
		for (int y = 1; y <= this->getBoard()->getBoardSize(); y++)
		{
			cout<<this->getBoard()->getField(x,y)->getColor()<<" ";
		}
		cout<<endl;
	}		
	return true;
}

void Game::save(string name)
{
	Game *game = this;
	cout <<"\033[1;43m" << "Aktuální hra uložena." << "\033[0m" << endl;
	
	// vytvoření streamu hry na základě cesty k ní
	ofstream ofs("./savedGames/"+name+".game");

    // uložení hry do souboru
    {
        boost::archive::text_oarchive oa(ofs);
        oa << game;
    }	
}

Game *Game::getSavedGame(string path)
{
	// načtení uložené hry a stavu programu ze souboru
    {
        Game *game;
		ifstream ifs(path);
        boost::archive::text_iarchive ia(ifs);
        ia >> game;
		
		// uložení historie počátečního stavu hry
		game->saveHistory();	
		return game;
    }
}

Game::TGamesList Game::getSavedGames()
{
	namespace fs = boost::filesystem;
	
	// cesta do adresáře s uloženými hrami
	fs::path dirPath("./savedGames/");
	
	// iterátor na konec adresáře
	fs::directory_iterator it_end;

	// získaný seznam her
	TGamesList gamesList;

	// postupné procházení adresáře
	if (fs::exists(dirPath) && fs::is_directory(dirPath))
	{
		for(fs::directory_iterator it(dirPath); it != it_end ; ++it)
		{
			if (fs::is_regular_file(it->status()) && fs::extension(*it) == ".game")
				gamesList.insert(TGamesList::value_type(fs::last_write_time(it->path()), *it));
		}
	}

	// odstranění starších her (11. a starší)
	int i = 1;
	for (TGamesList::iterator it = gamesList.begin(); it!=gamesList.end(); i++)
	{
		if (i > 10)
		{
			remove((*it).second.c_str());
			gamesList.erase(it++);
		}
		else
			it++;
	}
	return gamesList;
}

void Game::getScore()
{
	int firstPlayerOwnedStones = 0;
	int secondPlayerOwnedStones = 0;
// pro každý sloupec
	for (int x = 1; x <= this->getBoard()->getBoardSize(); x++) 
	{
		// pro každý řádek
		for (int y = 1; y <= this->getBoard()->getBoardSize(); y++)
		{
			// pokud je políčko obsazeno 1. hráčem
			if(this->getBoard()->getField(x,y)->getColor() == this->getFirstPlayer()->getColor())
				firstPlayerOwnedStones++; // výpočet počtu kamenů získaných 1. hráčem

			// pokud je políčko obsazeno 2. hráčem
			else if(this->getBoard()->getField(x,y)->getColor() == this->getSecondPlayer()->getColor())
				secondPlayerOwnedStones++; // výpočet počtu kamenů získaných 2. hráčem
		}
	}
	this->getFirstPlayer()->setOwnedStones(firstPlayerOwnedStones);
	this->getSecondPlayer()->setOwnedStones(secondPlayerOwnedStones);	
}