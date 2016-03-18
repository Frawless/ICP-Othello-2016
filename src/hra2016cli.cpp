/*************************************************************
*       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
*                Hra2016 (Othello - Reversi)                 *
*        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
*                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
* Název souboru: hra2016cli.cpp                              *
*         Datum: 10. 03. 2016                                *
*         Verze: 1.0                                         *
**************************************************************/

/**
 * @file hra2016cli.cpp
 * @brief Soubor obsahující hlavní třídu aplikace ovládanou pomocí příkazové
 * řádky (CLI) a main
 * @author Staněk Petr <xstane34@stud.fit.vutbr.cz>
 * @author Stejskal Jakub <xstejs24@stud.fit.vutbr.cz>
 */

#include "hra2016cli.h"

hra2016cli::hra2016cli()
{
	this->state = NONE; // stav aplikace (hra běží/neběží/žádáno zadání algoritmu)
	this->game = NULL; // ukazatel na hru
}

void hra2016cli::startCLI()
{
	int c; // získaný znak
	stringstream command; // získaný příkaz
	bool end = false; // příznak ukončení čtení znaků (po zadání "exit" nebo "^C")
	bool showTerminalSign = true; // příznak pro (ne)zobrazení "Prompt>"
	
	cout << "\033[1;43m" << "Spuštěna hra Othello! Ovládejte pomocí CLI. Pro nápovědu zadejte h." << "\033[0m" << endl;
	
	system("stty -icanon -isig -echo"); // nastavení terminalu (čtení po písmenech, neodchytávat ^C, nevypisovat)
	
	// dokud je povoleno zadávat znaky (není zadán příkaz "exit" nebo "^C")
	while(!end) 
	{	
		// vypsání znaku terminálu
		if (showTerminalSign)
			cout << "\033[1;32mPříkaz>\033[0m";
		showTerminalSign = false; // znak vypsán a příště nezobrazovat
		
		// získání znaku
		c = getchar(); 
		
		// pokud znak začíná jako klávesa šipky
		if (char(c) == '\033') 
		{ 
			getchar(); // přeskočení jednoho znaku
			c = getchar(); // získání posledního
			if (char(c) >= 'A' && c <= 'D') // pokud opravdu klávesa
				processCommand((string)""+char(c));
			showTerminalSign = true;
		}
		// pokud stisknuto < nebo >
		else if (char(c) == '<' || char(c) == '>') 
		{
			processCommand((string)""+char(c));
			showTerminalSign = true;
		}
		// pokud stisknuto Ctrl+C (^C)
		else if (c == 3) 
		{
			end = processCommand("exit");
			cout << endl;
		}
		// pokud stisknuto Backspace
		else if (c == 127) 
		{
			cout << endl;
			command.str("");
			showTerminalSign = true;
		}
		// pokud stisknut enter
		else if (char(c) == '\n')
		{
			cout << endl;
			// pokud prázdný příkaz --> pouze enter
			if (command.str() == "")
				end = processCommand("enter");
			// jinak odeslání získaného příkazu
			else
				end = processCommand(command.str());
			
			command.str("");
			showTerminalSign = true;
		}
		// pokud jiný anglický znak nebo číslo (přibližně) -> apendování příkazu
		else if ((char(c) >= '0' && char(c) <= 'z') || char(c) == ' ')
		{
			command << (string)""+char(c);
			cout << (string)""+char(c);
		}
	}
	system("stty cooked echo"); // obnovení původního nastavení terminalu
}

