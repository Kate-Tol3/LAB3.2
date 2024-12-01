cmake_minimum_required(VERSION 3.29)  # Меньшая версия для совместимости с Qt6
project(localLab3_2)

set(CMAKE_CXX_STANDARD 20)


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
        Unused.cpp
        Unused.h
)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()


#set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_link_libraries(localLab3_2 Qt6::Core Qt6::Gui Qt6::Widgets)