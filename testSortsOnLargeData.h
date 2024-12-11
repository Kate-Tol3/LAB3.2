#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <cassert>
#include <memory>
#include <fstream>
#include "Student.h"
#include "Sort/ISorter.h"
#include "FileFunc.h"
#include "Sequence/MutableArraySequence.h"
#include "Sort/BubbleSort.h"
#include "Sort/InsertionSort.h"
#include "Sort/SelectionSort.h"
#include "Sort/QuickSort.h"
#include "Sort/HeapSort.h"
#include "Sort/MergeSort.h"
#include "Sort/BinaryInsertionSort.h"
#include "Sort/ShakerSort.h"
#include "Sort/ShellSort.h"

template <typename T, template <typename> class SequenceType, typename Comparator>
void testSortOnLarge(ISorter<T, Comparator>& sorter, Comparator comp,
    const std::string& sortType, const std::string& comparedField, const std::string& filename, std::ofstream& outputFile) {

    SharedPtr<Sequence<T>> studentSequence = ReadStudentsFromFile(filename);

    // Измеряем время сортировки
    auto start = std::chrono::high_resolution_clock::now();
    sorter.sort(studentSequence, comp);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double time_taken = duration.count() * 1000.0; // время в миллисекундах

    // // проверка
    // for (int i = 0; i < studentSequence->getLength() - 1; ++i) {
    //     assert(!comp((*studentSequence)[i + 1], (*studentSequence)[i]));
    // }

    std::cout << "Sort Type: " << sortType << " | Comparator: " << comparedField << std::endl;
    std::cout << "Number of students: " << studentSequence->getLength() << std::endl;
    std::cout << "Sorting time: " << time_taken << " ms" << std::endl;
    std::cout << "~~~~~~" << std::endl;

    outputFile << "Sort Type: " << sortType << " | Comparator: " << comparedField << std::endl;
    outputFile << "Number of students: " << studentSequence->getLength() << std::endl;
    outputFile << "Sorting time: " << time_taken << " ms" << std::endl;
    outputFile << "~~~~~~" << std::endl;
}

inline void testAllSortsOnLarge(const std::string& filename) {
    using ComparatorFunc = std::function<bool(const Student&, const Student&)>;
    using Sort_template = std::vector<std::pair<std::string, ISorter<Student, ComparatorFunc>*>>;
    using Comparator_template = std::vector<std::pair<std::string, ComparatorFunc>>;

    Sort_template mySort = {
        {"BubbleSort", new BubbleSort<Student, ComparatorFunc>()},
        {"InsertionSort", new InsertionSort<Student, ComparatorFunc>()},
        {"SelectionSort", new SelectionSort<Student, ComparatorFunc>()},
        {"QuickSort", new QuickSort<Student, ComparatorFunc>()},
        {"HeapSort", new HeapSort<Student, ComparatorFunc>()},
        {"MergeSort", new MergeSort<Student, ComparatorFunc>()},
        {"BinaryInsertionSort", new BinaryInsertionSort<Student, ComparatorFunc>()},
        {"ShakerSort", new ShakerSort<Student, ComparatorFunc>()},
        {"ShellSort", new ShellSort<Student, ComparatorFunc>()}
    };

    Comparator_template myComparator = {
        {"First name", compareByFirstName()},
        {"Last name", compareByLastName()},
        {"Birth date", compareByBirthDate()},
        {"ID", compareByID()},
        {"Enrollment Year", compareByEnrollYear()},
        {"Group", compareByGroup()}
    };

    std::ofstream outputFile("largeSortingInfo.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return;
    }

    // Пары сортировка-компаратор
    for (const auto& sorter_pair : mySort) {
        for (const auto& comp_pair : myComparator) {
            testSortOnLarge<Student, MutableArraySequence, ComparatorFunc>(*sorter_pair.second, comp_pair.second, sorter_pair.first, comp_pair.first, filename, outputFile);
        }
    }

    outputFile.close();
}
