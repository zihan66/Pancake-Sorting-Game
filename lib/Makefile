CC = $(shell fltk-config --cxx)
BASEFLAGS = -w -std=c++11
CFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --cxxflags)
LDFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --ldflags)
TARGET = daugherity.a

<<<<<<< HEAD:Test/lib/Makefile
SRCS = Graph.cpp GUI.cpp score_screen.cpp Window.cpp
=======
SRCS = Graph.cpp GUI.cpp Simple_window.cpp Window.cpp
>>>>>>> add900a81806461caf97c5553a4ce11fe45b9e4c:lib/Makefile
OBJS = ${SRCS:.cpp=.o}

.PHONY: all clean run sample

all: $(TARGET)

# Objects
Graph.o: Graph.cpp Graph.h
GUI.o: GUI.cpp GUI.h
<<<<<<< HEAD:Test/lib/Makefile
score_screen.o: score_screen.cpp score_screen.h
=======
Simple_window.o: Simple_window.cpp Simple_window.h
>>>>>>> add900a81806461caf97c5553a4ce11fe45b9e4c:lib/Makefile
Window.o: Window.cpp Window.h Graph.h GUI.h
# Headers
Graph.h: Point.h std_lib_facilities_5.h
GUI.h: Window.h Graph.h
<<<<<<< HEAD:Test/lib/Makefile
score_screen.h: GUI.h Graph.h
=======
Simple_window.h: GUI.h Graph.h
>>>>>>> add900a81806461caf97c5553a4ce11fe45b9e4c:lib/Makefile
Window.h: Point.h std_lib_facilities_5.h
std_lib_facilities_5.h:
Point.h:

$(TARGET): $(OBJS)
	ar rvs $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	$(RM) $(TARGET) $(OBJS)
