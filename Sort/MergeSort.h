//
// Created by Kate on 14.11.2024.
//

#ifndef MERGESORT_H
#define MERGESORT_H
#include "Sequence/MutableArraySequence.h"


template <typename T, typename Comparator>
class MergeSort : public ISorter<T, Comparator> {
public:
    // Сортировка слиянием
    void sort(SharedPtr<Sequence<T>> sequence, Comparator comp) override {
        if (sequence->getLength() <= 1) return; // уже отсортировано
        mergeSort(sequence, 0, sequence->getLength() - 1, comp);
    }

private:

    void mergeSort(SharedPtr<Sequence<T>> sequence, int left, int right, Comparator comp) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;

        // сортируем две половины
        mergeSort(sequence, left, mid, comp);
        mergeSort(sequence, mid + 1, right, comp);

        // cливаем отсортированные половины
        merge(sequence, left, mid, right, comp);
    }

    void merge(SharedPtr<Sequence<T>> sequence, int left, int mid, int right, Comparator comp) {
        int leftSize = mid - left + 1;
        int rightSize = right - mid;

        Sequence<T> leftSequence(leftSize);
        Sequence<T> rightSequence(rightSize);

        // Копируем данные
        for (int i = 0; i < leftSize; ++i)
            leftSequence.set(i, sequence->get(left + i));
        for (int j = 0; j < rightSize; ++j)
            rightSequence.set(j, sequence->get(mid + 1 + j));

        int i = 0, j = 0, k = left;

        while (i < leftSize || j < rightSize) {
            if (i < leftSize && (j >= rightSize || comp(leftSequence.get(i), rightSequence.get(j)))) {
                sequence->set(k++, leftSequence.get(i++));
            } else {
                sequence->set(k++, rightSequence.get(j++));
            }
        }
    }
};


#endif //MERGESORT_H
