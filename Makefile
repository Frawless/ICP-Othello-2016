#Makefile

CC = g++
CFLAGS = -std=c++11 -Wall -pedantic -W -Wextra  
LOGIN = xstejs24-xstane34
PROJ_NAME = hra2016cli
PACK = src/ examples/ doc/ Makefile Doxyfile README.txt
DOCRM = doc/*

SRC = $(shell find . -name *.cpp)
DEL = $(shell find . -name *.o)
OBJ = $(SRC:%.cpp=%.o)

all: $(PROJ_NAME)
$(PROJ_NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(PROJ_NAME) $^ -lboost_regex

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $< -o $@
	
clean: 
	rm -f $(DEL) $(LOGIN).zip $(PROJ_NAME)
	
pack:
	rm -f $(LOGIN).zip $(DEL) $(DOCRM)
	zip -r $(LOGIN).zip $(PACK)

run:
	./$(PROJ_NAME)