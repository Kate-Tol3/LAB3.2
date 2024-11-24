cmake_minimum_required(VERSION 3.29)
project(localLab3_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(localLab3_2 main.cpp
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
        Student.h)
