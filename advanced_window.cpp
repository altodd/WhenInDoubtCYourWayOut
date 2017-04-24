/*
   Simple_window.cpp
   Minimally revised for C++11 features of GCC 4.6.3 or later
   Walter C. Daugherity		June 10, 2012
*/

//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "advanced_window.h"
#include "UsefulLogicFunctions.h"
#include "Score_Display.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

advanced_window::advanced_window(Point xy, int w, int h, const string& title, string playername) :
	Window(xy, w, h, title),

	Maroon(Point(790, 495), 175, 135, "Band", cb_maroon),
	White(Point(515, 495), 175, 135, "Team", cb_white),
	Black(Point(245, 495), 175, 135, "12th Man", cb_black),
	Quit(Point(x_max() - 70, 0), 70, 70, "quit", cb_quit),

	scoreDisp(Point(403, 290), 120, 60, ""),
	computer_correct(Point(615, 315), 170, 35, ""),
	choices_to_go(Point(403, 139), 120, 60, ""),

	observation(Point(0, 0), "observationText.png"),
	guessing(Point(0, 0), "playingText.png"),
	computerRight(Point(0, 0), "userLoose.png"),
	userWin(Point(0, 0), "userWin.png"),
	background(Point(0, 0), "gameBG.png"),

	observation_period{ true },
	playername{ playername },

	uniqueScore(Point(200, 50), 1200, 700, 2, playername),

	button_pushed(false)
{
	attach(choices_to_go);
	choices_to_go.put(intToStr(rounds));
	attach(observation);
	attach(Maroon);
	attach(White);
	attach(Black);
	attach(Quit);
	observation.resize_image(1199, 699);
	computerRight.resize_image(1199, 699);
	guessing.resize_image(1199, 699);
	userWin.resize_image(1199, 699);
	background.resize_image(1199, 699);
	attach(background);
	attach(observation);
	uniqueScore.hide();
}

//------------------------------------------------------------------------------

bool advanced_window::wait_for_button()
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

void advanced_window::cb_maroon(Address, Address pw)
{
	reference_to<advanced_window>(pw).maroon();
}

void advanced_window::cb_white(Address, Address pw)
{
	reference_to<advanced_window>(pw).white();
}

void advanced_window::cb_black(Address, Address pw)
{
	reference_to<advanced_window>(pw).black();
}

void advanced_window::cb_quit(Address, Address pw)
{
	reference_to<advanced_window>(pw).quitButton();
}

//------------------------------------------------------------------------------
void advanced_window::quitButton()
{
	exit(0);
}

void advanced_window::maroon()
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
			choices_to_go.put(intToStr(choices_left));
			detach(observation);
			attach(scoreDisp);
			attach(computer_correct);
			attach(guessing);
		}
		Fl::redraw();
		//button_pushed = true; // ??? this was in advanced_window.cpp, not here
	}
	else {
		calcProb(choices, probM, probW, probB);
		Choice guess = makeGuess(probM, probW, probB);
		Choice user = charToChoice('M');
		if (win == true) {
			detach(userWin);
		}
		else {
			detach(computerRight);
		}
		win = compareChoices(guess, user);
		if (win == true) {
			attach(userWin);
		}
		else {
			attach(computerRight);
		}
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
			uniqueScore.add(track_score);
			uniqueScore.show();
			hide();
		}
		Fl::redraw();
	}
}

void advanced_window::white()
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
			choices_to_go.put(intToStr(choices_left));
			detach(observation);
			attach(scoreDisp);
			attach(computer_correct);
			attach(guessing);
		}
		Fl::redraw();
	}
	else {
		calcProb(choices, probM, probW, probB);
		Choice guess = makeGuess(probM, probW, probB);
		Choice user = charToChoice('W');
		if (win == true) {
			detach(userWin);
		}
		else {
			detach(computerRight);
		}
		win = compareChoices(guess, user);
		if (win == true) {
			attach(userWin);
		}
		else {
			attach(computerRight);
		}
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
			uniqueScore.add(track_score);
			uniqueScore.show();
			hide();
		}
		Fl::redraw();
	}
}

void advanced_window::black()
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
			choices_to_go.put(intToStr(choices_left));
			detach(observation);
			attach(scoreDisp);
			attach(computer_correct);
			attach(guessing);
		}
		Fl::redraw();
	}
	else {
		calcProb(choices, probM, probW, probB);
		Choice guess = makeGuess(probM, probW, probB);
		Choice user = charToChoice('B');
		if (win == true) {
			detach(userWin);
		}
		else {
			detach(computerRight);
		}
		win = compareChoices(guess, user);
		if (win == true) {
			attach(userWin);
		}
		else {
			attach(computerRight);
		}
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
			uniqueScore.add(track_score);
			uniqueScore.show();
			hide();
		}
		Fl::redraw();
	}
}

//------------------------------------------------------------------------------
