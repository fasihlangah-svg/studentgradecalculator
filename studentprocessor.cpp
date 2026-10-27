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
void StudentProcessor::splitStudents(
    const std::vector<Person>& students,
    std::vector<Person>& passing,
    std::vector<Person>& failing
) {
    passing.clear();
    failing.clear();

    for (const Person& student : students) {
        if (student.calculateAverage() < 5.0) {
            failing.push_back(student);
        } else {
            passing.push_back(student);
        }
    }
}

void StudentProcessor::writeResults(
    const std::vector<Person>& passing,
    const std::vector<Person>& failing,
    const std::string& passingFile,
    const std::string& failingFile
) {
    std::ofstream passingOutput(passingFile);
    if (!passingOutput.is_open()) {
        throw std::runtime_error(
            "Could not open passing-students output file: " + passingFile
        );
    }

    std::ofstream failingOutput(failingFile);
    if (!failingOutput.is_open()) {
        throw std::runtime_error(
            "Could not open failing-students output file: " + failingFile
        );
    }

    for (const Person& student : passing) {
        passingOutput << student << '\n';
    }

    for (const Person& student : failing) {
        failingOutput << student << '\n';
    }

    if (!passingOutput || !failingOutput) {
        throw std::runtime_error("Error writing student results to files.");
    }
}