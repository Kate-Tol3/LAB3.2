#ifndef MERGESORT_H
#define MERGESORT_H

#include "ISorter.h"
#include <vector> // For temporary storage during merge

template <typename T, typename Comparator>
class MergeSort : public ISorter<T, Comparator> {
public:

    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override {
        int n = sequence->getLength();
        if (n <= 1) return; // Already sorted
        mergeSort(sequence, 0, n - 1, comp);
    }

private:

    void mergeSort(SharedPtr<Sequence<T>> sequence, int left, int right, Comparator comp) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;

        mergeSort(sequence, left, mid, comp);
        mergeSort(sequence, mid + 1, right, comp);

        merge(sequence, left, mid, right, comp);
    }

    void merge(SharedPtr<Sequence<T>> sequence, int left, int mid, int right, Comparator comp) {
        int leftSize = mid - left + 1;
        int rightSize = right - mid;

        std::vector<T> leftSequence(leftSize);
        std::vector<T> rightSequence(rightSize);

        for (int i = 0; i < leftSize; ++i)
            leftSequence[i] = (*sequence)[left + i];
        for (int j = 0; j < rightSize; ++j)
            rightSequence[j] = (*sequence)[mid + 1 + j];

        // Merge back into original sequence
        int i = 0, j = 0, k = left;
        while (i < leftSize && j < rightSize) {
            if (comp(leftSequence[i], rightSequence[j])) {
                (*sequence)[k++] = leftSequence[i++];
            } else {
                (*sequence)[k++] = rightSequence[j++];
            }
        }

        // Copy remaining elements
        while (i < leftSize) {
            (*sequence)[k++] = leftSequence[i++];
        }
        while (j < rightSize) {
            (*sequence)[k++] = rightSequence[j++];
        }
    }
};

#endif //MERGESORT_H
