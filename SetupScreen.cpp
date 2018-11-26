#include "SetupScreen.h"

SetupScreen::SetupScreen(string _scores, bool* _input, string* _inits, int* _diff, int* _numP, vector<int>* _order)
    : Window(Point(100,100), 600, 600, "Setup"),
        hScores(Point(10, 25), "High Scores: " + _scores),
        pOrder(Point(25, 450), "Order: "),
        enter(Point(300, 75), 100, 50, "Enter", cb_Enter),
        clear(Point(50, 525), 100, 50, "Clear", cb_Clear),
        next(Point(450, 525), 100, 50, "Next", cb_Next),
        inits(100, 75, 100, 50, "Initials: "),
        numPans(50, 150, 500, 50, "Number of Pancakes"),
        diffSlide(50, 225, 500, 50, "Difficulty"),
        randY(200, 300, 50, 50, "Random Order"),
        randN(400, 300, 50, 50, "Select Order")
        {

        //da basics
        numP = _numP; //start in middle of slider
        *numP = 6;
        diff = _diff; //start at left of slider(unknown right so cant start middle)
        *diff = 6;
        initials = _inits;
        *initials = "UKN";
        inputPans = _input; //and set the same bool as Random

        *inputPans = false;
        order = _order;
        //butts.capacity(9);

        //da Butts
        butts.push_back(new Button(Point(550/(9)+15, 375), 400/9, 35, "1", [](Address, Address pw){reference_to<SetupScreen>(pw).cb_Add(1);}));
        butts.push_back(new Button(Point(2*550/(9)+15, 375), 400/9, 35, "2", [](Address, Address pw){reference_to<SetupScreen>(pw).cb_Add(2);}));
        butts.push_back(new Button(Point(3*550/(9)+15, 375), 400/9, 35, "3", [](Address, Address pw){reference_to<SetupScreen>(pw).cb_Add(3);}));
        butts.push_back(new Button(Point(4*550/(9)+15, 375), 400/9, 35, "4", [](Address, Address pw){reference_to<SetupScreen>(pw).cb_Add(4);}));
        butts.push_back(new Button(Point(5*550/(9)+15, 375), 400/9, 35, "5", [](Address, Address pw){reference_to<SetupScreen>(pw).cb_Add(5);}));
        butts.push_back(new Button(Point(6*550/(9)+15, 375), 400/9, 35, "6", [](Address, Address pw){reference_to<SetupScreen>(pw).cb_Add(6);}));
        butts.push_back(new Button(Point(7*550/(9)+15, 375), 400/9, 35, "7", [](Address, Address pw){reference_to<SetupScreen>(pw).cb_Add(7);}));
        butts.push_back(new Button(Point(8*550/(9)+15, 375), 400/9, 35, "8", [](Address, Address pw){reference_to<SetupScreen>(pw).cb_Add(8);}));
        butts.push_back(new Button(Point(9*550/(9)+15, 375), 400/9, 35, "9", [](Address, Address pw){reference_to<SetupScreen>(pw).cb_Add(9);}));

        for(int i = 0; i < 9; i++){
            attach(butts[i]);
            butts[i].hide();
        }
        //da butts
        randY.callback(callbackRandY, this);
        randN.callback(callbackRandN, this);
        randY.value(1);//set the Random Yes button on
        randN.value(0); //and Random No button off

        //da sliders
        numPans.range(3,9);
        numPans.callback(callbackNumPans, this);
        diffSlide.range(1, *numP);
        diffSlide.callback(callbackDiff, this);
        numPans.value(*numP); //set the start value to the initial value
        diffSlide.value(*diff);
        numPans.step(1); //set the step between values to 1
        diffSlide.step(1);

        attach(hScores);
        attach(enter);
        attach(pOrder);
        attach(clear);
        attach(next);
        add(inits);
        add(numPans);
        add(diffSlide);
        add(randY);
        add(randN);
        show();
        Fl::redraw();
        showButtons(false);
        showOrder(false);
        Fl::run();
    }

void SetupScreen::callbackRandY(Fl_Widget *butt, void *win){
    SetupScreen* w = (SetupScreen*)win;
    *(w->inputPans) = false;
    Fl_Round_Button* rb = (Fl_Round_Button*)butt;
    rb->value(1);
    w->randN.value(0);
    w->showButtons(false);
    w->showOrder(false);
    w->callbackClear();
}

void SetupScreen::callbackRandN(Fl_Widget *butt, void *win){
    SetupScreen* w = (SetupScreen*)win;
    *(w->inputPans) = true;
    Fl_Round_Button* rb = (Fl_Round_Button*)butt;
    rb->value(1);
    w->randY.value(0);
    w->showButtons(true);
    w->showOrder(true);
}

void SetupScreen::callbackNumPans(Fl_Widget *slid, void *win){
    SetupScreen* w = (SetupScreen*)win;
    Fl_Hor_Nice_Slider* rb = (Fl_Hor_Nice_Slider*)slid;
    int temp = rb->value();
    if(temp > 9)
        temp = 9; //set the bounds for the num for insurance
    if(temp < 3)
        temp = 3;
    *(w->numP) = temp;
    rb->value(temp);
    w->diffSlide.range(1, temp);
    if(*(w->inputPans))
        w->showButtons(true);
}

void SetupScreen::callbackDiff(Fl_Widget *slid, void *win){
    SetupScreen* w = (SetupScreen*)win;
    Fl_Hor_Nice_Slider* rb = (Fl_Hor_Nice_Slider*)slid;
    int temp = rb->value();
    if(temp > *(w->numP))
        temp = *(w->numP); //set the bounds for the num for insurance
    if(temp < 1)
        temp = 1;
    rb->value(temp);
    *(w->diff) = temp; //set difficulty
}

void SetupScreen::showButtons(bool show){
    for(int i = 0; i < butts.size(); i++)
        butts[i].hide();
    if(show){
        for(int i = 0; i < *numP; i++)
            butts[i].show();
    }
    redraw();
}

void SetupScreen::showOrder(bool show){
    string orderOut;
    if(show){
        orderOut = "|top|   ";
        for(int i = 0; i < order->size();i++)
            orderOut = orderOut + to_string(order->at(i)) + "   ";
        orderOut += "|bot|";
    }
    else
        orderOut = "Randomized";
    pOrder.set_label(orderOut);
    redraw();
}

void SetupScreen::callbackClear(){
    order->erase(order->begin(), order->end());
    showButtons(*(inputPans));
    showOrder(*(inputPans));
}

void SetupScreen::callbackNext(){
    hide();
}

void SetupScreen::callbackEnter(){
    string temp = inits.value();
    temp.substr(0, 3); //get only the first three chars
    *initials = temp;
}

void SetupScreen::cb_Clear(Address, Address pw){
    reference_to<SetupScreen>(pw).callbackClear();
}

void SetupScreen::cb_Add(int i){
    butts[i-1].hide();
    order->push_back(i);
    showOrder(true);
}

void SetupScreen::cb_Enter(Address, Address pw){
    reference_to<SetupScreen>(pw).callbackEnter();
}

void SetupScreen::cb_Next(Address, Address pw){
    reference_to<SetupScreen>(pw).callbackNext();
}
