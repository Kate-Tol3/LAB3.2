#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "ISorter.h"

template <typename T, typename Comparator>
class QuickSort : public ISorter<T, Comparator> {
public:
    // Public sort function
    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override {
        int n = sequence->getLength();
        if (n > 0) {
            quickSort(sequence, 0, n - 1, comp);
        }
    }

private:
    // Recursive quick sort function
    void quickSort(SharedPtr<Sequence<T>> sequence, int left, int right, Comparator comp) {
        if (left < right) {
            // Partition the array and get the pivot index
            int pivot = partition(sequence, left, right, comp);

            // Recursively sort elements before and after the pivot
            quickSort(sequence, left, pivot - 1, comp);
            quickSort(sequence, pivot + 1, right, comp);
        }
    }

    // Partition function to arrange elements around the pivot
    static int partition(SharedPtr<Sequence<T>> sequence, int left, int right, Comparator comp) {
        T pivot = (*sequence)[right]; // Choose the last element as pivot
        int i = left - 1;

        // Rearrange elements based on the pivot
        for (int j = left; j < right; ++j) {
            if (comp((*sequence)[j], pivot)) { // If element is less than pivot
                ++i;
                std::swap((*sequence)[i], (*sequence)[j]);
            }
        }

        // Place the pivot in the correct position
        std::swap((*sequence)[i + 1], (*sequence)[right]);
        return i + 1;
    }
};

#endif //QUICKSORT_H
