#include <iostream>

int main() {
	std::cout << "Enter first integer: ";
	int n1;
	std::cin >> n1;
	std::cout << "Enter second integer: ";
	int n2;
	std::cin >> n2;
	int max;
	if (n1 > n2) {
		max = n1;
	}
	else {
		max = n2;
	}

	std::cout << max << " is larger." << std::endl;
	return 0;
}