###
### Program Name: Homeward Bound
### Program Author: Andrew Derringer
### Citation: Material aquired through OSU CS162 TA Harlan James
### within course supplementary material. Author name and
### comments left intact throughout.
###


###
### @file author - Harlan James <waldroha@oregonstate.edu>
###

#project name
PROJ = Final_Derringer_Andrew



#compiler
$(CXX) = g++



#source files
SRC = inputValidation.cpp
SRC += helperFunctions.cpp
SRC += Space.cpp
SRC += Desert.cpp
SRC += Forest.cpp
SRC += Plains.cpp
SRC += main.cpp
SRC += Board.cpp
SRC += Player.cpp


#creates an object for each source file
OBJ = $(SRC:.cpp=.o)



#outputs binary
BIN = $(PROJ).bin



#compiler Flags
CFLAGS = -Wall -pedantic -std=gnu++11



#valgrind Options
VOPT = --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes



#names of tags that aren't actually files
.PHONY: default debug clean zip



#default behavior:
#  1. remove everything to start from screatch
#  2. compile the binary
#  3. run executable
default: clean $(BIN)
	#@./$(BIN)



#special Symbols:
#  @     Suppresses the command from being printed to the terminal)
#  $@    Name of tag
#  $^    Name of dependency


  
#run behavior (default alternative with debug):
#  1. remove everything to start from screatch
#  2. compile the binary
#  3. run it through valgrind for quicker debugging
run: clean $(BIN) debug



debug: $(BIN)
	@valgrind $(VOPT) ./$(BIN)



$(BIN): $(OBJ)
	@echo "CC	$@"
	@$(CXX) $(CFLAGS) $^ -o $@



#% is a wildcard. Anything that ends in ".o" will match this tag, and each
#tag depends on the same matching wildcard, but ending in ".cpp"
%.o: %.cpp
	@echo "CC	$^"
	@$(CXX) $(CFLAGS) -c $^



zip:
	zip $(PROJ).zip *.cpp *.hpp makefile



clean: $(CLEAN)
	@echo "RM	*.o"
	@echo "RM	$(BIN)"
	@rm -f *.o $(BIN)
