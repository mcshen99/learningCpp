#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int largest = 100000;
const long long infinity = 40000000;
int N;
long long produce[largest];
long long forwards[largest];
long long backwards[largest];
long long minBack[largest];

bool works(int);

int main() {
	ifstream f("sabotage.in");
	ofstream out("sabotage.out");

	f >> N;

	for (int i = 0; i < N; ++i) {
		f >> produce[i];
	}

	long long a = 0;
	long long b = infinity;
	while (a < b) {
		//cout << a << " " << b << endl;
		long long mid = (a + b) / 2;
		if (works(mid)) {
			b = mid;
		} else {
			a = mid + 1;
		}
	}

	out << fixed << setprecision(3) << round((a - 1) / 4.0) / 1000.0 << endl;
	out.close();

	return 0;
}

bool works(int ave) {
	long long sum = 0;
	for (int i = 0; i < N; ++i) {
		sum += produce[i] * 4000 - ave;
		forwards[i] = sum;
	}
	sum = 0;
	for (int i = N - 1; i >= 0; --i) {
		sum += produce[i] * 4000 - ave;
		backwards[i] = sum;
	}

	long long minB = infinity;
	for (int i = N - 1; i >= 0; --i) {
		if (backwards[i] < minB) {
			minB = backwards[i];
		}
		minBack[i] = minB;
	}

	long long minS = infinity;
	for (int i = 0; i < N - 2; ++i) {
		if (forwards[i] + minBack[i + 2] < minS) {
			minS = forwards[i] + minBack[i + 2];
		}
	}

	//cout << "x " << ave << " " << minS << endl;
	if (minS <= 0) {
		return true;
	} else {
		return false;
	}
}