#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include "ISorter.h"

template <typename T, typename Comparator>
class SelectionSort : public ISorter<T, Comparator> {
public:
    // Сортировка с помощью простого выбора
    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override{
        int n = sequence->getLength();
        for (int i = 0; i < n - 1; ++i) { // < n
            int minIdx = i;
            for (int j = i + 1; j < n; ++j) {
                if (comp(sequence[j],  sequence[minIdx])) {
                    minIdx = j;
                }
            }
            std::swap(sequence[i], sequence[minIdx]);
        }
    }
};

#endif //SELECTIONSORT_H
