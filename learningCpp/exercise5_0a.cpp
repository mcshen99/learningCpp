#include <iostream>
#include "Student_info.h"
#include "grade.h"
#include <vector>
#include <list> 

using namespace std;

int main() {

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