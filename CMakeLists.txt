#cmake_minimum_required(VERSION 3.29)
#project(localLab3_2)
#
#set(CMAKE_CXX_STANDARD 20)
#
#add_executable(localLab3_2 main.cpp
#        Sequence/Sequence.h
#        Sort/BubbleSort.h
#        Sort/HeapSort.h
#        Sort/ShakerSort.h
#        Sort/InsertionSort.h
#        Sort/SelectionSort.h
#        Sort/BinaryInsertionSort.h
#        Sort/ISorter.h
#        Sort/QuickSort.h
#        Sort/MergeSort.h
#        Sort/ShellSort.h
#        Sequence/MutableListSequence.h
#        Sequence/MutableArraySequence.h
#        Pointers/WeakPtr.h
#        Pointers/UnqPtr.h
#        Student.cpp
#        Student.h
#        Sequence/DynamicArray.h
#        Sequence/Exception.h
#        Test.cpp
#        Test.h
#        StudentGUI.h
#)
##
#find_package(Qt6 REQUIRED COMPONENTS Core)
#find_package(Qt6 REQUIRED COMPONENTS Widgets)
#find_package(Qt6 REQUIRED COMPONENTS Gui)
##
#qt_standard_project_setup()
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
##qt_add_executable(localLab3_2
##        GUI.cpp
##)
#
##target_include_directories(localLab3_2 PUBLIC
##        Sort
##        Sequence
##        Pointers
##)
#
#target_link_libraries(localLab3_2 PRIVATE Qt6::Core Qt6::Widgets)
#
#
#
## Добавьте этот блок для обработки moc файлов
#set(CMAKE_AUTOMOC ON)
#
#
### Добавьте файл .cpp и .h в список исходников
##add_executable(localLab3_2
##        main.cpp
##        Student.cpp
##        StudentGUI.cpp
##        Test.cpp
##)
#
## Добавьте зависимость от Qt6
#target_link_libraries(localLab3_2 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)


cmake_minimum_required(VERSION 3.14)  # Меньшая версия для совместимости с Qt6
project(localLab3_2)

set(CMAKE_CXX_STANDARD 20)

# Добавляем исходники
add_executable(localLab3_2
        main.cpp
        Sequence/Sequence.h
        Sort/BubbleSort.h
        Sort/HeapSort.h
        Sort/ShakerSort.h
        Sort/InsertionSort.h
        Sort/SelectionSort.h
        Sort/BinaryInsertionSort.h
        Sort/ISorter.h
        Sort/QuickSort.h
        Sort/MergeSort.h
        Sort/ShellSort.h
        Sequence/MutableListSequence.h
        Sequence/MutableArraySequence.h
        Pointers/WeakPtr.h
        Pointers/UnqPtr.h
        Student.cpp
        Student.h
        Sequence/DynamicArray.h
        Sequence/Exception.h
        Test.cpp
        Test.h
        StudentGUI.h
        FileFunc.h
        # StudentGUI.cpp  # Убедитесь, что этот файл добавлен StudentGUI.cpp # Если есть, добавьте и cpp файл
)

# Найти Qt6 и необходимые компоненты
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Настройка Qt проекта
qt_standard_project_setup()

# Включаем автоматическую обработку moc файлов
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# Линкуем с Qt6
#target_link_libraries(localLab3_2 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# Включаем директивы для работы с moc (не требуется, если CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOMOC ON)


target_link_libraries(localLab3_2 Qt6::Core Qt6::Gui Qt6::Widgets)