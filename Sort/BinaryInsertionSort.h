//
// Created by Kate on 14.11.2024.
//

#ifndef BINARYINSERTIONSORT_H
#define BINARYINSERTIONSORT_H
#include <vector>

#include "ISorter.h"


template <typename T, typename Comparator>
class BinaryInsertionSort : public ISorter<T, Comparator> {
public:
    // Метод двоичных вставок
     void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) {
        int n = sequence->getLength();
        for (int i = 1; i < n; ++i) {
            T key = sequence[i];
            int left = 0, right = i;
            while (left < right) {
                int mid = (left + right) / 2;
                if (comp(key, sequence[mid])) left = mid + 1;//if (key >= sequence[mid]) left = mid + 1;
                else right = mid;
            }
            for (int j = i; j > left; --j) sequence[j] = sequence[j - 1];
            sequence[left] = key;
        }
    }
};



#endif //BINARYINSERTIONSORT_H
