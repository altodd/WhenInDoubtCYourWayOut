#pragma once
#include "GUI.h"
#include "Graph.h"

using namespace Graph_lib;

struct score_window : Graph_lib::Window {
	score_window(Point xy, int w, int h, const string& title, const int& difficulty, string playername);

	bool wait_for_button();

	void show_scores();

	string playername;

	int get_level();

private:
	Out_box highScore;
	Out_box secondPlace;
	Out_box thirdPlace;
	Out_box fourthPlace;
	Out_box fifthPlace;
	Button button_proceed;

	bool button_pushed;

	static void cb_proceed(Address, Address);

	void proceed();

	int level;
};