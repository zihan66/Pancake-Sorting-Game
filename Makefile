# Configuration
CC = g++-8.2.0
SRCS = Main.cpp AIPlayer.cpp Player.cpp HumanPlayer.cpp GameManager.cpp
OBJS = ${SRCS:.cpp=.o}
BASEFLAGS = -g -Wall -Wextra -std=c++2a -Wno-unused-parameter -w
# BASEFLAGS += -pedantic -fsanitize=address,undefined
TARGET = main

# Compiler Flags

.PHONY: all clean run sample
.SUFFIXES:

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB)
	$(CC) -o $@ $^ $(BASEFLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $^

# Clean and run
clean:
	$(RM) $(TARGET) *.o

cleanall: clean
	clean

run: $(TARGET)
	@./$(TARGET)