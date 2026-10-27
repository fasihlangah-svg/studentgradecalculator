#include "person.h"
#include "studentprocessor.h"

#include <chrono>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main() {
    const std::vector<std::string> files = {
        "students_1000.txt",
        "students_10000.txt",
        "students_100000.txt",
        "students_1000000.txt"
    };

    for (const std::string& filename : files) {
        std::vector<Person> students;
        std::vector<Person> passing;
        std::vector<Person> failing;

        try {
            const auto start = std::chrono::steady_clock::now();

            // 1. Read student records.
            StudentProcessor::readFromFile(students, filename);

            // 2. Sort students.
            StudentProcessor::sortStudents(students);

            // 3. Split students into passing and failing groups.
            StudentProcessor::splitStudents(students, passing, failing);

            // 4. Write the results to separate files.
            const std::string passingFile = "passing_" + filename;
            const std::string failingFile = "failing_" + filename;

            StudentProcessor::writeResults(
                passing, failing, passingFile, failingFile
            );

            const auto end = std::chrono::steady_clock::now();

            const double elapsedSeconds =
                std::chrono::duration<double>(end - start).count();

            std::cout << "Dataset: " << filename << '\n';
            std::cout << "Students read: " << students.size() << '\n';
            std::cout << "Passing: " << passing.size() << '\n';
            std::cout << "Failing: " << failing.size() << '\n';
            std::cout << "Total pipeline time: "
                      << elapsedSeconds << " seconds\n";
            std::cout << "------------------------------\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error processing " << filename
                      << ": " << e.what() << '\n';
            return 1;
        }
    }

    return 0;
}