#include "GUI.h"
#include <QMessageBox>
#include <fstream>
#include "Sort/BubbleSort.h"
#include "Sort/HeapSort.h"
#include "Sort/InsertionSort.h"
#include "Sort/ISorter.h"
#include "Sort/MergeSort.h"
#include "Sort/QuickSort.h"
#include "Sort/SelectionSort.h"
#include "Sort/ShakerSort.h"
#include "Sort/ShellSort.h"
#include "Sort/BinaryInsertionSort.h"
#include "FileFunc.h"


GUI::GUI(QWidget* parent) : QMainWindow(parent) {

    setWindowTitle("Управление студентами");
    resize(600, 400);

    // кнопки
    addButton = new QPushButton("Добавить студента", this);
    deleteButton = new QPushButton("Удалить студента", this);
    saveButton = new QPushButton("Сохранить в файл", this);
    loadButton = new QPushButton("Загрузить из файла", this);
    sortButton = new QPushButton("Сортировать", this);

    // выпадающий список выбора компаратора
    sortCriteriaBox = new QComboBox(this);
    sortCriteriaBox->addItem("По ID");
    sortCriteriaBox->addItem("По фамилии");
    sortCriteriaBox->addItem("По имени");
    sortCriteriaBox->addItem("По году поступления");
    sortCriteriaBox->addItem("По группе");
    sortCriteriaBox->addItem("По дате рождения");

    sorterBox = new QComboBox(this);
    sorterBox = new QComboBox();
    sorterBox->addItem("Bubble Sort");
    sorterBox->addItem("Heap Sort");
    sorterBox->addItem("Insertion Sort");
    sorterBox->addItem("BinaryInsertion Sort");
    sorterBox->addItem("Quick Sort");
    sorterBox->addItem("Shaker Sort");
    sorterBox->addItem("Selection Sort");
    sorterBox->addItem("Merge Sort");
    sorterBox->addItem("Shell Sort");


    studentList = new QListWidget(this);

    this->setStyleSheet(R"(
        QWidget {
            background-color: #f0f4f8;
            font-family: Arial, sans-serif;
        }

        QLineEdit, QSpinBox, QComboBox, QPushButton {
            border: 2px solid #a3b9c9;
            border-radius: 8px;
            padding: 5px;
            margin: 5px;
            background-color: #ffffff;
            font-size: 14px;
        }

        QPushButton {
            background-color: #5c7f8c;
            color: white;
            font-weight: bold;
            padding-left: 10px;  /* Добавляем отступ слева */
            padding-right: 10px; /* Добавляем отступ справа */
        }

        QPushButton:hover {
            background-color: #4b6d7c;
        }

        QComboBox {
            background-color: #e4f1f6;
        }

        QSpinBox {
            background-color: #e4f1f6;
        }

        QSpinBox::up-button, QSpinBox::down-button {
            border: none;
            background: transparent;
            width: 0px;
            height: 0px;
        }

        QComboBox {
            border: 2px solid #a3b9c9;
            border-radius: 8px;
            padding: 5px;
            background-color: #ffffff;
            font-size: 14px;
            padding-right: 20px;
        }

        QComboBox::drop-down {
            border: none;
            width: 0px;
            height: 0px;
        }

        QComboBox::down-arrow {
            image: none;
            width: 0px;
            height: 0px;
        }

        QListWidget {
            background-color: #ffffff;
            border: 1px solid #a3b9c9;
            border-radius: 5px;
            margin-top: 10px;
        }

        QLabel {
            color: #5f5f5f;
            font-size: 14px;
        }
    )");

    QFont font = studentList->font();
    font.setPointSize(11);  // Устанавливаем размер шрифта
    studentList->setFont(font);

    // Layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(loadButton);

    QHBoxLayout* sortLayout = new QHBoxLayout();
    sortLayout->addWidget(sortCriteriaBox);
    sortLayout->addWidget(sorterBox);
    sortLayout->addWidget(sortButton);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(sortLayout);
    mainLayout->addWidget(studentList);

    setCentralWidget(centralWidget);


    connect(addButton, &QPushButton::clicked, this, &GUI::openAddStudentDialog);
    connect(deleteButton, &QPushButton::clicked, this, &GUI::removeSelectedStudent);
    connect(saveButton, &QPushButton::clicked, this, &GUI::saveToFile);
    connect(loadButton, &QPushButton::clicked, this, &GUI::loadFromFile);
    connect(sortButton, &QPushButton::clicked, this, &GUI::sortStudents);
}

void GUI::openAddStudentDialog() {
    AddStudentDialog dialog(this);
    connect(&dialog, &AddStudentDialog::studentAdded, this, &GUI::addStudentToList);
    dialog.exec();
}

