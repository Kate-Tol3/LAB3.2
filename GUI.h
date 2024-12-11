#ifndef STUDENTGUI_H
#define STUDENTGUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QFileDialog>
#include "AddStudentDialog.h"
#include "Student.h"
#include "Sequence/MutableArraySequence.h"

class GUI : public QMainWindow {
    Q_OBJECT

public:
    explicit GUI(QWidget* parent = nullptr);

    private slots:
        void openAddStudentDialog();
    void addStudentToList(const Student& student);
    void removeSelectedStudent();
    void saveToFile();
    void loadFromFile();
    void sortStudents();


private:
    // Внутренние компоненты интерфейса
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* saveButton;
    QPushButton* loadButton;
    QPushButton* sortButton;
    QComboBox* sortCriteriaBox;
    QComboBox* sorterBox;
    QListWidget* studentList;

    // Внутреннее хранилище студентов
    MutableArraySequence<Student> students;

    void refreshStudentList();

};

inline int gui_start(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GUI window;
    window.setWindowTitle("Student Management System");
    window.show();
    return app.exec();
}

#endif // STUDENTGUI_H


