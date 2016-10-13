#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include "grade.h"
#include "Student_info.h"
#include "median.h"

using namespace std;

int main() {
	list<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0;

	while (read(cin, record)) {
		maxlen = max(maxlen, record.name.size());
		students.push_back(record);
	}
	students.sort(compare);

	for (list<Student_info>::const_iterator it = students.begin(); it != students.end(); ++it) {
		cout << (*it).name << string(maxlen + 1 - (*it).name.size(), ' ');

		try {
			double final_grade = grade(*it);
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << setprecision(prec);
		} catch (domain_error e) {
			cout << e.what();
		}

		cout << endl;
	}

	extract_fails(students);
	for (list<Student_info>::const_iterator it = students.begin(); it != students.end(); ++it) {
		cout << (*it).name << endl;
	}

	return 0;
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

list<Student_info> extract_fails(list <Student_info>& students) {
	list<Student_info> fail;
	list<Student_info>::iterator iter = students.begin();
	
	while (iter != students.end()) {
		if (fgrade(*iter)) {
			fail.push_back(*iter);
			iter = students.erase(iter);
		} else {
			++iter;
		}
	}

	return fail;
}