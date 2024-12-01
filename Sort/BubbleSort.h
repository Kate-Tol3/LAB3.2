

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "ISorter.h"

template <typename T, typename Comparator>
class BubbleSort: public ISorter<T, Comparator> {
public:
    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override {
        int n = sequence->getLength();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (comp((*sequence)[j + 1], (*sequence)[j])) {
                    std::swap((*sequence)[j], (*sequence)[j + 1]);
                }
            }
        }
    }
};

#endif //BUBBLESORT_H
