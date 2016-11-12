#include "Student_info_2.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "grade_2.h"

using namespace std;

istream& read_hw(istream&, vector<double>&);
double median(vector<double>);

double Student_info::grade() const {
	return ::grade(midterm, final, homework);
}

istream& Student_info::read(istream& in) {
	in >> n >> midterm >> final;
	read_hw(in, homework);
	return in;
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

double grade(double midterm, double final, double homework) {
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double>& hw) {
	if (hw.size() == 0) {
		throw domain_error("student has done no homework");
	}
	return grade(midterm, final, median(hw));
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

bool compare(const Student_info& x, const Student_info& y) {
	return x.name() < y.name();
}

Student_info::Student_info() : midterm(0), final(0) { }

Student_info::Student_info(istream& is) { read(is); }

int main() {
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0;

	while (record.read(cin)) {
		maxlen = max(maxlen, record.name().size());
		students.push_back(record);
	}

	sort(students.begin(), students.end(), compare);

	for (vector<Student_info>::size_type i = 0; i != students.size(); ++i) {
		cout << students[i].name() << string(maxlen + 1 - students[i].name().size(), ' ');
		try {
			double final_grade = students[i].grade();
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << setprecision(prec) << endl;
		} catch (domain_error e) {
			cout << e.what() << endl;
		}
	}

	return 0;
}
