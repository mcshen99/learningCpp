#include <iostream>
#include <random>

using namespace std;

static default_random_engine generator;
static bernoulli_distribution distribution(0.5);

bool fair_coin();
bool biased_coin(double);

int main() {
	int count = 0;
	for (int i = 0; i < 1000; ++i) {
		count = biased_coin(0.8) ? count + 1 : count;
	}
	cout << count << endl;

	count = 0;
	for (int i = 0; i < 1000; ++i) {
		count = biased_coin(0.5) ? count + 1 : count;
	}
	cout << count << endl;

	count = 0;
	for (int i = 0; i < 1000; ++i) {
		count = biased_coin(0.25) ? count + 1 : count;
	}
	cout << count << endl;

	count = 0;
	for (int i = 0; i < 1000; ++i) {
		count = biased_coin(0.75) ? count + 1 : count;
	}
	cout << count << endl;

	count = 0;
	for (int i = 0; i < 1000; ++i) {
		count = biased_coin(0.6) ? count + 1 : count;
	}
	cout << count << endl;

	return 0;
}

bool fair_coin() {
	return distribution(generator);
}

// 0 < p < 1
bool biased_coin(double p) {
	bool alwaysTrue = true;
	while (alwaysTrue) {
		int toss = fair_coin() ? 1 : 0;
		int i = p * 2;
		if (toss == 1) {
			if (i == 1) {
				return true;
			} else {
				return false;
			}
		}
		p = p * 2 - i;
	}

	return true;
}