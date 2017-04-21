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
	    start_win.resize_image(1199,699);
		main_menu.attach(start_win);
		main_menu.wait_for_button();
		
		
	return 0;
}

//Catch will handle exceptions of any type 
catch(...)
{
	cerr<<"Unknown Exception!\n";
	return 1;
}