void GUI::addStudentToList(const Student& student) {
    students.append(student);
    refreshStudentList();
}

void GUI::removeSelectedStudent() {
    QListWidgetItem* selectedItem = studentList->currentItem();
    if (selectedItem) {
        int row = studentList->row(selectedItem);
        delete selectedItem;
        students.erase(row);
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите студента для удаления.");
    }
}

void GUI::saveToFile() {

    if (students.getLength() == 0) {
        QMessageBox::information(this, "Ошибка", "Невозможно сохранить в файл пустую последовательность.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) {
        QMessageBox::information(this, "Ошибка", "Введите имя файла.");
        return;
    }

    try {
        SharedPtr<Sequence<Student>> ptrStudents = SharedPtr<Sequence<Student>>(new MutableArraySequence<Student>(students));
        WriteStudentsToFile(ptrStudents, fileName.toStdString());
    } catch (const std::exception& e) {
       QMessageBox::information(this, "Ошибка", e.what());
    }
}

void GUI::loadFromFile() {

        // диалоговое окно для выбора файла
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить файл", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        try {

            SharedPtr<Sequence<Student>> loadedStudents = ReadStudentsFromFile(fileName.toStdString());
            students =  MutableArraySequence<Student>(*loadedStudents);
            studentList->clear();
            for (int i = 0; i < students.getLength(); ++i) {
                Student student = students.get(i);
                studentList->addItem(QString::fromStdString(student.getFirstName() + " " + student.getLastName()));
            }
            refreshStudentList();
            QMessageBox::information(this, "Успех", "Данные загружены из файла.");
        } catch (const std::exception& e) {
            QMessageBox::information(this, "Ошибка", e.what());
        }
    }
}


void GUI::sortStudents() {
    int sortType = sorterBox->currentIndex();

    // Выбор алгоритма сортировки
    ISorter<Student, bool(*)(const Student&, const Student&)>* sorter = nullptr;
    switch (sortType) {
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

    // Выбор компаратора для сортировки
    int criteria = sortCriteriaBox->currentIndex();
    auto comparator = [&]() -> bool (*)(const Student&, const Student&) {
        switch (criteria) {
            case 0: return [](const Student& s1, const Student& s2) { return compareByID()(s1, s2); };
            case 1: return [](const Student& s1, const Student& s2) { return compareByEnrollYear()(s1, s2); };
            case 2: return [](const Student& s1, const Student& s2) { return compareByFirstName()(s1, s2); };
            case 3: return [](const Student& s1, const Student& s2) { return compareByLastName()(s1, s2); };
            case 4: return [](const Student& s1, const Student& s2) { return compareByGroup()(s1, s2); };
            case 5: return [](const Student& s1, const Student& s2) { return compareByBirthDate()(s1, s2); };
            default: return nullptr;
        }
    }();

    if (sorter && comparator && students.getLength() > 0) {

        SharedPtr<Sequence<Student>> ptrStudents = SharedPtr<Sequence<Student>>(new MutableArraySequence<Student>(students));
        sorter->sort(ptrStudents, comparator);

        students =  MutableArraySequence<Student>(*ptrStudents);
        studentList->clear();
        for (int i = 0; i < students.getLength(); ++i) {
            Student student = students.get(i);
            studentList->addItem(QString::fromStdString(student.getFirstName() + " " + student.getLastName()));
        }

    } else {
        studentList->clear();

        if (!sorter) {
            QMessageBox::information(this, "Ошибка", "Не выбран тип сортировки.");
        } else if (!comparator) {
            QMessageBox::information(this, "Ошибка", "Не выбран критерий сортировки.");
        } else if (students.getLength() == 0) {
            QMessageBox::information(this, "Ошибка", "Невозможно отсортировать пустую последовательность.");
        }
    }

    refreshStudentList();
    delete sorter;
}


void GUI::refreshStudentList() {
    studentList->clear();
    for (int i = 0; i < students.getLength(); ++i) {
        QString studentInfo = QString::fromStdString(
            students[i].getFirstName() + " " + students[i].getLastName() +
            " | ID: " + std::to_string(students[i].getID()) +
            " | Группа: " + students[i].getGroup() +
            " | Год: " + std::to_string(students[i].getEnrollmentYear()) +
            " | Дата рождения: " + std::to_string(students[i].getBirthDate()[0]) + "/" +
            std::to_string(students[i].getBirthDate()[1]) + "/" +
            std::to_string(students[i].getBirthDate()[2])
        );
        studentList->addItem(studentInfo);
    }
}




