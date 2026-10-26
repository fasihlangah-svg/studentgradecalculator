#include "studentprocessor.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>

bool StudentProcessor::compareStudents(
    const Person& a,
    const Person& b
) {
    if (a.getSurname() == b.getSurname()) {
        return a.getName() < b.getName();
    }

    return a.getSurname() < b.getSurname();
}

bool StudentProcessor::readFromFile(
    std::vector<Person>& students,
    const std::string& filename
) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Could not open file: " + filename
        );
    }

    students.clear();

    Person student;

    while (file >> student) {
        students.push_back(student);
    }

    if (!file.eof()) {
        throw std::runtime_error(
            "Error reading file: " + filename
        );
    }

    return true;
}

void StudentProcessor::sortStudents(
    std::vector<Person>& students
) {
    std::sort(
        students.begin(),
        students.end(),
        StudentProcessor::compareStudents
    );
}