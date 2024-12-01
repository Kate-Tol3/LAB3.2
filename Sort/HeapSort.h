//
// Created by Kate on 14.11.2024.
//

#pragma once
#include "ISorter.h"

template <typename T, typename Comparator>
class HeapSort : public ISorter<T, Comparator>{
private:
    //пирамидальная сортировка
    void heapify(SharedPtr<Sequence<T>> sequence, int n, int i, Comparator comp)
    {
        int largest = i; // Initialize largest because use 0 based indexing
        int l = 2 * i + 1; // left
        int r = 2 * i + 2; // right

        // left > root
        if (l < n && comp((*sequence)[largest], (*sequence)[l])) {
            largest = l;
        }
        // if right > largest already
        if (r < n && comp((*sequence)[largest], (*sequence)[r])){
            largest = r;
        }
        // if root is not largest
        if (largest != i) {
            std::swap((*sequence)[i], (*sequence)[largest]);

            // heapify sub-tree
            heapify(sequence, n, largest, comp);
        }
    }

public:

    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override {
        int n = sequence->getLength();

        // Build heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(sequence, n, i, comp);

        for (int i = n - 1; i >= 0; i--) {
            // Move current root to end
            std::swap((*sequence)[0], (*sequence)[i]);

            // call max heapify on the reduced heap
            heapify(sequence, i, 0, comp);
        }
    }
};
