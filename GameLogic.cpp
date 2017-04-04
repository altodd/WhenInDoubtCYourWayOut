#include "std_lib_facilities_4.h"
#include "UsefulLogicFunctions.h"

int main()
try {
	vector<int> choices;
	int difficulty = 0;
	int rounds = 0;
	int score = 0;
	int guesses = 0;
	double timesCorrect = 0.0;
	double probM = 0.0;
	double probW = 0.0;
	double probB = 0.0;

	cout << "Enter a difficulty 1 to 5: ";
	cin >> difficulty;

	//Set the difficulty
	switch (difficulty) {
	case 1:
		rounds = 32;
		break;
	case 2:
		rounds = 64;
		break;
	case 3:
		rounds = 128;
		break;
	case 4:
		rounds = 256;
		break;
	case 5:
		rounds = 512;
	}

	//observe the players first choices
	for (int i = 0; i < rounds; ++i) {
		cout << "You have " << rounds - i << " choices to go; enter M(Maroon), W(White), or B(Black): ";
		char input = 'z';
		cin >> input;
		Choice user = charToChoice(input);	//Take the input (currently char, eventually buttons) and make it a choice
		int calcVal = choiceToInt(user);	//Get the interger value of the choice to be put into the vector
		choices.push_back(calcVal);			//Vector to be used for all observations
	}

	//Where the actual game play happens
	for (int i = 0; i < rounds; ++i) {
		calcProb(choices, probM, probW, probB);			//Use the vector to calculate the probability of each choice
		Choice guess = makeGuess(probM, probW, probB);	//Make the secret guess
		cout << "You have " << rounds - i << " tries left; choose M(Maroon), W(White), or B(Black): ";
		char input = 'z';
		cin >> input;
		Choice user = charToChoice(input);				//Convert input to choice
		bool win = compareChoices(guess, user);			//Check if the user won against the computer
		score = trackScore(win, score);					//Update the score
		guesses = i + 1;
		percentCorrect(win, timesCorrect, guesses);		//display the percent the computer has been correct
		choices.erase(choices.begin());					//Clear the first choice the user made
		choices.push_back(choiceToInt(user));			//Update the choice vector with the most recent choice
	}

	keep_window_open();
}
catch (exception& e) {
	cerr << e.what() << endl;
	return -1;
}
catch (...) {
	cerr << "Unknown exception occured" << endl;
	return -1;
}