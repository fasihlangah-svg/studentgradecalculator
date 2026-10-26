
#pragma once

#include <string>
#include <vector>
#include <iostream>

class Person {
private:
    std::string name;
    std::string surname;
    std::vector<int> homework;
    int exam;
    double finalGrade;

public:
    Person();

    Person(const std::string& n,
           const std::string& s,
           const std::vector<int>& hw,
           int e);

    // Rule of Three
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();

    double calculateAverage() const;
    double calculateMedian() const;

    std::string getName() const;
    std::string getSurname() const;

    friend std::istream& operator>>(std::istream& in,
                                    Person& student);

    friend std::ostream& operator<<(std::ostream& out,
                                    const Person& student);
};
