#include <vector>
#include <memory>
#include <iostream>

using namespace std;

shared_ptr<vector<int>> make() {
	return make_shared<vector<int>>();
}

shared_ptr<vector<int>> read(shared_ptr<vector<int>> p) {
	cout << "Enter values: " << endl;
	int x;

	while (cin >> x) {
		p->push_back(x);
	}

	return p;
}

void print(shared_ptr<vector<int>> p) {
	for (int i : *p) {
		cout << i << " ";	
	}
}

int main() {
	auto p = read(make());
	print(p);

	return 0;
}