#ifndef GUARD_Triangle
#define GUARD_Triangle

#include <iostream>

struct Triangle {
	int s1, s2, s3;
	int perimeter;
	int squareAreaX16;
};

int getPerimeter(Triangle&);
int getSquareAreaX16(Triangle&);
bool compare(const Triangle&, const Triangle&);
std::istream& read(std::istream&, Triangle&);

#endif