#*************************************************************
#       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
#                Hra2016 (Othello - Reversi)                 *
#        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
#                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
# Název souboru: Makefile                                    *
#         Datum: 10. 03. 2016                                *
#         Verze: 1.0                                         *
#************************************************************/

#SRC

# nastavení překlače
CC = g++					# překladač
CFLAGS = -std=c++11 -Wall -pedantic -W -Wextra  # parametry překladu
LBOOST = -lboost_regex				# povolení boost regex

# názvy výsledných programů
PROGRAM_NAME1 = ../hra2016-cli		# ovládaný TUI
PROGRAM_NAME2 = ../hra2016			# ovládaný GUI

# cesty k souborům programu
SRC_FILES_CLI = logic/*.cpp logic/*.h hra2016cli.cpp hra2016cli.h
OBJ_FILES_CLI = logic/game.o logic/field.o logic/board.o logic/player.o hra2016cli.o
OBJ_FILES_GUI = logic/game.o logic/field.o logic/board.o logic/player.o GUI/board.o GUI/field.o GUI/mainwindow.o hra2016.o 
	
all: $(PROGRAM_NAME1) 
#$(PROGRAM_NAME2)
$(PROGRAM_NAME1): $(OBJ_FILES_CLI)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME1) $^ -lboost_regex  -lboost_serialization -lboost_filesystem
	@echo -e "\033[92mVytvořen soubor \033[93mhra2016-cli\033[0m"
#$(PROGRAM_NAME2): $(OBJ_FILES_GUI)	
#	$(CC) $(CFLAGS) -o $(PROGRAM_NAME1) $^ -lboost_regex  -lboost_serialization -lboost_filesystem
#	@echo -e "\033[92mVytvořen soubor \033[93mhra2016\033[0m"
	
%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $< -o $@
