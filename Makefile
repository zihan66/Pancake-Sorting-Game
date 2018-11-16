CXX = g++-8.2.0
CXXFLAGS = -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer
LDLIBS = -lncurses++ -lmenu -lpanel -lform -lutil -lncurses

OBJECTS = GameManager.o IOManager.o Player.o HumanPlayer.o AIPlayer.o

all: pancakes

pancakes: Main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o pancakes Main.o $(OBJECTS) find_solution.o $(LDLIBS)

tests: Tests.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o tests Tests.o $(OBJECTS) find_solution.o $(LDLIBS)

Main.o: GameManager.h
Tests.o: GameManager.h Score.h HumanPlayer.h TestPlayer.h
GameManager.o: GameManager.h IOManager.h Score.h Player.h PlayerType.h EndGame.h
IOManager.o: IOManager.h Score.h Player.h PlayerType.h
Player.o: Player.h find_solution.h
HumanPlayer.o: IOManager.h HumanPlayer.h Player.h
AIPlayer.o: AIPlayer.h Player.h

.PHONY: clean
clean:
	# remove .o files except for 'find_solution.o'
	find . ! -name 'find_solution.o' -name '*.o' -exec rm -f {} +
	rm -f *.bin pancakes tests