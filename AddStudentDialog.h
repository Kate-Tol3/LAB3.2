#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>
#include "Student.h"

class AddStudentDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddStudentDialog(QWidget* parent = nullptr);

    signals:
        void studentAdded(const Student& student);

    private slots:
        void onAddButtonClicked();

private:
    QLineEdit* firstNameEdit;
    QLineEdit* lastNameEdit;
    QLineEdit* idEdit;
    QLineEdit* groupEdit;
    QSpinBox* enrollmentYearSpinBox;
    // QLineEdit* dayEdit;
    // QLineEdit* monthEdit;
    // QLineEdit* yearEdit;
    QPushButton* addButton;
    QSpinBox* daySpinBox;
    QSpinBox* monthSpinBox;
    QSpinBox* yearSpinBox;
};

#endif // ADDSTUDENTDIALOG_H
