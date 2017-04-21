/*
   Simple_window.cpp
   Minimally revised for C++11 features of GCC 4.6.3 or later
   Walter C. Daugherity		June 10, 2012
*/

//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "start_window.h"
#include "beginner_window.h"
#include "intermediate_window.h"
#include "advanced_window.h"
#include "expert_window.h"
#include "missionImpossible_window.h"
#include "Score_Display.h"
#include "Graph.h"

using namespace Graph_lib;
//------------------------------------------------------------------------------

//start_wFindow's structure initializing the in-box for text

struct In_box: Widget
{	
	In_box(Point xy, int w, int h, const string& s)
	      :Widget(xy,w,h,s,0){}

	string get_string();
    void attach(start_window& win1);
};	
//-------------------------------------------------------------------------------

//start_window's structure initializing the out-box for text

struct Out_box: Widget
{	
	Out_box(Point xy, int w, int h, const string& s)
	      :Widget(xy,w,h,s,0){}

	string get_string();
    void attach(start_window& win1);
};	

//------------------------------------------------------------------------------

start_window::start_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
	
	//Constructors for the buttons
    quit_button(Point(x_max()-70,0), 70, 70, "Quit", cb_quit),
	level_beginner(Point(x_max()/5-200, y_max()-200), 150, 100, "Beginner", cb_beginner),
	level_intermediate(Point(((x_max())*2/5)-200, y_max()-200), 150, 100, "Intermediate", cb_intermediate),
	level_advanced(Point(((x_max())*3/5)-200, y_max()-200), 150, 100, "Advanced", cb_advanced),
	level_expert(Point(((x_max())*4/5)-200, y_max()-200), 150, 100, "Expert", cb_expert),
	level_missionImpossible(Point(((x_max())*5/5)-200, y_max()-200), 150, 100, "Mission Impossible", cb_missionImpossible),
    //getname_button(Point((x_max()*4/5)+ 60,20), 70, 20, "Get Name", cb_getname),
	
	//In-box and out-box for the upload window
	inboxplayername(Point ((x_max()/2)-125, y_max()/2 - 15), 250, 25, "Enter player name: "),
	invalidUsername(Point ((x_max()/2)-450, y_max()/2 - 17), "Please enter a username of 7 or less alphabeticical characters"),
	//errormessage(Point ((x_max()*3/5)-50, 20), 250, 25, "Error message: "),
	
	
	button_pushed(false),
	has_valid_name(false)
{
    attach(quit_button);
	attach(level_beginner);
	attach(level_intermediate);
	attach(level_advanced);
	attach(level_expert);
	attach(level_missionImpossible);
	//attach(getname_button);
	
	//Commands to attach In-box and out-box

	attach(inboxplayername);
	invalidUsername.set_color(Color::white);
	invalidUsername.set_font_size(24);
	//attach(errormessage);
}

//------------------------------------------------------------------------------

bool start_window::wait_for_button()
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



//------------------------------------------------------------------------------

void start_window::cb_quit(Address, Address pw)
// call start_window::quit() for the window located at pw
{  
    reference_to<start_window>(pw).quit();    
}
//------------------------------------------------------------------------------

void start_window::cb_beginner(Address, Address pw)
// call start_window::beginner() for the window located at pw
{  
    reference_to<start_window>(pw).beginner();    
}

//------------------------------------------------------------------------------

void start_window::cb_intermediate(Address, Address pw)
// call start_window::intermediate() for the window located at pw
{  
    reference_to<start_window>(pw).intermediate();    
}

//------------------------------------------------------------------------------

void start_window::cb_advanced(Address, Address pw)
// call start_window::advanced() for the window located at pw
{  
    reference_to<start_window>(pw).advanced();    
}
//------------------------------------------------------------------------------

void start_window::cb_expert(Address, Address pw)
// call start_window::expert() for the window located at pw
{  
    reference_to<start_window>(pw).expert();    
}
//------------------------------------------------------------------------------

void start_window::cb_missionImpossible(Address, Address pw)
// call start_window::missionImpossible() for the window located at pw
{  
    reference_to<start_window>(pw).missionImpossible();    
}
//------------------------------------------------------------------------------

/*void start_window::cb_getname(Address, Address pw)
// call start_window::getname() for the window located at pw
{  
    reference_to<start_window>(pw).getname();    
}*/
//------------------------------------------------------------------------------

//Callback function of beginner()

void start_window::beginner()
{
	getname();
	if( has_valid_name ) {
		beginner_window win2(Point(200,50),1200,700,"BEGINNER", playername);
		Score_Display_window begginnerScore(Point(200, 50), 1200, 700, 0, playername);
		win2.wait_for_button();
		//begginnerScore.show_scores();     // both of these are taken care of in the
		//begginnerScore.wait_for_button(); // constructor
	}
}
//-------------------------------------------------------------------------------

//Callback function of intermediate()

void start_window::intermediate()
{
	getname();
	if( has_valid_name ) {
		intermediate_window win3(Point(200,50),1200,700,"INTERMEDIATE", playername);
		Score_Display_window intermediateScore(Point(200, 50), 1200, 700, 1, playername);
		win3.wait_for_button();
		//intermediateScore.show_scores();
		//intermediateScore.wait_for_button();
	}
}
//-------------------------------------------------------------------------------

//Callback function of advanced()

void start_window::advanced()
{
	getname();
	if( has_valid_name ) {
		advanced_window win4(Point(200,50),1200,700,"ADVANCED", playername);
		Score_Display_window advancedScore(Point(200, 50), 1200, 700, 2, playername);
		win4.wait_for_button();
		//advancedScore.show_scores();
		//advancedScore.wait_for_button();
	}
}
//-------------------------------------------------------------------------------

//Callback function of expert()

void start_window::expert()
{
	getname();
	if( has_valid_name ) {
		expert_window win5(Point(200,50),1200,700,"EXPERT", playername);
		Score_Display_window expertScore(Point(200, 50), 1200, 700, 3, playername);
		win5.wait_for_button();
		//expertScore.show_scores();
		//expertScore.wait_for_button();
	}	
}
//-------------------------------------------------------------------------------

//Callback function of missionImpossible()

void start_window::missionImpossible()
{
	getname();
	if( has_valid_name ) {
		missionImpossible_window win6(Point(200,50),1200,700,"MISSION IMPOSSIBLE", playername);
		Score_Display_window missionScore(Point(200, 50), 1200, 700, 4, playername);
		win6.wait_for_button();
		//missionScore.show_scores();
		//missionScore.wait_for_button();
	}	
}
//-------------------------------------------------------------------------------------------------------------------------------------------

//The code to be executed once the get name button is clicked. It retrieves the file from directory and adds tags.

void start_window::getname()
{

	bool start = false;
	bool end = false;

	//while (!end)
	//{
	string getplayername;
	getplayername = inboxplayername.get_string();
		
	//The following if statement checks to see that filename end correctly, otherwise prints error message
	
	if (!mdo::is_valid_username( getplayername ))	//replace with is valid name
	{
	    attach(invalidUsername);
		Fl::redraw(); 
		has_valid_name = false;
		wait_for_button();
	}
	
	else 
	{
		playername = getplayername;
		detach(invalidUsername);
		Fl::redraw();
		has_valid_name = true;
		end = true;			
	}
}
	
//}
//------------------------------------------------------------------------------


void start_window::quit()
{
    exit(0);
}

//------------------------------------------------------------------------------
