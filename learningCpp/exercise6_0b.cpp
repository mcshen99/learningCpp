#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <numeric>
#include <iterator>
#include "grade.h"
#include "Student_info.h"
#include "median.h"

using namespace std;

bool did_all_hw(const Student_info&);
double median_analysis(const vector<Student_info>&);
void write_analysis(ostream& out, const string& name, double analysis(const vector<Student_info>&), const vector<Student_info>& did, const vector<Student_info>& didnt);
double average_analysis(const vector<Student_info>&);
double optimistic_median_analysis(const vector<Student_info>&);

int main() {
	vector<Student_info> did, didnt;

	Student_info student;
	while (read(cin, student)) {
		if (did_all_hw(student)) {
			did.push_back(student);
		} else {
			didnt.push_back(student);
		}
	}
	
	if (did.empty()) {
		cout << "No student did all the homework!" << endl;
		return 1;
	}
	if (didnt.empty()) {
		cout << "Every student did all the homework!" << endl;
		return 1;
	}

	write_analysis(cout, "median", median_analysis, did, didnt);
	write_analysis(cout, "average", average_analysis, did, didnt);
	write_analysis(cout, "median of homework turned in", optimistic_median_analysis, did, didnt);

	return 0;
}

bool did_all_hw(const Student_info& s) {
	return ((find(s.homework.begin(), s.homework.end(), 0)) == s.homework.end());
}

double average(const vector<double>& v) {
	return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double average_grade(const Student_info& s) {
	return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const vector<Student_info>& students) {
	vector<double> grades;

	transform(students.begin(), students.end(), back_inserter(grades), average_grade);

	return median(grades);
}

double optimistic_median(const Student_info& s) {
	vector<double> nonzero;
	remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0);

	if (nonzero.empty()) {
		return grade(s.midterm, s.final, 0);
	} else {
		return grade(s.midterm, s.final, median(nonzero));
	}
}

double optimistic_median_analysis(const vector<Student_info>& students) {
	vector<double> grades;

	transform(students.begin(), students.end(), back_inserter(grades), optimistic_median);

	return median(grades);
}

double median(vector<double> vec) {
	typedef vector<double>::size_type vec_sz;
	vec_sz size = vec.size();
	if (size == 0) {
		throw domain_error("median of an empty vector");
	}
	sort(vec.begin(), vec.end());

	vec_sz mid = size / 2;
	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

double grade_aux(const Student_info& s) {
	try {
		return grade(s);
	} catch (domain_error) {
		return grade(s.midterm, s.final, 0);
	}
}

double median_analysis(const vector <Student_info>& students) {
	vector<double> grades;

	transform(students.begin(), students.end(), back_inserter(grades), grade_aux);

	return median(grades);
}

void write_analysis(ostream& out, const string& name, double analysis(const vector<Student_info>&), const vector<Student_info>& did, const vector<Student_info>& didnt) {
	out << name << ": median(did) = " << analysis(did) << ", median(didnt) = " << analysis(didnt) << endl;
}

double grade(double midterm, double final, double homework) {
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double>& hw) {
	if (hw.size() == 0) {
		throw domain_error("student has done no homework");
	}
	return grade(midterm, final, median(hw));
}

istream& read_hw(istream& in, vector<double>& hw) {
	if (in) {
		hw.clear();

		double x;
		while (in >> x) {
			hw.push_back(x);
		}

		in.clear();
	}
	return in;
}

istream& read(istream& is, Student_info& s) {
	is >> s.name >> s.midterm >> s.final;

	read_hw(is, s.homework);
	return is;
}

double grade(const Student_info& s) {
	return grade(s.midterm, s.final, s.homework);
}

bool compare(const Student_info& x, const Student_info& y) {
	return x.name < y.name;
}

bool fgrade(const Student_info& s) {
	return grade(s) < 60;
}

bool pgrade(const Student_info& s) {
	return !fgrade(s);
}

vector<Student_info> extract_fails(vector <Student_info>& students) {
	vector<Student_info>::iterator iter = stable_partition(students.begin(), students.end(), pgrade);
	vector<Student_info> fail(iter, students.end());
	students.erase(iter, students.end());

	return fail;
}