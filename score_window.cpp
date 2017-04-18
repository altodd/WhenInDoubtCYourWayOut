#include "score_window.h"
#include "mdo_fileio.h"

using namespace Graph_lib;

score_window::score_window(Point xy, int w, int h, const string& title, const int& difficulty, string playername) :
	Window(xy, w, h, title),

	button_proceed(Point(x_max() - 70, 0), 70, 20, "Continue", cb_proceed),

	highScore(Point(x_max() / 2, 140), 150, 25, "First Place: "),
	secondPlace(Point(x_max() / 2, 170), 150, 25, "Second Place: "),
	thirdPlace(Point(x_max() / 2, 200), 150, 25, "Third Place: "),
	fourthPlace(Point(x_max() / 2, 230), 150, 25, "Fourth Place: "),
	fifthPlace(Point(x_max() / 2, 260), 150, 25, "Fifth Place: "),

	level{ difficulty },
	playername{ playername },

	button_pushed(false)
{
	attach(button_proceed);
	attach(highScore);
	attach(secondPlace);
	attach(thirdPlace);
	attach(fourthPlace);
	attach(fifthPlace);
}

bool score_window::wait_for_button()
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

void score_window::cb_proceed(Address, Address pw)
// call the game to continue
{
	reference_to<score_window>(pw).proceed();
}

int score_window::get_level() {
	return level;
}

void score_window::proceed() {
	
	button_pushed = true;
	
	hide();
}

void score_window::show_scores() {
	int difficulty = get_level();
	mdo::user_score tostring;
	stringstream output;
	if (difficulty == 1) {
		mdo::score_io score{ "\121\WhenInDoubtCYourWayOut\GameGUI\GameGUI\beginner.txt", 320 };
		for (int i = 1; i <= 5; ++i) {
			tostring = score.get(i);
			output << tostring.name << " scoring " << tostring.score;
			string box = output.str();
			switch (i) {
			case 1:
				highScore.put(box);
				break;
			case 2:
				secondPlace.put(box);
				break;
			case 3:
				thirdPlace.put(box);
				break;
			case 4:
				fourthPlace.put(box);
				break;
			case 5:
				fifthPlace.put(box);
				break;
			}
			output.str("");
		}
	}
	if (difficulty == 2) {
		mdo::score_io score{ "\121\WhenInDoubtCYourWayOut\GameGUI\GameGUI\intermediate.txt", 640 };
		for (int i = 1; i <= 5; ++i) {
			tostring = score.get(i);
			output << tostring.name << " scoring " << tostring.score;
			string box = output.str();
			switch (i) {
			case 1:
				highScore.put(box);
				break;
			case 2:
				secondPlace.put(box);
				break;
			case 3:
				thirdPlace.put(box);
				break;
			case 4:
				fourthPlace.put(box);
				break;
			case 5:
				fifthPlace.put(box);
				break;
			}
			output.str("");
		}
	}
	if (difficulty == 3) {
		mdo::score_io score{ "\121\WhenInDoubtCYourWayOut\GameGUI\GameGUI\advanced.txt", 1280 };
		for (int i = 1; i <= 5; ++i) {
			tostring = score.get(i);
			output << tostring.name << " scoring " << tostring.score;
			string box = output.str();
			switch (i) {
			case 1:
				highScore.put(box);
				break;
			case 2:
				secondPlace.put(box);
				break;
			case 3:
				thirdPlace.put(box);
				break;
			case 4:
				fourthPlace.put(box);
				break;
			case 5:
				fifthPlace.put(box);
				break;
			}
			output.str("");
		}
	}
	if (difficulty == 4) {
		mdo::score_io score{ "\121\WhenInDoubtCYourWayOut\GameGUI\GameGUI\expert.txt", 2560 };
		for (int i = 1; i <= 5; ++i) {
			tostring = score.get(i);
			output << tostring.name << " scoring " << tostring.score;
			string box = output.str();
			switch (i) {
			case 1:
				highScore.put(box);
				break;
			case 2:
				secondPlace.put(box);
				break;
			case 3:
				thirdPlace.put(box);
				break;
			case 4:
				fourthPlace.put(box);
				break;
			case 5:
				fifthPlace.put(box);
				break;
			}
			output.str("");
		}
	}
	if (difficulty == 5) {
		mdo::score_io score{ "\altodd\121\WhenInDoubtCYourWayOut\GameGUI\GameGUI\missionImpossible.txt", 5120 };
		for (int i = 1; i <= 5; ++i) {
			tostring = score.get(i);
			output << tostring.name << " scoring " << tostring.score;
			string box = output.str();
			switch (i) {
			case 1:
				highScore.put(box);
				break;
			case 2:
				secondPlace.put(box);
				break;
			case 3:
				thirdPlace.put(box);
				break;
			case 4:
				fourthPlace.put(box);
				break;
			case 5:
				fifthPlace.put(box);
				break;
			}
			output.str("");
		}
	}
}


