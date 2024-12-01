#include "Student.h"


#include "Student.h"
#include <cstring>
#include <limits>
// #include <iomanip>
#include <iostream>
#include <sstream>


// проверка что строка содержит только буквы
bool isAlpha(const std::string& str) {
    for (char ch : str) {
        if (!std::isalpha(ch) && !std::isspace(ch)) { //static_cast<unsigned char>(ch)
            return false;
        }
    }
    return true;
}

// проверка что строка содержит только цифры
bool isNumeric(const std::string& str) {
    for (char ch : str) {
        if (!std::isdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}


///////// методы структуры Date ///////////////////////////////////////////
bool Date::isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) return false; // проверка месяца
    const int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // дней в месяцах
    bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));// проверка високосного года для февраля
    int maxDays = (month == 2 && isLeapYear) ? 29 : daysInMonth[month - 1];
    return day >= 1 && day <= maxDays;// проверка дня
}

std::istream& operator>>(std::istream& is, Date& date) {
    int d, m, y;
    char separator1;

   // std::cout << "Enter date (format: DD/MM/YYYY): ";
    while (true) {
        if ((is >> d >> separator1 >> m >> separator1 >> y) && (separator1 == '/')
           && Date::isValidDate(d, m, y)) {
            date.date[0] = d;
            date.date[1] = m;
            date.date[2] = y;
            break;\
            }
        else {
                is.clear(); // Сброс флагов ошибок
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка ошибочного ввода
                std::cout << "Invalid date. Please enter a valid date (format: DD/MM/YYYY): ";
            }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << (date.date[0] < 10 ? "0" : "") << date.date[0] << "/"
       << (date.date[1] < 10 ? "0" : "") << date.date[1] << "/"
       << date.date[2];
    return os;
}

////// методы класса Person////////////////////////////////////////
Person::Person() : ID(0), birth_date(std::array<int, 3>{{0, 0, 0}}) {
    std::array<int, 3> temp {{0, 0, 0}};
    birth_date = Date(temp);
}// ?

Person::Person(const std::string& firstName, const std::string& lastName, int id, const std::array<int, 3>& dateArray) :
    first_name(firstName), last_name(lastName), ID(id), birth_date(dateArray) {}

Person::~Person() = default;

Person::Person(const Person& other): first_name(other.first_name), last_name(other.last_name), ID(other.ID),
    birth_date(other.birth_date) {}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        first_name = other.first_name;
        last_name = other.last_name;
        ID = other.ID;
        birth_date = other.birth_date;
    }
    return *this;
}

std::istream& operator>>(std::istream& is, Person& person) {
    std::string buffer;
    std::cout << "Enter first name:";
    while (true) {
        is >> buffer;
        if (isAlpha(buffer)) break; // проверка, что в имени только буквы и пробелы
        std::cout << "Invalid input. Please enter a valid first name (only letters and space):\n";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    person.first_name = buffer;
    buffer.clear();

    std::cout << "Enter last name:";
    while (true) {
        is >> buffer;
        if (isAlpha(buffer)) break; // проверка, что в фамилии нет цифр
        std::cout << "Invalid input. Please enter a valid last name (only letters and space):\n";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    person.last_name = buffer;
    buffer.clear();

    std::cout << "Enter birth date (format: DD/MM/YYYY):";
    is >> person.birth_date; // ввод даты через перегруженный оператор

    std::cout << "Enter ID:";
    while (true) {
        is >> buffer;
        if (isNumeric(buffer)) {
            // Конвертируем строку в целое число
            person.ID = std::stoi(buffer);
            if (person.ID >= 0) break; // Проверка на неотрицательность
        }
        is.clear();  // Сброс флагов ошибок
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очистка ошибочного ввода
        std::cout << "Invalid input. Please enter a valid non-negative ID (only digits): ";
    }
    buffer.clear();

    return is;
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "First Name: " << person.first_name << "\n";
    os << "Last Name: " << person.last_name << "\n";
    os << "Birth Date: " << person.birth_date << "\n";
    os << "ID: " << person.ID << "\n";
    return os;
}

std::istream& inputFromFile(std::istream& is, Person& person) {
    std::string firstName, lastName;
    int id;
    std::array<int, 3> date{};

    if (is >> firstName >> lastName >> id >> date[0] >> date[1] >> date[3]) {
        person = Person(firstName, lastName, id, date);
    } else {
        is.clear();
        is.setstate(std::ios::failbit);
        throw std::runtime_error("Ошибка чтения данных для Person из файла.");
    }

    return is;
}

////////// методы для класса Student /////////////////////////////
Student::Student() : Person(), enrollment_year(0), group(){}

Student::Student(const std::string& firstName, const std::string& lastName, int id,
    const std::array<int, 3>& dateArray, int year, const std::string& group):
Person(firstName, lastName, id, dateArray), enrollment_year(year), group(group) {}

Student::Student(const Student& other) : Person(other), enrollment_year(other.enrollment_year), group(other.group) {}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        Person::operator=(other);
        enrollment_year = other.enrollment_year;
        group = other.group;
    }
    return *this;
}

