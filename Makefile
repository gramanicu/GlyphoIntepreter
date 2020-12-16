# Copyright 2020 Grama Nicolae

.PHONY: gitignore clean memory beauty run
.SILENT: beauty clean memory gitignore

# Program arguments

INPUT = ./tests/test.gly
BASE = 10

# Compilation variables
CC = g++
CFLAGS = -Wno-unused-parameter -Wall -Wextra -pedantic -pthread -g -O3 -std=c++17
EXE = GlyphoIntepreter
SRC = $(wildcard */*.cpp)
OBJ = $(SRC:.cpp=.o)

# Compiles the program
build: $(OBJ)
	$(info Compiling code...)
	@$(CC) -o $(EXE) $^ $(CFLAGS) ||:
	$(info Compilation successfull)
	-@rm -f *.o ||:
	@$(MAKE) -s gitignore ||:

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) 

# Executes the binary
run: clean build
	./$(EXE) $(INPUT) $(BASE)

# Deletes the binary and object files
clean:
	rm -f $(EXE) $(OBJ) GlyphoIntepreter.zip
	echo "Deleted the binary and object files"

# Automatic coding style, in my personal style
beauty:
	clang-format -i -style=file */*.cpp
	clang-format -i -style=file */*.hpp

# Checks the memory for leaks
MFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
memory:clean build
	valgrind $(MFLAGS) ./$(EXE)

# Adds and updates gitignore rules
gitignore:
	@echo "$(EXE)" > .gitignore ||:
	@echo "src/*.o" >> .gitignore ||:
	@echo ".vscode*" >> .gitignore ||:	
	@echo "*.zip" >> .gitignore ||:	
	echo "Updated .gitignore"
	
# Creates an archive of the project
archive: clean
	cp Readme.md README
	zip -FSr GlyphoIntepreter.zip ./src
	rm README

