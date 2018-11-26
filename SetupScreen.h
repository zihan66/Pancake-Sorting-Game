#pragma once

#include "Window.h"
#include "Point.h"
#include "GUI.h"
#include "Graph.h"
#include <Fl/Fl_Text_Buffer.H>
#include <Fl/Fl_Text_Display.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Hor_Nice_Slider.H>
#include <Fl/Fl_Round_Button.H>
#include "std_lib_facilities_5.h"

using namespace Graph_lib;

class SetupScreen : Graph_lib::Window
{
    private:
        Vector_ref<Button> butts;

        Button clear;
        Button next;
        Text pOrder;
        Text hScores;
        Button enter;

        Fl_Input inits;
        Fl_Hor_Nice_Slider numPans;
        Fl_Hor_Nice_Slider diffSlide;
        Fl_Round_Button randY;
        Fl_Round_Button randN;


        bool* inputPans;
        int* numP;
        int* diff;
        string* initials;
        string scores;
        vector<int>* order;

        static void callbackRandY(Fl_Widget *butt, void *butt2);
        static void callbackRandN(Fl_Widget *butt, void *butt2);
        static void callbackNumPans(Fl_Widget *slid, void *diffSlide);
        static void callbackDiff(Fl_Widget *slid, void *win);
        void callbackClear();
        static void cb_Clear(Address, Address pw);
        void callbackNext();
        static void cb_Next(Address butt, Address pw);
        void cb_Add(int i);
        void callbackEnter();
        static void cb_Enter(Address, Address pw);

        void setBool(bool b);
        void showButtons(bool show);
        void showOrder(bool show);

    public:
        SetupScreen(string _scores, bool* _input, string* _inits, int* _diff, int* _numP, vector<int>* _order);

};
