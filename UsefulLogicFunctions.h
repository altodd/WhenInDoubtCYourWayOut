#include "std_lib_facilities_4.h"

enum class Choice {
	M = 1, W = 2, B = 3
};

class Probability {
public:
	Probability(double prob, Choice check);
	double getProb();
	Choice getChoice();
private:
	double probability;
	Choice guess;
};

void calcProb(const vector<int>& choices, double& probM, double& probW, double& probB);

bool sortFun(Probability i, Probability j) {
	return i.getProb() < j.getProb();
}

Choice makeGuess(const double& probM, const double& probW, const double& probB);

int choiceToInt(Choice user);

Choice charToChoice(char input);

bool compareChoices(Choice guess, Choice user);

int trackScore(bool win, int score);

void percentCorrect(bool win, double& timesCorrect, int& guesses);