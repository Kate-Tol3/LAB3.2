#include "AddStudentDialog.h"
#include <QSpinBox>
#include <QMessageBox>

AddStudentDialog::AddStudentDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Добавить студента");

    setFixedSize(400, 400); // Задаем размер окна (ширина, высота)

    firstNameEdit = new QLineEdit(this);
    firstNameEdit->setPlaceholderText("Имя");

    lastNameEdit = new QLineEdit(this);
    lastNameEdit->setPlaceholderText("Фамилия");

    idEdit = new QLineEdit(this);
    idEdit->setPlaceholderText("ID");

    groupEdit = new QLineEdit(this);
    groupEdit->setPlaceholderText("Группа");

    enrollmentYearSpinBox = new QSpinBox(this);
    enrollmentYearSpinBox->setRange(1900, 2100);
    enrollmentYearSpinBox->setToolTip("Год поступления");

    // Используем QSpinBox для ввода дня, месяца и года
    daySpinBox = new QSpinBox(this);
    daySpinBox->setRange(1, 31);  // День от 1 до 31
    daySpinBox->setToolTip("День (1-31)");

    monthSpinBox = new QSpinBox(this);
    monthSpinBox->setRange(1, 12);  // Месяц от 1 до 12
    monthSpinBox->setToolTip("Месяц (1-12)");

    yearSpinBox = new QSpinBox(this);
    yearSpinBox->setRange(1900, 2100);  // Год от 1900 до 2100
    yearSpinBox->setToolTip("Год");

    addButton = new QPushButton("Добавить студента", this);
    addButton->setFixedSize(200, 50); // Увеличенная кнопка

    // Layouts
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Введите данные студента:", this));
    layout->addWidget(firstNameEdit);
    layout->addWidget(lastNameEdit);
    layout->addWidget(idEdit);
    layout->addWidget(groupEdit);
    layout->addWidget(enrollmentYearSpinBox);

    layout->addWidget(new QLabel("Дата рождения:", this));
    QHBoxLayout* dateLayout = new QHBoxLayout();
    dateLayout->addWidget(daySpinBox);
    dateLayout->addWidget(monthSpinBox);
    dateLayout->addWidget(yearSpinBox);
    layout->addLayout(dateLayout);
    layout->addWidget(addButton);

    this->setStyleSheet(R"(
            QWidget {
                background-color: #f0f4f8;
                font-family: Arial, sans-serif;
            }

            QLineEdit, QSpinBox, QPushButton {
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
            }

            QPushButton:hover {
                background-color: #4b6d7c;
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

            QLabel {
                color: #5f5f5f;
                font-size: 14px;
            }
        )");

    // Соединение кнопки с обработкой добавления
    connect(addButton, &QPushButton::clicked, this, &AddStudentDialog::onAddButtonClicked);
}

void AddStudentDialog::onAddButtonClicked() {
    try {
        std::string firstName = firstNameEdit->text().toStdString();
        std::string lastName = lastNameEdit->text().toStdString();
        int id = idEdit->text().toInt();
        std::string group = groupEdit->text().toStdString();
        int enrollmentYear = enrollmentYearSpinBox->value();
        int day = daySpinBox->value();  // Получаем значение из QSpinBox
        int month = monthSpinBox->value();  // Получаем значение из QSpinBox
        int year = yearSpinBox->value();  // Получаем значение из QSpinBox

        if (!Date::isValidDate(day, month, year)) {
            throw std::invalid_argument("Некорректная дата рождения!");
        }

        Date birthDate(day, month, year);
        Student newStudent(firstName, lastName, id, {day, month, year}, enrollmentYear, group);

        emit studentAdded(newStudent); // Отправляем сигнал с новым студентом
        accept();
    } catch (const std::exception& e) {
        // Обработка ошибок ввода
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}