bool hra2016cli::processCommand(string command)
{ 
	bool end = false; // příznak ukončení čtení znaků (po zadání "exit" nebo "^C")
	boost::cmatch subStr; // pole s částmi příkazu rozparsovaného regexem 
	
	// konec programu
	if(command == "exit")	
	{ 
		cout << "\033[1;34m" << "Program ukončen." << "\033[0m" << endl;
		quitGame();
		end = true;
	}		
	// výpis nápovědy
	else if(command == "h" || command == "help")
		this->showHelp();
	// blok podmínek pro příkazy s "podnabídkou" ===============================
	// volba algoritmu počítače
	else if (this->state == ASKING_FOR_ALGORITHM)
	{	// spuštění hry
		if (command == "1") // pro první algoritmus
			this->newGame(this->tmpBoardSize, tmpPlayerType, Player::ALG1);
		if (command == "2") // pro druhý algoritmus
			this->newGame(this->tmpBoardSize, tmpPlayerType, Player::ALG2);
		// ukončení programu
		else if(command == "exit")
			end = true;
		// jinak zopakování hlášení
		else 
			cout << "\033[1;34m" << "Zvolte algoritmus: jednodušší: 1, složitější: 2" << "\033[0m" << endl;
	}
	// nahrání uložené hry
	else if(command == "load" || this->state == LOADING_GAME)
	{ 
		// získání uložených her
		Game::TGamesList savedGames = Game::getSavedGames();
		
		// volba hry ze seznamu
		if (this->state == LOADING_GAME && boost::regex_match(command.c_str(), subStr, boost::regex ("^([0-9]*)$")) &&
			 stoi(string(subStr[1])) > 0 && stoi(string(subStr[1])) <= int(savedGames.size()))
		{
			cout << "\033[1;34m" << "Nahrána uložená hra: " << command << "\033[0m" << endl;
			this->quitGame(); // ukončení případné již běžící hry
			int i = 1; // pořadí hry v seznamu
			// procházení seznamu uložených her
			for (Game::TGamesList::iterator it = savedGames.begin(); it!=savedGames.end(); ++it, i++)
			{
				if (stoi(string(command)) == i) // pokud se požadovaná hra shoduje se hrou v seznamu
					this->game = Game::getSavedGame((*it).second.string()); // načtení zvolené hry
			}
			this->state = RUNNING;
			this->showBoard();
		}
		// výpis seznamu uložených her
		else
		{	
			cout << "\033[1;34m" << "Nahrání uložené hry. Zvolte číslo hry ze seznamu: " << "\033[0m" << endl;
			
			char formatedDate[128];
			int i = 1;
			// procházení seznamu uložených her
			for (Game::TGamesList::iterator it = savedGames.begin(); it!=savedGames.end(); ++it, i++)
			{
				// zformátování data
				strftime(formatedDate, sizeof(formatedDate), " %d.%m.%Y %H:%M:%S", std::localtime(&((*it).first)));
				cout << i << ": " << string(formatedDate) << " (" << (*it).second.stem().string() << ")" << endl;
			}
			this->state = LOADING_GAME;
		}
	}
	// uložení hry
	else if((this->state == RUNNING && command == "save") || this->state == SAVING_GAME)	
	{
		// pokud zadán název ukládané hry
		if (this->state == SAVING_GAME && boost::regex_match(command.c_str(), subStr, boost::regex ("([A-Za-z0-9_-]+)")))
		{
			cout << "\033[1;34m" << "Aktuální hra uložena pod jménem: " << string(subStr[1]) << "\033[0m" << endl;
			this->game->save(string(subStr[1]));
			this->state = RUNNING;
		}
		// jinak zopakování hlášení
		else
		{	
			cout << "\033[1;34m" << "Zadejte název hry: " << "\033[0m" << endl;
			this->state = SAVING_GAME;
		}
	}
	// blok podmínek, pokud hra běží ===========================================
	// posun kurzoru
	else if(this->state == RUNNING && command == "A") // nahorů 
		this->moveCursor(Board::UP);	
	else if(this->state == RUNNING && command == "B") // dolů 
		this->moveCursor(Board::DOWN);
	else if(this->state == RUNNING && command == "C") // vpravo 	
		this->moveCursor(Board::RIGHT);
	else if(this->state == RUNNING &&  command == "D") //  vlevo 
		this->moveCursor(Board::LEFT);
	
	// položení kamene na místo kurzoru
	else if(this->state == RUNNING && command == "enter")	
		this->putDisk();
	
	// krok v historii vzad
	else if(this->state == RUNNING && command == "<")	
	{ 		
		if (this->game->undoHistory())
			cout << "\033[1;34m" << "Proveden krok vzad." << "\033[0m" << endl;
		else
			cout << "\033[1;34m" << "Historie vyčerpána." << "\033[0m" << endl;

		this->showBoard();
	}
	// krok v historii vpřed
	else if(this->state == RUNNING && command == ">")
	{ 
		if (this->game->redoHistory())
			cout << "\033[1;34m" << "Proveden rok vpřed." << "\033[0m" << endl;
		else
			cout << "\033[1;34m" << "Historie vyčerpána." << "\033[0m" << endl;
		
		this->showBoard();
	}
	// ukončení hry
	else if(this->state == RUNNING && command == "quit")
		this->quitGame();
	
	// blok podmínek, pokud hra nemusí běžet ===================================
	// spuštění nové hry (implicitní velikost desky 8)
	else if(boost::regex_match(command.c_str(), subStr, boost::regex ("n (p|c)")))
	{
		this->tmpBoardSize = Game::DEFAULT_BOARD_SIZE;
		this->tmpPlayerType = string(subStr[1]) == "p" ? Player::PERSON : Player::COMPUTER;
		
		// pokud je protihráč počítač -> vyžadovat zvolení algoritmu
		if (this->tmpPlayerType == Player::COMPUTER)
		{
			cout << "\033[1;34m" << "Zvolte algoritmus: jednodušší: 1, složitější: 2" << "\033[0m" << endl;
			this->state = ASKING_FOR_ALGORITHM;
		}
		// jinak rovnou spustit hru
		else
			this->newGame(this->tmpBoardSize, tmpPlayerType, Player::ALG_NONE);
		
	}
	// spuštění nové hry (volena velikost desky)
	else if(boost::regex_match(command.c_str(), subStr, boost::regex ("n (6|8|10|12) (p|c)")))
	{
		this->tmpBoardSize = stoi(string(subStr[1])); // velikost desky
		this->tmpPlayerType = string(subStr[2]) == "p" ? Player::PERSON : Player::COMPUTER; // protihráč
		
		// pokud je protihráč počítač -> vyžadovat zvolení algoritmu
		if (this->tmpPlayerType == Player::COMPUTER)
		{
			
			cout << "\033[1;34m" << "Zvolte algoritmus: jednodušší: 1, složitější: 2" << "\033[0m" << endl;
			this->state = ASKING_FOR_ALGORITHM;
		}
		else // jinak rovnou spustit hru
			this->newGame(this->tmpBoardSize, tmpPlayerType, Player::ALG_NONE);
	}
	
	else
		cout << "\033[1;91m" << "Neznámý příkaz: '" << command << "'. Pro nápovědu zadejte písmeno 'h'" << "\033[0m" << endl;	   
	
	return end;
}

