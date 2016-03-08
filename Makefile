#Makefile

CC = g++
CFLAGS = -std=c++11 -Wall -pedantic -W -Wextra  
LOGIN = xstejs24-xstane34
PROJ_NAME = hra2016cli
FILES = hra2016cli.o
PACK = *.cpp *.h Makefile Doxyfile README.txt
MKDIR = src/

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c -o $@ $<
	
default: $(MKDIR)$(FILES)
	$(CC) $(CFLAGS) -o $(PROJ_NAME) $^ -lboost_regex
	
pack: clean
	rm -f $(LOGIN).zip
	zip -r $(LOGIN).zip $(PACK)
	
run:
	./$(PROJ_NAME)
	
doxygen:
	doxygen Doxyfile
	
clean:
	rm -f $(MKDIR)*.o $(MKDIR)*.out $(PROJ_NAME)
