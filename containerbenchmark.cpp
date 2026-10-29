#include "person.h"

#include <algorithm>
#include <chrono>
#include <deque>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;

bool compareStudents(const Person& a, const Person& b) {
    if (a.getSurname() != b.getSurname()) {
        return a.getSurname() < b.getSurname();
    }
    return a.getName() < b.getName();
}

template <typename Container>
void runBenchmark(const string& filename, const string& containerName) {
    Container students;
    size_t passing = 0;
    size_t failing = 0;

    try {
        auto start = steady_clock::now();

        ifstream input(filename);
        if (!input.is_open()) {
            throw runtime_error("Cannot open input file: " + filename);
        }

        Person student;
        while (input >> student) {
            students.push_back(student);
        }

        if (!input.eof()) {
            throw runtime_error("Error reading input file: " + filename);
        }

        if constexpr (is_same_v<Container, list<Person>>) {
            students.sort(compareStudents);
        } else {
            sort(students.begin(), students.end(), compareStudents);
        }

        ofstream passFile("passing_" + containerName + "_" + filename);
        ofstream failFile("failing_" + containerName + "_" + filename);

        if (!passFile.is_open() || !failFile.is_open()) {
            throw runtime_error("Cannot open output files.");
        }

        for (const Person& p : students) {
            if (p.calculateAverage() >= 5.0) {
                passFile << p << '\n';
                ++passing;
            } else {
                failFile << p << '\n';
                ++failing;
            }
        }

        if (!passFile || !failFile) {
            throw runtime_error("Error writing output files.");
        }

        auto end = steady_clock::now();
        double seconds = duration<double>(end - start).count();

        cout << "Container: " << containerName << '\n';
        cout << "Dataset: " << filename << '\n';
        cout << "Students: " << students.size() << '\n';
        cout << "Passing: " << passing << '\n';
        cout << "Failing: " << failing << '\n';
        cout << "Total time: " << seconds << " seconds\n";
        cout << "------------------------------\n";
    } catch (const exception& e) {
        cerr << "Error (" << containerName << ", " << filename
             << "): " << e.what() << '\n';
        throw;
    }
}

int main() {
    const vector<string> files = {
    "students_1000.txt",
    "students_10000.txt",
    "students_100000.txt",
    "students_1000000.txt"
};

    try {
        for (const string& file : files) {
            runBenchmark<vector<Person>>(file, "vector");
            runBenchmark<list<Person>>(file, "list");
            runBenchmark<deque<Person>>(file, "deque");
        }
    } catch (const exception&) {
        return 1;
    }

    return 0;
}