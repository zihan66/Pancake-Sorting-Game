CC = $(shell fltk-config --cxx)
BASEFLAGS = -w -std=c++11
CFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --cxxflags)
LDFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --ldflags)
TARGET = daugherity.a

SRCS = Graph.cpp GUI.cpp Simple_window.cpp Window.cpp
OBJS = ${SRCS:.cpp=.o}

.PHONY: all clean run sample

all: $(TARGET)

# Objects
Graph.o: Graph.cpp Graph.h
GUI.o: GUI.cpp GUI.h
Simple_window.o: Simple_window.cpp Simple_window.h
Window.o: Window.cpp Window.h Graph.h GUI.h
# Headers
Graph.h: Point.h std_lib_facilities_5.h
GUI.h: Window.h Graph.h
Simple_window.h: GUI.h Graph.h
Window.h: Point.h std_lib_facilities_5.h
std_lib_facilities_5.h:
Point.h:

$(TARGET): $(OBJS)
	ar rvs $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	$(RM) $(TARGET) $(OBJS)
