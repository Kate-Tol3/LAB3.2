#ifndef FILEFUNC_H
#define FILEFUNC_H

#include "Sequence/MutableArraySequence.h"
#include "Sequence/Sequence.h"
#include "Student.h"
#include "Pointers/SharedPtr.h"
#include <iostream>
#include <fstream>
#include <sstream>


SharedPtr<Sequence<Student>> ReadStudentsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    SharedPtr<Sequence<Student>> students(new MutableArraySequence<Student>());
    std::string line;

    while (std::getline(file, line)) {
        std::string firstName, lastName, group;
        int id = 0, enrollmentYear = 0;
        std::array<int, 3> birthDate {};

        // пропуск пустых строк
        if (line.empty()) continue;

        try {
            // first_name
            if (line.starts_with("First Name: ")) {
                firstName = line.substr(12); // длина "First Name: "
            } else {
                throw std::runtime_error("Invalid format at First Name");
            }

            // last_name
            if (std::getline(file, line) && line.starts_with("Last Name: ")) {
                lastName = line.substr(11); // длина "Last Name: "
            } else {
                throw std::runtime_error("Invalid format at Last Name");
            }

            // birth_date
            if (std::getline(file, line) && line.starts_with("Birth Date: ")) {
                std::istringstream dateStream(line.substr(12));
                char delimiter;
                if (!(dateStream >> birthDate[0] >> delimiter >> birthDate[1] >> delimiter >> birthDate[2]) || delimiter != '/') {
                    throw std::runtime_error("Invalid birth date format");
                }
            } else {
                throw std::runtime_error("Invalid format at Birth Date");
            }

            // ID
            if (std::getline(file, line) && line.starts_with("ID: ")) {
                id = std::stoi(line.substr(4)); // длина "ID: "
            } else {
                throw std::runtime_error("Invalid format at ID");
            }

            // enrollment_year
            if (std::getline(file, line) && line.starts_with("Enrollment Year: ")) {
                enrollmentYear = std::stoi(line.substr(17)); // длина "Enrollment Year: "
            } else {
                throw std::runtime_error("Invalid format at Enrollment Year");
            }

            // group
            if (std::getline(file, line) && line.starts_with("Group: ")) {
                group = line.substr(7); //длина "Group: "
            } else {
                throw std::runtime_error("Invalid format at Group");
            }

            // пропуск пустой сроки после записи студента
            std::getline(file, line);

            auto student = Student(firstName, lastName, id, birthDate, enrollmentYear, group);
            students->append(student);

        } catch (const std::exception& e) {
            std::cerr << "Error while parsing student data: " << e.what() << "\nLine: " << line << std::endl;
            continue; // пропускаем блок если возникла ошибка
        }
    }

    file.close();
    return students;
}

template<typename T>
void WriteStudentsToFile(const SharedPtr<Sequence<T>>& students, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file" + filename);
    }

    for (int i = 0; i < students->getLength(); ++i) {
        file << (*students)[i] << std::endl;
    }
    file.close();
}

#endif // FILEFUNC_H