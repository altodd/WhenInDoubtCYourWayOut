
// This is the cpp file for the Splash window which is the main window of our project

#include "splash.h"
#include "start_window.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

//Splash's constructor initializing the buttons

splash::splash(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    
//Buttons and their points for Splash window

	start_button(Point(x_max()/2-50,y_max()-200), 100,70, "START", cb_start),
	quit_button (Point (x_max()-70,0),70,70,"Quit",cb_quit),
    button_pushed(false)
{
//Commands for attaching the buttons to the window
	Image quit(Point(x_max() - 70, 0), "quitButton.jpg");
	quit.resize_image(70, 70);
	attach(quit);
	attach(start_button);
	attach(quit_button);
	
}

//------------------------------------------------------------------------------

bool splash::wait_for_button()
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

//Changes the state of button_pushed

void splash::button_pushed_change(bool state)
{
	button_pushed = state;
}

//-------------------------------------------------------------------------------

//Compares the state of button_pushed

bool splash::button_pushed_compare()
{
	if (button_pushed == true)
	{
		return true;
	}
	
	else 
	{
		return false;
	}
}
  

//-----------------------------------------------------------------------------------

//Call splash::start() for the window located at pw

void splash::cb_start(Address, Address pw)
{  

    reference_to<splash>(pw).start();    
}


//-----------------------------------------------------------------------------------

//Call splash::quit() for the window located at pw

void splash::cb_quit(Address, Address pw)
{  
    reference_to<splash>(pw).quit();    
}

//-------------------------------------------------------------------------------

//Callback function of start()

void splash::start()
{
	start_window win1(Point(200,50),1200,700,"START");
	Image game_instructions(Point(0,0),"directionsUpdated.png");
	Image beginner_label(Point(x_max()/5-200,y_max()-200),"beginner.jpg");
	Image intermediate_label(Point(((x_max())*2/5)-200,y_max()-200),"intermediate.jpg");
	Image advanced_label(Point(((x_max())*3/5)-200,y_max()-200),"advanced.jpg");
	Image expert_label(Point(((x_max())*4/5)-200,y_max()-200),"expert.jpg");
	Image missionImpossible_label(Point(((x_max())*5/5)-200,y_max()-200),"missionImpossible.jpg");
	Image quitJpg(Point(x_max() - 70, 0), "quitButton.jpg");
	
	game_instructions.resize_image(1200,700);
	beginner_label.resize_image(150,100);
	intermediate_label.resize_image(150,100);
	advanced_label.resize_image(150,100);
	expert_label.resize_image(150,100);
	missionImpossible_label.resize_image(150,100);
	quitJpg.resize_image(70, 70);
    
    win1.attach(game_instructions);
	win1.attach(beginner_label);
	win1.attach(intermediate_label);
	win1.attach(advanced_label);
	win1.attach(expert_label);
	win1.attach(missionImpossible_label);
	win1.attach(quitJpg);
	win1.wait_for_button();
}


//--------------------------------------------------------------------------------

//Callback function of quit()

void splash::quit()
{
    exit(0);
}

//------------------------------------------------------------------------------
