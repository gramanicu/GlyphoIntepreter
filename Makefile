# Copyright 2020 Grama Nicolae

.PHONY: gitignore clean memory beauty run
.SILENT: beauty clean memory gitignore

# Program arguments

INPUT = ./tests/printn.gly
BASE = 

# Compilation variables
CC = g++
CFLAGS = -Wno-unused-parameter -Wall -Wextra -pedantic -pthread -g -O3 -std=c++17
EXE = GlyphoIntepreter
SRC = src/Main.cpp src/Glypho/InputParser.cpp src/Glypho/Interpreter.cpp src/Glypho/Instruction.cpp src/Glypho/Stack.cpp src/Glypho/Integer.cpp src/Glypho/Helpers.cpp
OBJ = $(SRC:.cpp=.o)

CSFILES = */*.cpp */*/*.cpp */*/*.hpp

# Compiles the program
build: $(OBJ)
	@$(CC) -o $(EXE) $^ $(CFLAGS) ||:
	-@rm -f *.o ||:
	@$(MAKE) -s gitignore ||:

%.o: %.cpp
	@$(CC) -o $@ -c $< $(CFLAGS) ||:

# Executes the binary
run: clean build
	@./$(EXE) $(INPUT) $(BASE) ||:

# Deletes the binary and object files
clean:
	rm -f $(EXE) $(OBJ) GlyphoIntepreter.zip

# Automatic coding style, in my personal style
beauty:
	clang-format -i -style=file $(CSFILES)

# Checks the memory for leaks
MFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
memory:clean build
	valgrind $(MFLAGS) ./$(EXE) $(INPUT) $(BASE) 

# Adds and updates gitignore rules
gitignore:
	@echo "$(EXE)" > .gitignore ||:
	@echo "src/*.o" >> .gitignore ||:
	@echo "src/*/*.o" >> .gitignore ||:
	@echo ".vscode*" >> .gitignore ||:	
	@echo "*.zip" >> .gitignore ||:	
	@echo "*vcx*" >> .gitignore ||:	
	@echo "*.log" >> .gitignore ||:	
	@echo "*.sln" >> .gitignore ||:	
	@echo ".vs*" >> .gitignore ||:	
	@echo "Debug*" >> .gitignore ||:	

# Creates an archive of the project
archive: clean
	cp Readme.md README
	zip -FSr GlyphoIntepreter.zip ./src
	rm README

