
#ifndef BINARYINSERTIONSORT_H
#define BINARYINSERTIONSORT_H

#include "ISorter.h"


template <typename T, typename Comparator>
class BinaryInsertionSort : public ISorter<T, Comparator> {
public:
    // Метод двоичных вставок
    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) {
        int n = sequence->getLength();
        for (int i = 1; i < n; ++i) {
            T key = (*sequence)[i];
            int left = 0, right = i;

            // binary search to find the correct position for key
            while (left < right) {
                int mid = (left + right) / 2;

                if (comp((*sequence)[mid], key))
                    left = mid + 1;
                else
                    right = mid;
            }

            // shift elements to make space for key
            for (int j = i; j > left; --j) {
                (*sequence)[j] = (*sequence)[j - 1];
            }

            // insert key at the correct position
            (*sequence)[left] = key;
        }
    }
};



#endif //BINARYINSERTIONSORT_H