void hra2016cli::newGame(int boardSize, Player::PlayerType playerType, Player::PlayerAlgorithm playerAlgorithm)
{
	// výpis akcí příkazu
	cout << "\033[1;34m";
	cout << "Spuštěna nová hra. Velikost desky: " << boardSize;
	cout << ", protihráč: ";
	cout << (playerType == Player::COMPUTER ? "počítač." : "člověk.");
	cout << "\033[0m" << endl;	
	
	this->quitGame(); // ukončí případnou běžící hru
	this->state = RUNNING; // stav programu - hra běží
	this->game = new Game(boardSize, playerType, playerAlgorithm); // spuštění hry
	this->game->saveHistory(); // uložení stavu hry (ihned po spuštění)
	this->revalidate();	// vyhodnotit možné tahy a znovu vykreslit hru
}

void hra2016cli::putDisk()
{
	// provedení tahu
	bool isMoved = this->game->processMove(false); // aktualizovat hru (false - pokud možno, táhnout)
	
	// zobrazení stavu hry
	this->showState();
	
	// zobrazení hrací desky
	this->showBoard();

	// pokud nebylo taženo nebo bylo taženo a další tahy neexistují
	if(!isMoved || (isMoved && !this->game->getMoves()))
	{
		this->showResults(); // zobrazení výsledků hry
		hra2016cli::quitGame(); // ukončit hru	
	}
//	else
//		this->game->saveHistory(); // uloží hru ???
}

void hra2016cli::moveCursor(Board::MoveDirection direction)
{
	this->game->getBoard()->moveCursor(direction); // posune kurzor daným směrem
	this->revalidate(); // vyhodnotit možné tahy a znovu vykreslit hru
}

void hra2016cli::quitGame()
{
	this->state = hra2016cli::NONE; // stav programu - hra neběží
	if (this->game != NULL) // pokud hra běžela
	{
		cout << "\033[1;43m" << "Aktuální hra ukončena." << "\033[0m" << endl;
		this->game->~Game();
		this->game = NULL;
	}
}