std::istream& operator>>(std::istream& is, Student& student) {

    is >> static_cast<Person&>(student); // ввод полей для класса Person
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка оставшихся символов в буфере после ввода Person

    std::string buffer;
    std::cout << "Enter enrollment year:";
    while (true) {
        std::getline(is, buffer);
        if (isNumeric(buffer)) {
            if (std::stoi(buffer) >= 0) break; // Проверка на неотрицательность
        }
        std::cout << "Invalid input. Please enter a valid non-negative enrollment year: ";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    student.enrollment_year = std::stoi(buffer);


    std::cout << "Enter group:";
    std::getline(is, student.group);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {

    os << static_cast<const Person&>(student);// вывод полей для класса Person

    os << "Enrollment Year: " << student.enrollment_year << "\n";
    os << "Group: " << student.group << "\n";
    return os;
}

std::istream& inputFromFile(std::istream& is, Student& student) {

    std::string firstName, lastName, group;
    int id, enrollmentYear;
    std::array<int, 3> date{};

    if (is >> firstName >> lastName >> id >> date[0] >> date[1] >> date[3] >> enrollmentYear >> group) {
        student = Student(firstName, lastName, id, date, enrollmentYear, group);
    } else {
        is.clear();
        is.setstate(std::ios::failbit);
        throw std::runtime_error("Ошибка чтения данных для Person из файла.");
    }

    return is;
}

//  std::istream& inputFromFile(std::istream& is, Student& student) {
//     std::string line, firstName, lastName,group;
//     int id, enrollmentYear;
//     std::array<int, 3> date{};
//
//     auto readField = [&](const std::string& prefix, auto& value) {
//         return std::getline(is, line) && line.starts_with(prefix) &&
//                std::istringstream(line.substr(prefix.size())) >> value;
//     };
//
//     auto readDate = [&](const std::string& prefix, int& d, int& m, int& y) {
//         char delim1, delim2;
//         return std::getline(is, line) && line.starts_with(prefix) &&
//                std::istringstream(line.substr(prefix.size())) >> d >> delim1 >> m >> delim2 >> y &&
//                delim1 == '/' && delim2 == '/' && d > 0 && d <= 31 && m > 0 && m <= 12;
//     };
//
//     if (readField("First Name: ", firstName) &&
//         readField("Last Name: ", lastName) &&
//         readDate("Birth Date: ", date[0], date[1], date[2]) &&
//         readField("ID: ", id) &&
//         readField("Enrollment Year: ", enrollmentYear) &&
//         readField("Group: ", group)) {
//         student = Student(firstName, lastName, id, {date[0], date[1], date[2]}, enrollmentYear, group);
//
//         // Ensure an empty line follows the student dat
//     if (std::getline(is, line) && line.empty()) {
//         return is;
//     }
//     else {
//         is.clear();
//         is.setstate(std::ios::failbit);
//         throw std::runtime_error("Ошибка чтения данных для Person из файла.");
//     }
// }



