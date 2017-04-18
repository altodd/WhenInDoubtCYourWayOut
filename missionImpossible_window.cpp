/*
   Simple_window.cpp
   Minimally revised for C++11 features of GCC 4.6.3 or later
   Walter C. Daugherity		June 10, 2012
*/

//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "missionImpossible_window.h"
#include "UsefulLogicFunctions.h"
#include "mdo_fileio.h"
#include "score_window.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

missionImpossible_window::missionImpossible_window(Point xy, int w, int h, const string& title, string playername) :
    Window(xy,w,h,title),

	Maroon(Point(x_max()/5, 200), 70, 20, "Band", cb_maroon),
	White(Point(x_max()*2/5, 200), 70, 20, "Team", cb_white),
	Black(Point(x_max()*3/5, 200), 70, 20, "12th Man", cb_black),

	scoreDisp(Point(x_max() - 70, 20), 150, 25, "Score: "),
	computer_correct(Point(x_max() - 300, 25), 150, 25, "Percent I have guessed right: "),
	choices_to_go(Point(x_max() - 600, 25), 150, 25, "Choices to go: "),

	observation(Point(x_max()/2, 500), "Make some choices so that I can get you figured out"),
	guessing(Point(x_max()/2, 500), "I will guess what you are going to select next, now"),

	observation_period{ true },
	playername{ playername },

    button_pushed(false)
{
	attach(choices_to_go);
	attach(observation);
    attach(Maroon);
	attach(White);
	attach(Black);
}

//------------------------------------------------------------------------------

bool missionImpossible_window::wait_for_button()
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

void missionImpossible_window::cb_maroon(Address, Address pw)
{  
    reference_to<missionImpossible_window>(pw).maroon();    
}

void missionImpossible_window::cb_white(Address, Address pw)
{
	reference_to<missionImpossible_window>(pw).white();
}

void missionImpossible_window::cb_black(Address, Address pw)
{
	reference_to<missionImpossible_window>(pw).black();
}

//------------------------------------------------------------------------------

void missionImpossible_window::maroon()
{
	if (observation_period == true) {
		Choice user = charToChoice('M');
		int calcVal = choiceToInt(user);
		choices.push_back(calcVal);
		--choices_left;
		choices_to_go.put(intToStr(choices_left));
		if (choices_left == 0) {
			observation_period = false;
			choices_left = rounds;
			detach(observation);
			attach(scoreDisp);
			attach(computer_correct);
			attach(guessing);
		}
		Fl::redraw();
		button_pushed = true;
	}
	else {
		calcProb(choices, probM, probW, probB);
		Choice guess = makeGuess(probM, probW, probB);
		Choice user = charToChoice('M');
		bool win = compareChoices(guess, user);
		score = trackScore(win, score);
		scoreDisp.put(intToStr(score));
		computer_correct.put(dubToStr(percentCorrect(win, timesCorrect, guesses)));
		++guesses;
		choices.erase(choices.begin());
		choices.push_back(choiceToInt(user));
		--choices_left;
		choices_to_go.put(intToStr(choices_left));
		if (choices_left == 0) {
			mdo::user_score track_score;
			track_score.score = score;
			track_score.name = playername;
			mdo::score_io fin_score{ "\121\WhenInDoubtCYourWayOut\GameGUI\GameGUI\missionImpossible.txt", 5120 };
			fin_score.mdo::score_io::add(track_score);
			score_window missionScore(Point(200, 50), 1200, 700, "Mission Impossible Scores", 5, playername);
			missionScore.show_scores();
			missionScore.wait_for_button();
			hide();
		}
		Fl::redraw();
		button_pushed = true;
	}
}

void missionImpossible_window::white()
{
	if (observation_period == true) {
		Choice user = charToChoice('W');
		int calcVal = choiceToInt(user);
		choices.push_back(calcVal);
		--choices_left;
		choices_to_go.put(intToStr(choices_left));
		if (choices_left == 0) {
			observation_period = false;
			choices_left = rounds;
			detach(observation);
			attach(scoreDisp);
			attach(computer_correct);
			attach(guessing);
		}
		Fl::redraw();
		button_pushed = true;
	}
	else {
		calcProb(choices, probM, probW, probB);
		Choice guess = makeGuess(probM, probW, probB);
		Choice user = charToChoice('W');
		bool win = compareChoices(guess, user);
		score = trackScore(win, score);
		scoreDisp.put(intToStr(score));
		computer_correct.put(dubToStr(percentCorrect(win, timesCorrect, guesses)));
		++guesses;
		choices.erase(choices.begin());
		choices.push_back(choiceToInt(user));
		--choices_left;
		choices_to_go.put(intToStr(choices_left));
		if (choices_left == 0) {
			mdo::user_score track_score;
			track_score.score = score;
			track_score.name = playername;
			mdo::score_io fin_score{ "\121\WhenInDoubtCYourWayOut\GameGUI\GameGUI\missionImpossible.txt", 5120 };
			fin_score.mdo::score_io::add(track_score);
			score_window missionScore(Point(200, 50), 1200, 700, "Mission Impossible Scores", 5, playername);
			missionScore.show_scores();
			missionScore.wait_for_button();
			hide();
		}
		Fl::redraw();
		button_pushed = true;
	}
}

void missionImpossible_window::black()
{
	if (observation_period == true) {
		Choice user = charToChoice('B');
		int calcVal = choiceToInt(user);
		choices.push_back(calcVal);
		--choices_left;
		choices_to_go.put(intToStr(choices_left));
		if (choices_left == 0) {
			observation_period = false;
			choices_left = rounds;
			detach(observation);
			attach(scoreDisp);
			attach(computer_correct);
			attach(guessing);
		}
		Fl::redraw();
		button_pushed = true;
	}
	else {
		calcProb(choices, probM, probW, probB);
		Choice guess = makeGuess(probM, probW, probB);
		Choice user = charToChoice('B');
		bool win = compareChoices(guess, user);
		score = trackScore(win, score);
		scoreDisp.put(intToStr(score));
		computer_correct.put(dubToStr(percentCorrect(win, timesCorrect, guesses)));
		++guesses;
		choices.erase(choices.begin());
		choices.push_back(choiceToInt(user));
		--choices_left;
		choices_to_go.put(intToStr(choices_left));
		if (choices_left == 0) {
			mdo::user_score track_score;
			track_score.score = score;
			track_score.name = playername;
			mdo::score_io fin_score{ "\121\WhenInDoubtCYourWayOut\GameGUI\GameGUI\missionImpossible.txt", 5120 };
			fin_score.mdo::score_io::add(track_score);
			score_window missionScore(Point(200, 50), 1200, 700, "Mission Impossible Scores", 5, playername);
			missionScore.show_scores();
			missionScore.wait_for_button();
			hide();
		}
		Fl::redraw();
		button_pushed = true;
	}
}

//------------------------------------------------------------------------------