void hra2016cli::showHelp()
{
	cout << "\033[1;34m" << "Zobrazuji nápovědu" << "\033[0m" << endl;

	cout << "\033[1m" << "Vysvětlivky" << "\033[0m" << endl;
	cout << "\033[32m<velikost>\033[0m \t\t velikost desky 6, 8, 10 nebo 12" << endl;
	cout << "\033[32m<soupeř>\033[0m \t\t p (člověk) nebo c (počítač)" << endl;

	cout << endl << "\033[1m" << "Příkazy" << "\033[0m" << endl;
	cout << "\033[32mh\033[0m \t\t\t tato nápověda" << endl;
	cout << "\033[32mn <soupeř>\033[0m \t\t spuštění hry (velikost desky 8)" << endl;
	cout << "\033[32mn <velikost> <soupeř>\033[0m \t spuštění hry" << endl;
	cout << "\033[32mšipky\033[0m \t\t\t posun kurzoru" << endl;
	cout << "\033[32mEnter\033[0m \t\t\t umístění kamene (běží-li hra)" << endl;
	cout << "\033[32m<\033[0m \t\t\t krok vzad  (běží-li hra)" << endl;
	cout << "\033[32m>\033[0m \t\t\t krok vpřed (běží-li hra)" << endl;
	cout << "\033[32msave\033[0m \t\t\t uložení hry (běží-li hra)" << endl;
	cout << "\033[32mload\033[0m \t\t\t načtení uložené hry" << endl;
	cout << "\033[32mquit\033[0m \t\t\t ukončení hry (běží-li hra)" << endl;
	cout << "\033[32mexit\033[0m \t\t\t ukončení celého programu" << endl;
}


void hra2016cli::showBoard()
{
	Board *board = this->game->getBoard(); // hrací deska
	
	// pro každý sloupec (včetně horní hrany y == 0)
	for (int y = 0; y <= board->getBoardSize(); y++) 
	{
		// pro každý řádek (včetně levé hrany x == 0)
		for (int x = 0; x <= board->getBoardSize(); x++)
		{	
			// vygenerování rastru (šachovnice)
			// levý horní roh - prázdno
			if (x == 0 && y == 0)
				cout << "  ";
			// levá hrana (1-12)
			else if (x == 0)
			{
				cout << y;
				if (y < 10)
					cout << " ";
			}
			// horní hrana (A-L)
			else if (y == 0)
				cout << char('A'-1+x) << " ";
			// plocha hry
			else
			{
				// barva v místě kurzoru
				if (x == board->getCursor()->x && y == board->getCursor()->y)
					cout << "\033[4m";
				
				// zvýraznění políčka přípustného tahu
				if (board->getField(x, y)->isHighlight())
					cout << this->game->getPlayerOnMove()->formatPlayer("xx");
				// nastavení barvy hráče BLACK
				else if (board->getField(x, y)->getColor() == Field::BLACK)
					cout << "\033[41m" << "  " << "\033[0m";
				// nastavení barvy hráče WHITE
				else  if (board->getField(x, y)->getColor() == Field::WHITE) 
					cout << "\033[43m" << "  " << "\033[0m";
				// v ostatních případech vygenerování rastru (šachovnice)
				else
				{
					if ((x+y+board->getBoardSize()) % 2 == 0)
						cout << "\033[40m" << "  " << "\033[0m";
					else
						cout << "\033[100m" << "  " << "\033[0m";
				}

				// konec barvy v místě kurzoru
				if (x == board->getCursor()->x && y == board->getCursor()->y)
					cout << "\033[0m";
			}
		}
		cout << endl;		
	}
}

