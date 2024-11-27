//
// Created by Kate on 14.11.2024.
//

#pragma once
#include "ISorter.h"

template <typename T, typename Comparator>
class HeapSort : public ISorter<T, Comparator>{
private:
    // Пирамидальная сортировка
    // static void sort(MutableArraySequence<T>& sequence) {
    //
    //     auto heapify = [](MutableArraySequence<T>& arr, int n, int i) {
    //         int largest = i;
    //         int left = 2 * i + 1;
    //         int right = 2 * i + 2;
    //         if (left < n && arr[left] > arr[largest]) largest = left;
    //         if (right < n && arr[right] > arr[largest]) largest = right;
    //         if (largest != i) {
    //             std::swap(arr[i], arr[largest]);
    //             heapify(arr, n, largest);
    //         }
    //     };
    //
    //     int n = sequence.getLength();
    //     for (int i = n / 2 - 1; i >= 0; --i) heapify(sequence, n, i);
    //     for (int i = n - 1; i >= 0; --i) {
    //         std::swap(sequence[0], sequence[i]);
    //         heapify(sequence, i, 0);
    //     }
    // }

    void heapify(SharedPtr<Sequence<T>> sequence, int n, int i, Comparator comp)
    {
        int largest = i; // Initialize largest as root Since we are using 0 based indexing
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && comp((*sequence)[largest], (*sequence)[l])) {
            largest = l;
        }
        // If right child is larger than largest so far
        if (r < n && comp((*sequence)[largest], (*sequence)[r])){
            largest = r;
        }
        // If largest is not root
        if (largest != i) {
            std::swap((*sequence)[i], (*sequence)[largest]);

            // Recursively heapify the affected sub-tree
            heapify(sequence, n, largest, comp);
        }
    }

public:
    // main function to do heap sort
    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override {
        int n = sequence->getLength();

        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(sequence, n, i, comp);

        // One by one extract an element from heap
        for (int i = n - 1; i >= 0; i--) {
            // Move current root to end
            std::swap((*sequence)[0], (*sequence)[i]);

            // call max heapify on the reduced heap
            heapify(sequence, i, 0, comp);
        }
    }
};
