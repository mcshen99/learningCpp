#pragma once

#include <string>
#include <vector>

class Student_info {
public:
	Student_info();
	Student_info(std::istream&);
	std::istream& read(std::istream&);
	double grade() const;
	std::string name() const { return n; }
	bool valid() const { return !homework.empty(); }

private: 
	std::string n;
	double midterm, final;
	std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);
