
#include "person.h"

#include <algorithm>
#include <iomanip>
#include <numeric>

Person::Person()
    : name(""), surname(""), exam(0), finalGrade(0.0) {
}

Person::Person(const std::string& n,
               const std::string& s,
               const std::vector<int>& hw,
               int e)
    : name(n),
      surname(s),
      homework(hw),
      exam(e),
      finalGrade(0.0) {
}

// Copy constructor
Person::Person(const Person& other)
    : name(other.name),
      surname(other.surname),
      homework(other.homework),
      exam(other.exam),
      finalGrade(other.finalGrade) {
}

// Copy assignment operator
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        name = other.name;
        surname = other.surname;
        homework = other.homework;
        exam = other.exam;
        finalGrade = other.finalGrade;
    }

    return *this;
}

// Destructor
Person::~Person() {
}

double Person::calculateAverage() const {
    if (homework.empty()) {
        return exam;
    }

    double sum = std::accumulate(
        homework.begin(),
        homework.end(),
        0.0
    );

    double average = sum / homework.size();

    return 0.4 * average + 0.6 * exam;
}

double Person::calculateMedian() const {
    if (homework.empty()) {
        return exam;
    }

    std::vector<int> sortedHomework = homework;

    std::sort(
        sortedHomework.begin(),
        sortedHomework.end()
    );

    double median;

    if (sortedHomework.size() % 2 == 0) {
        int middle1 =
            sortedHomework[sortedHomework.size() / 2 - 1];

        int middle2 =
            sortedHomework[sortedHomework.size() / 2];

        median = (middle1 + middle2) / 2.0;
    } else {
        median = sortedHomework[sortedHomework.size() / 2];
    }

    return 0.4 * median + 0.6 * exam;
}

std::string Person::getName() const {
    return name;
}

std::string Person::getSurname() const {
    return surname;
}

// Read a student from a file or input stream
std::istream& operator>>(std::istream& in, Person& student) {
    int numberOfHomework;

    if (!(in >> student.name >> student.surname
             >> numberOfHomework)) {
        return in;
    }

    if (numberOfHomework < 0) {
        in.setstate(std::ios::failbit);
        return in;
    }

    student.homework.clear();

    for (int i = 0; i < numberOfHomework; i++) {
        int grade;

        if (!(in >> grade)) {
            return in;
        }

        student.homework.push_back(grade);
    }

    if (!(in >> student.exam)) {
        return in;
    }

    return in;
}

// Print a student's information
std::ostream& operator<<(std::ostream& out,
                         const Person& student) {
    out << std::left
        << std::setw(15) << student.name
        << std::setw(15) << student.surname
        << std::fixed << std::setprecision(2)
        << student.calculateAverage();

    return out;
}
