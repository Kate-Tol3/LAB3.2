#include "Test.h"


template <typename T, template <typename> class SequenceType, typename Comparator>
void testSort(ISorter<T, Comparator>& sorter, Comparator comp,
    const std::string& sortType, const std::string& comparedField) {
    SharedPtr<Sequence<T>> emptySequence = SharedPtr<Sequence<T>>(new SequenceType<T>());// empty sequence
    sorter.sort(emptySequence, comp);
    assert(emptySequence->getLength() == 0);

    std::array<int, 3> date1 = {5, 10, 2005}; // dates of birth
    std::array<int, 3> date2 = {6, 11, 2002};
    std::array<int, 3> date3 = {7, 4, 2000};

    //no duplicates
    std::array<Student, 3> myGroup = { Student("Alex", "Black", 0, date1, 2021, "21-aba"),
        Student("Alex", "Black", 0, date2, 2021, "21-aba"),
        Student("Alex", "Black", 0, date3, 2021, "21-aba")
    };

    SharedPtr<Sequence<T>> tempSequence = SharedPtr<Sequence<T>>(new SequenceType<T>(myGroup.data(), myGroup.size()));
    sorter.sort(tempSequence, comp);
    assert(tempSequence->getLength() == myGroup.size());
    for (int i = 0; i < tempSequence->getLength() - 1; ++i) {
        assert(!comp((*tempSequence)[i + 1], (*tempSequence)[i]));
    }

    std::array<int, 3> date4 = {7, 4, 2000};
    std::array<int, 3> date5 = {7, 4, 2000};
    std::array<int, 3> date6 = {7, 4, 2001};

    //with duplicates
    std::array<Student, 3> myGroup1 = { Student("Alex", "Black", 0, date4, 2021, "20-abb"),
       Student("Alex", "Black", 0, date5, 2021, "20-abb"),
       Student("Alex", "Black", 0, date6, 2021, "20-abb")
   };

    SharedPtr<Sequence<T>> tempSequence1 = SharedPtr<Sequence<T>>(new SequenceType<T>(myGroup1.data(), myGroup1.size()));
    sorter.sort(tempSequence1, comp);
    assert(tempSequence1->getLength() == myGroup1.size());
    for (int i = 0; i < tempSequence1->getLength() - 1; ++i) {
        assert(!comp((*tempSequence)[i + 1], (*tempSequence)[i]));
    }

    std::cout << "Sorted sequence(no duplicates): " << sortType << " by " << comparedField << std::endl;
    tempSequence->print();
    std::cout << "~~~~~~" << std::endl;

    std::cout << "Sorted sequence(with duplicates): " << sortType << " by " << comparedField << std::endl;
    tempSequence1->print();
    std::cout << "~~~~~~" << std::endl;

};


void testAllSorts() {
    using ComparatorFunc = std::function<bool(const Student&, const Student&)>;
    using Sort_template = std::vector<std::pair<std::string, ISorter<Student, ComparatorFunc> *>>;
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
        {"ShellSort", new ShellSort<Student, ComparatorFunc>()},
    };

    Comparator_template myComparator = {
        {"First name", compareByFirstName()},
        {"Last name", compareByLastName()},
        {"Birth date", compareByBirthDate()},
        {"ID", compareByID()},
        {"Enrollment Year", compareByEnrollYear()},
        {"Group", compareByGroup()}
    };

    for (const auto & sorter_pair: mySort) {
        for (const auto & comp_pair: myComparator) {
            testSort<Student, MutableArraySequence, ComparatorFunc>(*sorter_pair.second, comp_pair.second,sorter_pair.first, comp_pair.first);
            testSort<Student, MutableListSequence, ComparatorFunc>(*sorter_pair.second, comp_pair.second,sorter_pair.first, comp_pair.first);
        }
    }
}

void testAll() {
    testAllSorts();
}