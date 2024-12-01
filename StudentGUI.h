#ifndef GUI_H
#define GUI_H
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include <QSpinBox>
#include <QMessageBox>
#include <QFileDialog>

#include <iostream>

#include "Student.h"
#include "Sort/ISorter.h"
#include "Sort/BubbleSort.h"
#include "Sort/HeapSort.h"
#include "Sort/BinaryInsertionSort.h"
#include "Sort/InsertionSort.h"
#include "Sort/QuickSort.h"
#include "Sort/SelectionSort.h"
#include "Sort/ShellSort.h"
#include "Sort/MergeSort.h"
#include "Sort/ShakerSort.h"
#include "Sequence/MutableArraySequence.h"
#include "Sequence/MutableListSequence.h"
#include "FileFunc.h"


class StudentGUI : public QWidget {
    signals:
        void dummySignal();
private:
    QLineEdit* firstNameEdit;
    QLineEdit* lastNameEdit;
    QLineEdit* idEdit;
    QLineEdit* groupEdit;//
    QSpinBox* birthDateDaySpinBox;
    QSpinBox* birthDateMonthSpinBox;
    QSpinBox* birthDateYearSpinBox;
    QSpinBox* enrollmentYearSpinBox;
    QPushButton* addStudentButton;
    QListWidget* studentListWidget;

    QComboBox* sorterComboBox;
    QComboBox* comparatorComboBox;
    QComboBox* sequenceComboBox;

    QPushButton* sortButton;
    QListWidget* sortedStudentListWidget;

    SharedPtr<Sequence<Student>> studentSequence;

    void displayErrorMessage(const QString& message) {
        QMessageBox::critical(this, "Error", message);
    }

