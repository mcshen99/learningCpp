#include <iostream>
#include <vector>
#include <random>
#include <time.h>

using namespace std;

int main() {
	const int numCastles = 10;
	const int numSoldiers = 100;
	cout << "Enter your Blotto distribution: ";
	int x;
	int userBlotto[numCastles] = {};
	int sum = 0;
	for (int i = 0; i < numCastles; ++i) {
		cin >> x;
		sum += x;
		userBlotto[i] = x;
	}
	if (sum != numSoldiers) {
		cout << "Your distribution sums to " << sum << ", not " << numSoldiers << ". Run again.";
		return 1;
	}

	default_random_engine generator(clock());
	discrete_distribution<int> distribution {1,2,3,4,5,6,7,8,9,10};

	int computerBlotto[numCastles] = {};
	for (int i = 0; i < numSoldiers; ++i) {
		int number = distribution(generator);
		++computerBlotto[number];
	}

	cout << "Computer's distribution: ";
	for (int i = 0; i < numCastles; ++i) {
		cout << computerBlotto[i] << " ";
	}
	cout << endl;

	cout << "Who won each castle: " << endl;
	int userScore = 0;
	int computerScore = 0;
	for (int i = 0; i < numCastles; ++i) {
		cout << (i + 1) << ": ";
		if (userBlotto[i] > computerBlotto[i]) {
			cout << "user" << endl;
			userScore += (i + 1);
		} else if (computerBlotto[i] > userBlotto[i]) {
			cout << "computer" << endl;
			computerScore += (i + 1);
		} else {
			cout << "tie" << endl;
		}
	}
	cout << "userScore: " << userScore << endl;
	cout << "computerScore: " << computerScore << endl;

	cout << "Final winner: ";
	if (computerScore < userScore) {
		cout << "user" << endl;
	} else if (computerScore > userScore) {
		cout << "computer" << endl;
	} else {
		cout << "tie" << endl;
	}

	return 0;
}