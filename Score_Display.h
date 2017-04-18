/********************************************************************************
 * NAME:        Marcus Overzet (523 00 2848)
 * CLASS:       CSCE 121-514
 * DUE DATE:    Wednesday, April 27, 2017
 * FILE NAME:   Score_Display.h
 ********************************************************************************/

/*
 * create constructor (Point,int,int, int difficulty_level, user_score to_add_in)
 * or (Point,int,int, int difficulty_level) and later use add(us)
 * 
 * for our case, use the later.
 */

#ifndef MDO_SCOREDISPLAY_H
#define MDO_SCOREDISPLAY_H

#include "std_lib_facilities_4.h"
#include "GUI.h"
#include "Graph.h"
#include "Window.h"
#include "mdo_fileio.h"
using namespace Graph_lib;

// callback for leaving this screen
static void cb_proceed(Address,Address);
//static void cb_quit(Address, Address);

class Score_Display_window : public Graph_lib::Window {
    // things to draw on our window.
    Graph_lib::Text title_text;
    
    Graph_lib::Text score0;
    Graph_lib::Text score1;
    Graph_lib::Text score2;
    Graph_lib::Text score3;
    Graph_lib::Text score4;
    
    Graph_lib::Button button_proceed;
    
    // difficulty level for this screen
    int difficulty;
    
    // internal logic
    mdo::score_io my_io;
    
    void update();
    
    void proceed();
    
    string playername;
     
public:
    // constructor.
    // MAY PUT BACK! CHECK CODE TO SEE IF IT WORKS!
    //Score_Display_window(Point xy, int w, int h, int diff, mdo::user_score us);
    Score_Display_window(Point xy, int w, int h, int diff , string& playername);
    
    // return the difficulty level for this screen
    int get_level() { return difficulty; };
    
    // callback functions. empty (for now)
    void go_to_main() {return;};
    
    void add( mdo::user_score );
    
};

#endif
