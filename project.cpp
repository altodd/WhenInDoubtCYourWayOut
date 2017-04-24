#include "std_lib_facilities_4.h"
#include "splash.h"
#include "start_window.h"
#include "Graph.h"

int main()
try
 {	

 //Make a Aggiesnap_window 

		splash main_menu(Point(200,50),1200,700,"Splash main");
		
//Adds the Instructions
		
		Image start_win(Point(0,0),"handmadeSplash.jpg");
	    start_win.resize_image(1200,700);
		Image quitJpg(Point(x_max() - 70, 0), "quitButton.jpg");
		quitJpg.resize_image(70, 70);
		main_menu.attach(start_win);
		main_menu.attach(quitJpg);
		main_menu.wait_for_button();
		
		return 0;
}

//Catch will handle exceptions of any type 
catch(...)
{
	cerr<<"Unknown Exception!\n";
	return 1;
}