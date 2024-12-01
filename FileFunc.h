#ifndef FILEFUNC_H
#define FILEFUNC_H

#include "Sequence/MutableArraySequence.h"
#include "Sequence/Sequence.h"
#include "Student.h"
#include "Pointers/SharedPtr.h"
#include <iostream>
#include <fstream>
#include <sstream>


// SharedPtr<Sequence<Student>> ReadStudentsFromFile(const std::string& filename) {
//     std::ifstream file(filename);
//     if (!file.is_open()) {
//         throw std::runtime_error("Could not open file: " + filename);
//     }
//
//     SharedPtr<Sequence<Student>> students(new MutableArraySequence<Student>());
//     std::string line;
//
//     while (std::getline(file, line)) {
//         std::istringstream iss(line);
//         char firstName[256], lastName[256], group[256];
//         int id,  enrollmentYear;
//         std::array<int, 3> date{};
//
//         if (iss >> firstName >> lastName >> id >> date[0] >> date[1] >> date[2] >> enrollmentYear >> group) {
//
//             auto student = Student (firstName, lastName, id, date, enrollmentYear, group);
//             students->append(student);
//
//         } else {
//             std::cerr << "Error while parsing line: " << line << std::endl;
//             continue;
//         }
//     }
//
//     file.close();
//     return students;
// }

SharedPtr<Sequence<Student>> ReadStudentsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    SharedPtr<Sequence<Student>> students(new MutableArraySequence<Student>());
    std::string line;

    while (std::getline(file, line)) {
        // Переменные для хранения данных студента
        std::string firstName, lastName, group;
        int id = 0, enrollmentYear = 0;
        std::array<int, 3> birthDate = {0, 0, 0};

        // Пропускаем пустые строки
        if (line.empty()) continue;

        try {
            // Читаем строку с именем
            if (line.starts_with("First Name: ")) {
                firstName = line.substr(12); // 12 символов - длина "First Name: "
            } else {
                throw std::runtime_error("Invalid format at First Name");
            }

            // Читаем строку с фамилией
            if (std::getline(file, line) && line.starts_with("Last Name: ")) {
                lastName = line.substr(11); // 11 символов - длина "Last Name: "
            } else {
                throw std::runtime_error("Invalid format at Last Name");
            }

            // Читаем строку с датой рождения
            if (std::getline(file, line) && line.starts_with("Birth Date: ")) {
                std::istringstream dateStream(line.substr(12));
                char delimiter;
                if (!(dateStream >> birthDate[0] >> delimiter >> birthDate[1] >> delimiter >> birthDate[2]) || delimiter != '/') {
                    throw std::runtime_error("Invalid birth date format");
                }
            } else {
                throw std::runtime_error("Invalid format at Birth Date");
            }

            // Читаем строку с ID
            if (std::getline(file, line) && line.starts_with("ID: ")) {
                id = std::stoi(line.substr(4)); // 4 символа - длина "ID: "
            } else {
                throw std::runtime_error("Invalid format at ID");
            }

            // Читаем строку с годом зачисления
            if (std::getline(file, line) && line.starts_with("Enrollment Year: ")) {
                enrollmentYear = std::stoi(line.substr(17)); // 17 символов - длина "Enrollment Year: "
            } else {
                throw std::runtime_error("Invalid format at Enrollment Year");
            }

            // Читаем строку с группой
            if (std::getline(file, line) && line.starts_with("Group: ")) {
                group = line.substr(7); // 7 символов - длина "Group: "
            } else {
                throw std::runtime_error("Invalid format at Group");
            }

            // Пропускаем пустую строку после записи студента
            std::getline(file, line); // Если строка есть, она будет проигнорирована

            // Создаем объект студента и добавляем в последовательность
            auto student = Student(firstName, lastName, id, birthDate, enrollmentYear, group);
            students->append(student);

        } catch (const std::exception& e) {
            std::cerr << "Error while parsing student data: " << e.what() << "\nLine: " << line << std::endl;
            continue; // Пропускаем этот студентский блок
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
        file << (*students)[i] << std::endl;///
    }
    file.close();
}

#endif // FILEFUNC_H