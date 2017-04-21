/********************************************************************************
 * NAME:        Marcus Overzet (523 00 2848)
 * CLASS:       CSCE 121-514
 * DUE DATE:    Wednesday, April 27, 2017
 * FILE NAME:   Score_Display.cpp
 ********************************************************************************/

#include "std_lib_facilities_4.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "Score_Display.h"

////////////////////////// FOR TEAM MEMBER'S EDITS ////////////////////////////////
/*  SUGGESTED EDITS TO OTHER FILES:
 *
 * - advanced_window.cpp line120 -> have an initialized hidden Score_Display_window
 *      with difficulty 2 (2=advanced), use Score_Display_window.add(track_score);
 *   do similar edits for lines 168 and 216
 *   do similar for beginner_window (diff = 0), intermediate_window (diff = 1),
 *      expert_window (diff = 3), and missionImpossible_window (diff = 4)
 *
 * I'll post the above edits in my section of the google drive and will try to do a
 *   branch for it on the github
 */

/* Callback that hides this screen and shows the other screen */
static void cb_proceed(Address, Address pw) {
    reference_to<Score_Display_window>(pw).hide();
}

/* Function internal to Score_Display_window for accessing internal members */
void Score_Display_window::proceed() {
    return;
}

////////////////////////// END TEAM MEMBER'S EDITS ////////////////////////////////

bool Score_Display_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
	show();
	button_pushed = false;
#if 1
	// Simpler handler
	while (!button_pushed) Fl::wait();
	Fl::redraw();
#else
	// To handle the case where the user presses the X button in the window frame
	// to kill the application, change the condition to 0 to enable this branch.
	Fl::run();
#endif
	return button_pushed;
}

/* INITIAL CONDITIONS FOR OUR SCORE_IO */
string get_label(int diff) {
    // change display depending on difficulty
    switch(diff) {
        case 0:  return "Beginner";
        case 1:  return "Intermediate";
        case 2:  return "Advanced";
        case 3:  return "Expert";
        case 4:  return "Impossible";
        default: return "ERROR";
    }
}

string get_file_to_open( int diff ) {
    switch(diff) {
        case 0:  return "Beginner_Scores.txt";
        case 1:  return "Intermediate_Scores.txt";
        case 2:  return "Advanced_Scores.txt";
        case 3:  return "Expert_Scores.txt";
        case 4:  return "Impossible_Scores.txt";
        default: return "Other_Scores.txt";
    }
}

int get_max_score( int diff ) {
    switch(diff) {
        case 0:  return 320;
        case 1:  return 640;
        case 2:  return 1280;
        case 3:  return 2560;
        case 4:  return 5120;
        default: return -1;
    }
}

/* Reget our data values from Score_Display... internal, DOES NOT REDRAW */
void Score_Display_window::update() {
    //make our vector of texts
    // only update and attach text widgets if we have the data
    // fixme: move each score to be centered
    int num = my_io.get_num_read_scores();
    int n;
    
    if( num > 0 ) {
        score0.set_label( my_io.get(0).name + "   " + to_string( my_io.get(0).score ) );
        attach( score0 );
    }
    if( num > 1 ) {
        score1.set_label( my_io.get(1).name + "   " + to_string( my_io.get(1).score ) );
        attach( score1 );
    }
    if( num > 2 ) {
        score2.set_label( my_io.get(2).name + "   " + to_string( my_io.get(2).score ) );
        attach( score2 );
    }
    if( num > 3 ) {
        score3.set_label( my_io.get(3).name + "   " + to_string( my_io.get(3).score ) );
        attach( score3 );
    }
    if( num > 4 ) {
        score4.set_label( my_io.get(4).name + "   " + to_string( my_io.get(4).score ) );
        attach( score4 );
    }
}

void Score_Display_window::add( mdo::user_score us ) {
    my_io.add(us);
    update();
    
    Fl::redraw();
}

/* Basic Constructor */
Score_Display_window::Score_Display_window(Point xy, int w, int h, int diff , string& playername) :
    Window(xy,w,h,"Scoreboard"),
    title_text(Point((w/2),50),get_label(diff)),
    my_io(get_file_to_open(diff),get_max_score(diff)),
    score0( Point((w/2),200+50*0), "*" ),
    score1( Point((w/2),200+50*1), "*" ),
    score2( Point((w/2),200+50*2), "*" ),
    score3( Point((w/2),200+50*3), "*" ),
    score4( Point((w/2),200+50*4), "*" ),
    button_proceed( Point((w/2)-100,h-75), 200, 50, "Continue", cb_proceed),
    difficulty(diff),
    playername(playername)
{
    // resize the font for our score Text objects
	try {
		score0.set_font_size(20);
		score1.set_font_size(20);
		score2.set_font_size(20);
		score3.set_font_size(20);
		score4.set_font_size(20);
	}
	catch (exception& e) {
		cerr << "it done broke, on the score display window" << endl;
	}
    
    title_text.set_font_size( 40 );
    
    // update score Text objects with my_io's data and draw.
    update();
    
    // attach our title_text
    attach(title_text);
    attach(button_proceed);
    
    // display our screen.
    show();
}
