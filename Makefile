<<<<<<< HEAD
CXX = g++-8.2.0
CXXFLAGS = -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer
LDLIBS = -lfltk -lfltk_images -lX11 -ljpeg

OBJECTS = GameManager.o Player.o HumanPlayer.o AIPlayer.o EndGame.o

all: pancakes

pancakes: Main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o pancakes Main.o $(OBJECTS) $(LDLIBS)

tests: Tests.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o tests Tests.o $(OBJECTS) $(LDLIBS)

Main.o: GameManager.h
Tests.o: GameManager.h Score.h HumanPlayer.h TestPlayer.h
GameManager.o: GameManager.h Score.h Player.h PlayerType.h EndGame.h
Player.o: Player.h
HumanPlayer.o: HumanPlayer.h Player.h
AIPlayer.o: AIPlayer.h Player.h
EndGame.o: EndGame.h

.PHONY: clean
clean:
	# remove .o files except for 'find_solution.o'
	find . ! -name 'find_solution.o' -name '*.o' -exec rm -f {} +
	rm -f *.bin pancakes tests
=======
# Configuration
CC = $(shell fltk-config --cxx)
SRCS = Startmenu.cpp AIPlayer.cpp Player.cpp HumanPlayer.cpp EndGame.cpp
OBJS = ${SRCS:.cpp=.o}
BASEFLAGS = -g -Wall -Wextra -std=c++11 -Wno-unused-parameter -w 
# BASEFLAGS += -pedantic -fsanitize=address,undefined
TARGET = main

# Generate objects and FLTK library
ifndef LIBDIR
	LIBDIR = lib
endif
LIBNAME = daugherity.a
LIB = $(LIBDIR)/$(LIBNAME)
SAMPLEOBJ = $(LIBDIR)/sample_main5.o

# Compiler Flags
CFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --cxxflags)
LDFLAGS = $(BASEFLAGS) -lfltk -lfltk_images

.PHONY: all clean run sample
.SUFFIXES:

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -I$(LIBDIR) -c -o $@ $^


# Compile and run the sample
sample: $(SAMPLEOBJ) $(LIB)
	$(CC) $(LDFLAGS) -o $@ $(SAMPLEOBJ) $(LIB)
	@./$@

# Clean and run
clean:
	$(RM) $(TARGET) *.o $(SAMPLEOBJ) sample

cleanall: clean
	$(MAKE) -C $(LIBDIR) clean

run: $(TARGET)
	@./$(TARGET)


# Recursively compile the library
$(LIB):
	$(MAKE) -C $(LIBDIR)
>>>>>>> add900a81806461caf97c5553a4ce11fe45b9e4c
