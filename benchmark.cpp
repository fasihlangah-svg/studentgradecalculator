#include "datasetgenerator.h"

#include <iostream>
#include <exception>

int main() {
    try {
        std::cout << "Generating test datasets...\n";

        DatasetGenerator::generateFile("students_1000.txt", 1000);
        std::cout << "Created dataset: 1,000 students\n";

        DatasetGenerator::generateFile("students_10000.txt", 10000);
        std::cout << "Created dataset: 10,000 students\n";

        DatasetGenerator::generateFile("students_100000.txt", 100000);
        std::cout << "Created dataset: 100,000 students\n";

        DatasetGenerator::generateFile("students_1000000.txt", 1000000);
        std::cout << "Created dataset: 1,000,000 students\n";

        //DatasetGenerator::generateFile("students_10000000.txt", 10000000);
        //std::cout << "Created dataset: 10,000,000 students\n";

        std::cout << "\nAll datasets generated successfully!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}