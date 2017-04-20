
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//



#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct start_window: Graph_lib ::Window {
    start_window(Point xy, int w, int h, const string& title );

    bool wait_for_button(); // simple event loop

	string playername;
	
	bool has_valid_name;
private:

    In_box inboxplayername;  
	Out_box errormessage;
	Button getname_button;
    Button quit_button;     // Quit button
	Button level_beginner;
	Button level_intermediate;
	Button level_advanced;
	Button level_expert;
	Button level_missionImpossible;
	
	bool button_pushed;     // implementation detail
	
	static void cb_quit(Address, Address); // callback for quit_button
	static void cb_beginner(Address, Address);
	static void cb_intermediate(Address, Address);
	static void cb_advanced(Address, Address);
	static void cb_expert(Address, Address);
	static void cb_missionImpossible(Address, Address);
	static void cb_getname(Address, Address);
	
    void quit();            // action to be done when next_button is pressed
	void beginner();
	void intermediate();
	void advanced();
	void expert();
	void missionImpossible();
	void getname();
};

//------------------------------------------------------------------------------