    void displayStudentData(const Student& student, QListWidget* listWidget) {
        std::string firstName = student.getFirstName();
        std::string lastName = student.getLastName();

        listWidget->addItem(QString::fromStdString(
            firstName + " " +
            lastName + ", ID: " +
            std::to_string(student.getID()) + ", Birth Date: " +
            std::to_string(student.getBirthDate()[0]) + "/" +
            std::to_string(student.getBirthDate()[1]) + "/" +
            std::to_string(student.getBirthDate()[2]) + ", Enrollment Year: " +
            std::to_string(student.getEnrollmentYear()) + ", Group: " +
            student.getGroup()//
        ));
    }

public:
    StudentGUI(QWidget* parent = nullptr) : QWidget(parent), studentSequence(new MutableArraySequence<Student>()) {

        firstNameEdit = new QLineEdit();
        lastNameEdit = new QLineEdit();
        idEdit = new QLineEdit();
        birthDateDaySpinBox = new QSpinBox();  birthDateDaySpinBox->setRange(1, 31);
        birthDateMonthSpinBox = new QSpinBox(); birthDateMonthSpinBox->setRange(1, 12);
        birthDateYearSpinBox = new QSpinBox(); birthDateYearSpinBox->setRange(1900, 2024);
        enrollmentYearSpinBox = new QSpinBox(); enrollmentYearSpinBox->setRange(0, 2025);
        groupEdit = new QLineEdit();

        birthDateDaySpinBox->setValue(1);
        birthDateMonthSpinBox->setValue(1);
        birthDateYearSpinBox->setValue(2000);

        addStudentButton = new QPushButton("Add Student");
        studentListWidget = new QListWidget();

        sorterComboBox = new QComboBox();
        sorterComboBox->addItem("Bubble Sort");
        sorterComboBox->addItem("Heap Sort");
        sorterComboBox->addItem("Insertion Sort");
        sorterComboBox->addItem("BinaryInsertion Sort");
        sorterComboBox->addItem("Quick Sort");
        sorterComboBox->addItem("Shaker Sort");
        sorterComboBox->addItem("Selection Sort");
        sorterComboBox->addItem("Merge Sort");
        sorterComboBox->addItem("Shell Sort");

        comparatorComboBox = new QComboBox();
        comparatorComboBox->addItem("By ID");
        comparatorComboBox->addItem("By Enrollment year");//
        comparatorComboBox->addItem("By First Name");
        comparatorComboBox->addItem("By Last Name");
        comparatorComboBox->addItem("By Group");//
        comparatorComboBox->addItem("By Birth Date");//


        sequenceComboBox = new QComboBox();
        sequenceComboBox->addItem("Array Sequence");
        sequenceComboBox->addItem("List Sequence");

        int initialSequenceType = sequenceComboBox->currentIndex();

        if (initialSequenceType == 0) {
            studentSequence = SharedPtr<Sequence<Student>>(new MutableArraySequence<Student>());
        } else {
            studentSequence = SharedPtr<Sequence<Student>>(new MutableListSequence<Student>());
        }

        sortButton = new QPushButton("Sort");
        sortedStudentListWidget = new QListWidget();

        QVBoxLayout* mainLayout = new QVBoxLayout();

        QPushButton* loadButton = new QPushButton("Load From File");
        QPushButton* saveButton = new QPushButton("Save To File");

        QHBoxLayout* fileOperationsLayout = new QHBoxLayout();
        fileOperationsLayout->addWidget(loadButton);
        fileOperationsLayout->addWidget(saveButton);

        mainLayout->addLayout(fileOperationsLayout);

        QGridLayout *inputLayout = new QGridLayout;
        inputLayout->addWidget(new QLabel("First Name:"), 0, 0);
        inputLayout->addWidget(firstNameEdit, 0, 1);
        inputLayout->addWidget(new QLabel("Last Name:"), 1, 0);
        inputLayout->addWidget(lastNameEdit, 1, 1);
        inputLayout->addWidget(new QLabel("ID:"), 2, 0);
        inputLayout->addWidget(idEdit, 2, 1);
        inputLayout->addWidget(new QLabel("Date of Birth:"), 3, 0);

        QHBoxLayout* birthDateLayout = new QHBoxLayout();
        birthDateLayout->addWidget(birthDateDaySpinBox);
        birthDateLayout->addWidget(birthDateMonthSpinBox);
        birthDateLayout->addWidget(birthDateYearSpinBox);
        inputLayout->addLayout(birthDateLayout, 3, 1);

        inputLayout->addWidget(new QLabel("Enrollment Year:"), 4, 0);
        inputLayout->addWidget(enrollmentYearSpinBox, 4, 1);
        inputLayout->addWidget(new QLabel("Group:"), 5, 0);
        inputLayout->addWidget(groupEdit, 5, 1);
        inputLayout->addWidget(addStudentButton, 6, 0, 1, 2);


        mainLayout->addLayout(inputLayout);
        mainLayout->addWidget(studentListWidget);

        QHBoxLayout* sortingLayout = new QHBoxLayout();
        sortingLayout->addWidget(new QLabel("Sorter:"));
        sortingLayout->addWidget(sorterComboBox);
        sortingLayout->addWidget(new QLabel("Comparator:"));
        sortingLayout->addWidget(comparatorComboBox);
        sortingLayout->addWidget(new QLabel("Sequence:"));
        sortingLayout->addWidget(sequenceComboBox);
        mainLayout->addLayout(sortingLayout);

        mainLayout->addWidget(sortButton);
        mainLayout->addWidget(sortedStudentListWidget);

        setLayout(mainLayout);

        connect(addStudentButton, &QPushButton::clicked, this, &StudentGUI::addStudent);
        connect(sortButton, &QPushButton::clicked, this, &StudentGUI::sortStudents);
        connect(sequenceComboBox, &QComboBox::currentIndexChanged, this, &StudentGUI::changeSequenceType);
        connect(loadButton, &QPushButton::clicked, this, &StudentGUI::loadFromFile);
        connect(saveButton, &QPushButton::clicked, this, &StudentGUI::saveToFile);
    }


private slots:

    void addStudent() {

        bool is_valid;
        int id = idEdit->text().toInt(&is_valid);
        if (!is_valid) {
            displayErrorMessage("Invalid ID input.");
            return;
        }

        int enrollmentYear = enrollmentYearSpinBox->value();
        std::array<int, 3> date = { birthDateDaySpinBox->value(), birthDateMonthSpinBox->value(), birthDateYearSpinBox->value() };

        std::string firstName = firstNameEdit->text().toStdString();
        std::string lastName = lastNameEdit->text().toStdString();
        std::string group = groupEdit->text().toStdString();

        try {

            Student student(firstName, lastName, id, date, enrollmentYear,group);
            studentSequence->append(student);

            displayStudentData(student, studentListWidget);

            firstNameEdit->clear();
            lastNameEdit->clear();
            idEdit->clear();
            groupEdit->clear();
            birthDateDaySpinBox->setValue(1);
            birthDateMonthSpinBox->setValue(1);
            birthDateYearSpinBox->setValue(2000);
            enrollmentYearSpinBox->setValue(2018);

        } catch (const std::exception& e) {
            displayErrorMessage(e.what());
        }
    }