void hra2016cli::showState()
{
	cout<<"Poslední x: "<<this->game->getFirstPlayer()->getLastMove().x<<endl; // kontrílní vypis pro undo
	if(this->game->getFirstPlayer()->getLastMove().x > 0)
	{
		stringstream tmpChar;
		string tmpString;
		tmpChar << char('A'-1+this->game->getOponent()->getLastMove().x);
		tmpChar >> tmpString;
		
		if(this->game->getSecondPlayer()->getPlayerType() == Player::COMPUTER)
		{
			if(this->game->getPlayerOnMove()->getPlayerType() == Player::COMPUTER)
				cout<<"Hráč "<<this->game->getOponent()->formatPlayer("  ")<<" vložil kámen na: "<<this->game->getOponent()->formatPlayer("["+tmpString+":"+to_string(this->game->getOponent()->getLastMove().y)+"]")<<endl;
			else
				cout<<"Počítač "<<this->game->getOponent()->formatPlayer("  ")<<" vložil kámen na: "<<this->game->getOponent()->formatPlayer("["+tmpString+":"+to_string(this->game->getOponent()->getLastMove().y)+"]")<<endl;
		}
		else
		{
			cout<<"Hráč "<<this->game->getOponent()->formatPlayer("  ")<<" vložil kámen na: "<<this->game->getOponent()->formatPlayer("["+tmpString+":"+to_string(this->game->getOponent()->getLastMove().y)+"]")<<endl;
		}
	}
	cout << "Hráč na tahu: " << this->game->getPlayerOnMove()->formatPlayer("  ") << " | Počet zbývajících kamenů: " << this->game->getPlayerOnMove()->formatPlayer(to_string(this->game->getPlayerOnMove()->getAvalaibleStones()))<< endl;
	
	cout << "Skóre: ";
	cout << this->game->getFirstPlayer()->formatPlayer(to_string(this->game->getFirstPlayer()->getOwnedDisks())) << ":";
	cout << this->game->getSecondPlayer()->formatPlayer(to_string(this->game->getSecondPlayer()->getOwnedDisks())) << endl;	
}

void hra2016cli::showResults()
{
	int nEmptyFields = 0; // počet nevyplněných políček
	int nFields = this->game->getBoard()->getBoardSize()*this->game->getBoard()->getBoardSize(); // počet vyplěných políček
	int nFirstPlayerDisks = this->game->getFirstPlayer()->getOwnedDisks(); // počet kamenů 1. hráče
	int nSecondPlayerDisks = this->game->getSecondPlayer()->getOwnedDisks(); // počet kamenů 2. hráče
	
	// zjištění počtu nevyplněných políček
	if(nFirstPlayerDisks + nSecondPlayerDisks < nFields)
		nEmptyFields = nFields - nFirstPlayerDisks - nSecondPlayerDisks;

	if (this->game->getWinner()->getColor() == this->game->getFirstPlayer()->getColor())
		nFirstPlayerDisks += nEmptyFields;
	else
		nSecondPlayerDisks += nEmptyFields;
		
	cout << this->game->getFirstPlayer()->formatPlayer("  ") << " -> " << nFirstPlayerDisks << endl;
	cout << this->game->getSecondPlayer()->formatPlayer("  ") << " -> " << nSecondPlayerDisks << endl;
	
	cout << "Vyhrál " << this->game->getWinner()->formatPlayer("  ") << endl;
}

void hra2016cli::testGame()
{
	/* nejlépe nastavit větší délku záznamu u terminalu (v nastavení programu)
	 * vlevo (D), vpravo (C), nahoru (A), dolu (B),
	 * potvrzení/položení kamene (enter)
	 * historie (</>)
	 * save/load
	 * quit/exit
	 */
	string test1[] = {"n c", "1", "B", "enter", "<", "enter"};
	
	for(const string &text : test1)
	{
		cout << endl << "Test action: " << text << endl;
	}
}

void hra2016cli::revalidate()
{
	// vyhodnocení možných tahů dle pozice kurzoru
	(void)this->game->processMove(true);
	
	// zobrazení stavu hry	
	this->showState();
	
	// zobrazení hrací desky
	this->showBoard();

	/* ??? odtud odstraněna reakce na isMoved vracené processMove(true),  -> podle toho co jsem zatím viděl tak snad ne
	 * které zobrazuje výsledky a ukončuje hru - nově revalidate jen po spuštění,
	 * posunu kurzoru, při putDisk je výše uvedený kód odlišný, nevadí to ničemu
	 */
}

/**
 * Main aplikace hry ovládané pomocí CLI.
 * @param argc počet zadaných argumentů
 * @param argv hodnoty zadaných argumentů
 * @return návratová hodnota programu
 */
int main(int argc, char** argv) 
{
	(void)argc;
	(void)argv;
	
	// spuštění programu ovládaného CLI
	hra2016cli *hra = new hra2016cli();
	
	// spuštění textového menu CLI
	//hra->testGame(); // zakomentovat startCLI()
	hra->startCLI(); 
	
	return 0;
}
