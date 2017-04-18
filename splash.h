
// This is the header (.h) file for the Aggiesnap window which is the main window of our project


#include "GUI.h"    
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct splash : Graph_lib::Window 

{
		splash(Point xy, int w, int h, const string& title);

		bool wait_for_button();                   // Simple event loop   
		void button_pushed_change(bool state);    //Declaration of button_pushed_change
		bool button_pushed_compare();             //Declaration of button_pushed_compare
		
	private:
		                  
		Button quit_button;                       // The quit button
		Button start_button; 
		bool button_pushed;                       // Implementation detail

		
		
		static void cb_start(Address, Address);  // Callback for start_button 
		void start();           
	
		static void cb_quit(Address, Address);    // Callback for quit_button
		void quit();                              // Action to be done when quit_button is pressed
	
};

//------------------------------------------------------------------------------


