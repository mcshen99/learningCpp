#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

constexpr int f(int d, int x) {
	return d == 0 ? x : (x % 2 == 1 ? f(d - 1, 3 * x + 1) : f(d - 1, x / 2));
}
vector<long double> randomVector();

int main() {
	long double arr[f(5, 50)];
	for (int i = 0; i < sizeof(arr) / sizeof(*arr); ++i) {
		arr[i] = 1;
	}

	auto randVect = randomVector();

	long double sum1 = 0;
	for (auto e1 : randVect) {
		sum1 += e1;
	}
	long double sum2 = 0;
	for (auto i : arr) {
		sum2 += i;
	}
	cout << sum1 << endl;
	cout << sum2 << endl;

	return 0;
}

//6.5.2, 2.5.4 for constexpr
//p. 68 for auto

vector<long double> randomVector() {
	return{ 2.718281828459l, 3.1415926535l, sqrt(2) };
}