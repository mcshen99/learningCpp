//Write a program that reads in triangles defined by their side lengths (all integers), 
//sorts them by area, and then prints out each triangle’s side lengths, perimeter and area squared * 16 
//(hint: use Heron’s formula, there’s also no need to use doubles). Write some test cases.

#include <iostream>
#include <vector>
#include "Triangle.h"
#include <algorithm>

using namespace std;

int main() {
	vector<Triangle> triangles;
	Triangle t;

	while (read(cin, t)) {
		t.perimeter = getPerimeter(t);
		t.squareAreaX16 = getSquareAreaX16(t);
		triangles.push_back(t);
	}
	sort(triangles.begin(), triangles.end(), compare);

	for (vector<Triangle>::size_type i = 0; i != triangles.size(); ++i) {
		t = triangles[i];
		cout << "side lengths: " << t.s1 << ", " << t.s2 << ", " << t.s3
			<< "; perimeter: " << t.perimeter << "; area squared: " << t.squareAreaX16 << endl;
	}
	return 0;
}

istream& read(istream& is, Triangle& t) {
	is >> t.s1 >> t.s2 >> t.s3;

	return is;
}

int getPerimeter(Triangle& t) {
	int perimeter = t.s1 + t.s2 + t.s3;
	return perimeter;
}

int getSquareAreaX16(Triangle& t) {
	int p = getPerimeter(t);
	int squareAreaX16 = p * (p - 2 * t.s1) * (p - 2 * t.s2) * (p - 2 * t.s3);
	return squareAreaX16;
}

bool compare(const Triangle& t1, const Triangle& t2) {
	return t1.squareAreaX16 < t2.squareAreaX16;
}

ostream& print(ostream& os, const Triangle& t) {
	os << "side lengths: " << t.s1 << ", " << t.s2 << ", " << t.s3
		<< "; perimeter: " << t.perimeter << "; area squared: " << t.squareAreaX16 << endl;

	return os;
}