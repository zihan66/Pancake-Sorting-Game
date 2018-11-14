# Configuration
CC = $(shell fltk-config --cxx)
SRCS = Startmenu.cpp
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
LDFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --ldflags)

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
