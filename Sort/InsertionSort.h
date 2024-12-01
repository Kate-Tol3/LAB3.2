//
// Created by Kate on 14.11.2024.
//

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "ISorter.h"

template <typename T, typename Comparator>
class InsertionSort : public ISorter<T, Comparator> {
public:

    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override{
        int n = sequence->getLength();
        for (int i = 1; i < n; ++i) {
            T key = (*sequence)[i];
            int j = i - 1;
            while (j >= 0 && comp(key, (*sequence)[j])) {
                (*sequence)[j + 1] = (*sequence)[j];
                --j;
            }
            (*sequence)[j + 1] = key;
        }
    }
};

#endif //INSERTIONSORT_H