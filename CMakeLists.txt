cmake_minimum_required(VERSION 3.29)
project(localLab3_2)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

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
        GUI.h
        AddStudentDialog.h
        AddStudentDialog.cpp
        GUI.cpp
        testSortsOnLargeData.h
)

target_link_libraries(localLab3_2
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

