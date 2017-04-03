Probability::Probability(double prob = 0.0, Choice check = Choice::M) {
	probability = prob;
	guess = check;
}

double Probability::getProb() {
	return probability;
}

Choice Probability::getChoice() {
	return guess;
}

void calcProb(const vector<int>& choices, double& probM, double& probW, double& probB) {
	int timesMSelected = 0;
	int timesWSelected = 0;
	int timesBSelected = 0;

	for (unsigned int i = 0; i < choices.size(); ++i) {
		switch (choices[i]) {
		case 1:
			++timesMSelected;
			break;
		case 2:
			++timesWSelected;
			break;
		case 3:
			++timesBSelected;
			break;
		}
	}
	probM = static_cast<double>(timesMSelected) / choices.size();
	probW = static_cast<double>(timesWSelected) / choices.size();
	probB = static_cast<double>(timesBSelected) / choices.size();
}

Choice makeGuess(const double& probM, const double& probW, const double& probB) {
	vector<Probability> probs;
	Probability ProM{ probM, Choice::M };
	Probability ProW{ probW, Choice::W };
	Probability ProB{ probB, Choice::B };
	probs.push_back(ProM);
	probs.push_back(ProW);
	probs.push_back(ProB);
	sort(probs.begin(), probs.end(), sortFun);
	int selection = rand() % 100;
	Probability select1{ 100 * probs[0].getProb(), probs[0].getChoice() };
	Probability select2{ 100 * (probs[1].getProb() + probs[0].getProb()), probs[1].getChoice() };
	Probability select3{ 100 * (probs[2].getProb() + probs[1].getProb() + probs[0].getProb()), probs[2].getChoice() };
	if (selection == 0) {
		return select3.getChoice();
	}
	if (selection <= select1.getProb()) {
		return select1.getChoice();
	}
	if (selection <= select2.getProb()) {
		return select2.getChoice();
	}
	if (selection <= select3.getProb()) {
		return select3.getChoice();
	}
}

int choiceToInt(Choice user) {
	if (user == Choice::M) return 1;
	if (user == Choice::W) return 2;
	if (user == Choice::B) return 3;
}

Choice charToChoice(char input) {
	if (input == 'M') return Choice::M;
	if (input == 'W') return Choice::W;
	if (input == 'B') return Choice::B;
}

bool compareChoices(Choice guess, Choice user) {
	if (guess == user) return false;
	else return true;
}

int trackScore(bool win, int score) {
	if (win == true) {
		cout << "Wow! you outsmarted me! you get 10 points!" << endl;
		return score + 10;
	}
	else {
		cout << "Ha! you thought you could win! try agian." << endl;
		return score;
	}
}

void percentCorrect(bool win, double& timesCorrect, int& guesses) {
	if (win == false) {
		++timesCorrect;
	}
	double percent = 100.0 * (timesCorrect / guesses);
	cout << "So far, I've been right " << percent << "% of the time!" << endl;
	return;
}