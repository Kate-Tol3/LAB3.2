#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "ISorter.h"

template <typename T, typename Comparator>
class QuickSort : public ISorter<T, Comparator> {
public:
    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override {
        int n = sequence->getLength();
        if (n > 0) {
            quickSort(sequence, 0, n - 1, comp);
        }
    }

private:

    void quickSort(SharedPtr<Sequence<T>> sequence, int left, int right, Comparator comp) {
        if (left < right) {
            int pivot = partition(sequence, left, right, comp);

            quickSort(sequence, left, pivot - 1, comp);
            quickSort(sequence, pivot + 1, right, comp);
        }
    }

    static int partition(SharedPtr<Sequence<T>> sequence, int left, int right, Comparator comp) {
        T pivot = (*sequence)[right]; // last element as pivot
        int i = left - 1;

        for (int j = left; j < right; ++j) {
            if (comp((*sequence)[j], pivot)) {
                ++i;
                std::swap((*sequence)[i], (*sequence)[j]);
            }
        }

        std::swap((*sequence)[i + 1], (*sequence)[right]);
        return i + 1;
    }
};

#endif //QUICKSORT_H
