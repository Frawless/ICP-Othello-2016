#*************************************************************
#       Projekt: Projekt do předmětu Seminář C++ (ICP)       * 
#                Hra2016 (Othello - Reversi)                 *
#        Autoři: Jakub Stejskal <xstejs24@stud.fit.vutbr.cz> *
#                Petr Staněk    <xstane34@stud.fit.vutbr.cz> *
# Název souboru: Makefile                                    *
#         Datum: 10. 03. 2016                                *
#         Verze: 1.0                                         *
#************************************************************/


# vstupní a výstupní názvy souborů archivu ZIP
PACK_NAME = xstejs24-xstane34
PACK_FILES = src/ examples/ doc/ Makefile Doxyfile README.txt

# cesta k souborům s dokumentací
DOC_FILE = doc/*

# nastavení překlače
CC = g++					# překladač
CFLAGS = -std=c++11 -Wall -pedantic -W -Wextra  # parametry překladu
LBOOST = -lboost_regex				# povolení boost regex


# názvy výsledných programů
PROGRAM_NAME1 = hra2016-cli		# ovládaný TUI
PROGRAM_NAME2 = hra2016			# ovládaný GUI

# cesty k souborům programu
SRC_FILES = $(shell find . -name *.cpp)	# zdrojové soubory
TMP_FILES = $(shell find . -name *.o)	# vzniklé dočasné objektové soubory
OBJ_FILES = $(SRC_FILES:%.cpp=%.o)

all: $(PROGRAM_NAME1)
$(PROGRAM_NAME1): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME1) $^ -lboost_regex  -lboost_serialization -lboost_filesystem

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $< -o $@
	
clean: 
	rm -f $(TMP_FILES) $(PACK_NAME).zip $(PROGRAM_NAME1)
	
pack:
	rm -f $(PACK_NAME).zip $(TMP_FILES) $(DOC_FILE)
	zip -r $(PACK_NAME).zip $(PACK_FILES)

	
doxygen:
	doxygen Doxyfile

run:
	./$(PROGRAM_NAME1)