#Makefile

CC = g++
CFLAGS = -std=c++98 -Wall -pedantic -ansi -W -Wextra
LOGIN = xstejs24-xstane34
PROJ_NAME = hra2016
FILES = main.o
PACK = *.cpp *.h Makefile Doxyfile README.txt
MKDIR = src/

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c -o $@ $<
	
default: $(MKDIR)$(FILES)
	$(CC) $(CFLAGS) -o $(PROJ_NAME) $^
	
pack: clean
	rm -f $(LOGIN).zip
	zip -r $(LOGIN).zip $(PACK)
	
run:
	./$(PROJ_NAME)
	
doxygen:
	doxygen Doxyfile
	
clean:
	rm -f $(MKDIR)*.o $(MKDIR)*.out $(PROJ_NAME)