    void sortStudents() {
        int sorterIndex = sorterComboBox->currentIndex();
        ISorter<Student, bool(*)(const Student&, const Student&)>* sorter = nullptr;

        switch (sorterIndex) {
            case 0: sorter = new BubbleSort<Student, bool(*)(const Student&, const Student&)>(); break;
            case 1: sorter = new HeapSort<Student, bool(*)(const Student&, const Student&)>(); break;
            case 2: sorter = new InsertionSort<Student, bool(*)(const Student&, const Student&)>(); break;
            case 3: sorter = new BinaryInsertionSort<Student, bool(*)(const Student&, const Student&)>(); break;
            case 4: sorter = new QuickSort<Student, bool(*)(const Student&, const Student&)>(); break;
            case 5: sorter = new ShakerSort<Student, bool(*)(const Student&, const Student&)>(); break;
            case 6: sorter = new SelectionSort<Student, bool(*)(const Student&, const Student&)>(); break;
            case 7: sorter = new MergeSort<Student, bool(*)(const Student&, const Student&)>(); break;
            case 8: sorter = new ShellSort<Student, bool(*)(const Student&, const Student&)>(); break;
        }


        int comparatorIndex = comparatorComboBox->currentIndex();
        auto comparator = [&]() -> bool (*)(const Student&, const Student&) {
            switch (comparatorIndex) {
                case 0: return [](const Student& s1, const Student& s2) { return compareByID()(s1, s2); };
                case 1: return [](const Student& s1, const Student& s2) { return compareByEnrollYear()(s1, s2); };
                case 2: return [](const Student& s1, const Student& s2) { return compareByFirstName()(s1, s2); };
                case 3: return [](const Student& s1, const Student& s2) { return compareByLastName()(s1, s2); };
                case 4: return [](const Student& s1, const Student& s2) {return compareByGroup()(s1, s2); };
                case 5: return [](const Student& s1, const Student& s2) { return compareByBirthDate()(s1, s2); };

                default: return nullptr;
            }
        }();

        if (sorter && comparator && studentSequence.get() && studentSequence->getLength() > 0) {
            SharedPtr<Sequence<Student>> sortedSequence (studentSequence);
            sorter->sort(sortedSequence, comparator);

            sortedStudentListWidget->clear();
            for (int i = 0; i < sortedSequence->getLength(); ++i) {
                displayStudentData(sortedSequence->get(i), sortedStudentListWidget);
            }

        } else {
            sortedStudentListWidget->clear();

            if (!sorter) {
                displayErrorMessage("Sort type have not been selected.");
            } else if (!comparator) {
                displayErrorMessage("Comparator have not been selected.");
            } else if (!studentSequence.get() || studentSequence->getLength() == 0) {
                displayErrorMessage("cannot sort empty sequence.");
            }
        }

        delete sorter;
    }

    void changeSequenceType(int index) {
        SharedPtr<Sequence<Student>> newSequence;

        if (index == 0) {
            newSequence = SharedPtr<Sequence<Student>>(new MutableArraySequence<Student>());
        } else {
            newSequence = SharedPtr<Sequence<Student>>(new MutableListSequence<Student>());
        }


        if (studentSequence.get()) {
            for (int i = 0; i < studentSequence->getLength(); ++i) {
                newSequence->append(studentSequence->get(i));
            }
        }
        studentSequence = newSequence;
        updateStudentListWidget();
    }

    void updateStudentListWidget() {
        studentListWidget->clear();
        for (int i = 0; i < studentSequence->getLength(); ++i) {
            displayStudentData(studentSequence->get(i), studentListWidget);
        }
    }


    void loadFromFile() {
         QString filename = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt)");
         if (filename.isEmpty()) {
             displayErrorMessage("File not selected.");
             return;
         }

         try {
             SharedPtr<Sequence<Student>> loadedStudents = ReadStudentsFromFile(filename.toStdString());
             studentSequence = loadedStudents;
             studentListWidget->clear();
             for (int i = 0; i < studentSequence->getLength(); ++i) {
                 displayStudentData(studentSequence->get(i), studentListWidget);
             }
            // updateStudentListWidget();
         } catch (const std::exception& e) {
             displayErrorMessage(e.what());
         }
     }

    void saveToFile() {
        if (!studentSequence.get() || studentSequence->getLength() == 0) {
            displayErrorMessage("Cannot save empty sequence.");
            return;
        }

        QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt)");
        if (fileName.isEmpty()) {
            displayErrorMessage("File has not been selected.");
            return;
        }

        try {
            WriteStudentsToFile(studentSequence, fileName.toStdString());
        } catch (const std::exception& e) {
            displayErrorMessage(e.what());
        }
    }

};

int interface(int argc, char *argv[]) {
    QApplication app(argc, argv);

    StudentGUI gui;
    gui.setWindowTitle("Student sorts showcase");
    gui.show();

    return app.exec();
}
#endif


