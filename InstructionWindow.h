#include "Graph.h"
#include "Window.h"
#include "Point.h"
#include "std_lib_facilities_5.h"
#include "GUI.h"
using namespace Graph_lib;
struct InstructionWindow : Graph_lib::Window{
  InstructionWindow(Point xy, int w, int h, const string& title);
private:
  Button start_;
  Image c;
  static void cb_start(Address, Address);
  void start();
};
